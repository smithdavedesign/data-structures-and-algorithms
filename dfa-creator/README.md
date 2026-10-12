# DFA creator

Builds a deterministic finite automaton at run time from your description of a regular language: strings that start with, end with or contain a substring, or contain it at most, at least or exactly k times, or an odd or even number of times. It prints the transition table, then tests any strings you type against it. The DFA is a 2-D transition array.

CS 454 (theory of computation), August 2016.

```sh
make && ./dfa-creator    # then follow the prompts
```

**Changed in 2026:** `user_Choice` returns on every path (one fell off the end of the function).
