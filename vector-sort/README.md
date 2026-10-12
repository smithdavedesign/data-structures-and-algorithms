# Vector sort: why summation order matters

Reads floating-point values into a `std::vector`, then sums them three ways: unsorted, sorted descending and sorted ascending. The totals differ, because `float` addition isn't associative: adding small values first keeps more of their precision.

Homework 2, February 2017.

```sh
make && ./vector-sort test.txt
```

```
The sum of the unsorted values is: 33916632.00000
The sum of the descending values is: 33916636.00000
The sum of the ascending values is: 33916636.00000
```

**Changed in 2026:** the helper was named `function`, which clashes with `std::function` under `using namespace std` on modern compilers. It's now `sortAndSum`.
