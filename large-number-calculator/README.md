# Large-number calculator

Adds and subtracts integers of any length, stored as digit vectors (`largeNum`). It also has a recursive integer exponentiation.

```sh
make
printf '123456789012345678901234567890\n987654321098765432109876543210\nn\n' | ./large-number-calculator
```

```
EX result : 64
a + b = 1111111110111111111011111111100
 a - b = -864197532086419753208641975320
```

**Changed in 2026:**
- `exponentiation()` never finished. `exp_num-1 / 2` parses as `exp_num - 0`, so odd exponents recursed forever, and the program hung before printing anything. It now uses exponentiation by squaring.
- `main` leaked every number it read and every result (16 blocks for two calculations). The inputs now live on the stack and the results are deleted.
- The second prompt said "first" again.

Add and subtract were checked against Python's integers on 2,000 random pairs of up to 40 digits: all correct.
