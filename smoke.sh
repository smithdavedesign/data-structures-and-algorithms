#!/bin/sh
# Runs every program with sample input and fails on a crash, a hang, or (when built with
# -fsanitize=address,undefined) any memory error, undefined behavior or leak.
# CI: make CXXFLAGS="-std=c++17 -O1 -g -fsanitize=address,undefined" && sh smoke.sh
set -e
export UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 ASAN_OPTIONS=halt_on_error=1
run() { name=$1; shift; printf '%-26s' "$name"; if out=$(cd "$name" && eval "timeout 60 $*" 2>&1); then echo ok; else echo FAIL; echo "$out" | tail -20; exit 1; fi; }
run linked-list "./linked-list test.input"
run maze "printf 'x\nd\ns\nq\ny\nx\nq\nn\n' | ./maze"
run vector-sort "./vector-sort test.txt"
run real-number-calculator "./real-number-calculator < /dev/null"
run large-number-calculator "printf '123456789012345678901234567890\n987654321098765432109876543210\ny\n-5\n12\nn\n' | ./large-number-calculator"
for lang in '1\n01\n0110\n1\n10' '2\n01\n1101\n1\n0110' '3\n11\n1\n1\n0110\n1\n1111' '3\n1\n2\n2\n0101' '3\n1\n3\n2\n0101' '4\n1\no\n0111\n1\n0110' '4\n1\ne\n0110'; do
  run dfa-creator "printf '2\n01\n$lang\n2\n' | ./dfa-creator"
done
