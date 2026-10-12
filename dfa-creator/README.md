# DFA creator

Builds a deterministic finite automaton at run time from your description of a regular language: strings that start with, end with or contain a substring, or contain it at most, at least or exactly k times, or an odd or even number of times. It prints the transition table, then tests any strings you type against it. The DFA is a 2-D transition array.

CS 454 (theory of computation), August 2016.

```sh
make && ./dfa-creator    # then follow the prompts
```

**Changed in 2026** (found with strict warnings and the sanitizers):
- `if (contain_even_odd = true)` assigned instead of comparing, so the odd/even DFA was built whenever no earlier option matched. It's now `==`.
- The at most / at least / exactly flags were read without ever being initialized (UndefinedBehaviorSanitizer).
- A zero-length array member was read out of bounds. It's removed, since nothing used it.
- The four transition tables were variable-length arrays, which aren't standard C++. They're now `vector<vector<int>>`.
- `user_Choice` returns on every path, and the generator object is no longer leaked.

Checked with scripted sessions for all seven language types (starts with, ends with, contains at most / at least / exactly k, odd and even counts).
