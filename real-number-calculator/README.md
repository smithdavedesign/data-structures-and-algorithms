# Arbitrary-precision real numbers

A `Real` class for signed decimals of any length and precision, stored as digit vectors:
- comparisons, `+`, `-`, `*` and `/`;
- `round(n)`, half away from zero;
- `precision()` and `toString()`;
- stream I/O;
- conversion from `int`, `long long`, strings, and `double` (every digit of the binary value).

CS 460, Homework 4, March 2017. The test driver (`smithH6.cpp`) was written by a classmate, credited in its header.

```sh
make && ./real-number-calculator < /dev/null   # the classmate's driver
make test                                      # 9,000 random cases against Python's exact Decimal
```

```
R6: -1234.567890000000033978722058236598968505859375
add : 1000.000
-8769.879 + -4859.75843 = -13629.63743
R2 should (CORRECTLY) be less than R3: -141.100055 < -11.9456
```

| Result | Precision |
|---|---|
| sum or difference | the larger precision of the two operands |
| product | the sum of their precisions |
| quotient | 10 more digits than the larger, rounded half away from zero |

Division by zero throws `std::domain_error`. `R6` comes from a `double`, and printing its exact binary value is the point: `-1234.56789` can't be stored exactly as a `double`.

**Rewritten in 2026.** A fuzz test against exact decimal arithmetic showed the 2017 class was mostly broken:
- **Addition and subtraction:** wrong on every case. A stray NUL byte was printed before the result, and the last fraction digit was dropped.
- **Memory:** the addition loop read past the end of a vector (found by AddressSanitizer).
- **Multiplication:** usually returned the left operand.
- **Division:** a stub.
- **Comparisons:** crashed on whole numbers.

The class keeps the same public interface, so the classmate's driver runs unchanged. The arithmetic is now about 370 lines instead of 1,800, and `make test` checks it against Python's `Decimal`. The original is in git history.
