"""Checks Real's + - * / < == against Python's exact Decimal on random signed decimals.

Usage: python3 fuzz.py SEED OPS COUNT DRIVER   (make test runs it)
"""
import random, subprocess, sys
from decimal import Decimal, getcontext, ROUND_HALF_UP
getcontext().prec = 200
random.seed(int(sys.argv[1]) if len(sys.argv) > 1 else 1)
def num():
    s = '-' if random.random() < 0.3 else ''
    s += str(random.randint(0, 10 ** random.randint(0, 6)))
    if random.random() < 0.7: s += '.' + ''.join(random.choice('0123456789') for _ in range(random.randint(1, 6)))
    return s
def norm(t):
    t = t.strip()
    if t in ('0', '1') : return t
    try: d = Decimal(t)
    except Exception: return 'BAD:' + t
    return str(d.normalize()) if d != 0 else '0'
cases, ops = [], sys.argv[2] if len(sys.argv) > 2 else '+-*<='
for _ in range(int(sys.argv[3]) if len(sys.argv) > 3 else 400):
    cases.append((num(), random.choice(ops), num()))
inp = '\n'.join(f"{a} {'==' if o == '=' else o} {b}" for a, o, b in cases) + '\n'
p = subprocess.run([sys.argv[4] if len(sys.argv) > 4 else './fuzz_driver'], input=inp, capture_output=True, text=True, timeout=120)
outs = p.stdout.split('\n')
bad = {}
for (a, o, b), got in zip(cases, outs):
    A, B = Decimal(a), Decimal(b)
    if o == '/':
        if B == 0: want = 'DIV0'
        else:
            q, sc = got.split()[0], int(got.split()[1]) if len(got.split()) > 1 else 0
            want = (A / B).quantize(Decimal(1).scaleb(-sc), rounding=ROUND_HALF_UP); got = q
    else:
        want = {'+': A + B, '-': A - B, '*': A * B, '<': int(A < B), '=': int(A == B)}[o]
    w = norm(str(want)) if o in '+-*/' and want != 'DIV0' else str(want)
    g = norm(got) if o in '+-*/' and got.strip() != 'DIV0' else got.strip()
    if w != g: bad.setdefault(o, []).append(f"{a} {o} {b}: got {got.strip()!r}, want {w}")
print(f"{len(cases)} cases, {len(outs)-1} answered; stderr: {p.stderr[:300]!r}")
for o in ops: print(f"  {o}: {len(bad.get(o, []))} wrong", (bad.get(o) or [''])[0][:160])
sys.exit(1 if bad or p.returncode or p.stderr else 0)
