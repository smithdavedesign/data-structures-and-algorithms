# Arbitrary-precision real numbers

A `Real` class that stores numbers as digit vectors, so they keep any precision: comparison, addition, subtraction and multiplication of signed decimals, plus conversion from `int`, `long long`, `double` and strings.

CS 460, Homework 4, March 2017. The test driver (`smithH6.cpp`) was written by a classmate, credited in its header.

```sh
make && ./real-number-calculator
```

```
R6: -1234.567890000000033978722058236598968505859375
999.999
0.001
add :  1000.000
R4 + R5, where R5 is: 12.3123answer is:  12357.3123
```

`R6` comes from a `double`. Printing its exact binary value is the point: `-1234.56789` can't be stored exactly as a `double`.
