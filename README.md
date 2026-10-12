# Data structures and algorithms (C++)

C++ data structures and algorithms from college (2012–2017), gathered from separate repos into one. Each folder builds on its own; git history from the original repos is kept.

| Folder | Topic |
|---|---|
| [linked-list](linked-list/) | singly linked list with the rule of three |
| [maze](maze/) | maze generation by recursive division |
| [vector-sort](vector-sort/) | sorting, and why floating-point summation order changes the result |
| [real-number-calculator](real-number-calculator/) | arbitrary-precision decimals as digit vectors |
| [large-number-calculator](large-number-calculator/) | big-integer add and subtract, exponentiation by squaring |
| [dfa-creator](dfa-creator/) | building a DFA (transition table) from a language description |

Intro programs from the same years are in [cpp-coursework](https://github.com/smithdavedesign/cpp-coursework). The compiler-construction project (lexical and syntactic analysis of Scheme) is in [SyntacticalAnalyzer](https://github.com/smithdavedesign/SyntacticalAnalyzer). For an interactive take on algorithms, see [algorithms-docs](https://github.com/smithdavedesign/algorithms-docs).

## Build

Any C++17 compiler (g++ or clang++) and `make`:

```sh
make          # builds every program into its own folder
make clean
```

CI builds everything with gcc on every push.

## History

These used to be separate repos, now archived: LinkedLists-C-, Recursive-made-Maze-Game, vector-sort, Real-Number-Calculator, exponential-Large-Number-Calculator and DFA-Creator. In 2026 they were cleaned up: build junk removed, one Makefile each, no warnings under `-Wall -Wextra`. Each program was then run under AddressSanitizer and UndefinedBehaviorSanitizer. That found and fixed a list insert that reported failure, an exponentiation that never finished, an `=`/`==` mix-up, uninitialized flags, memory leaks, and a hang when input ends. The arbitrary-precision `Real` class turned out to be mostly broken and was rewritten; it's now checked against Python's exact `Decimal`. Each README says what changed.

CI builds with gcc and clang with warnings as errors. It also runs every program with sample input under the sanitizers (`smoke.sh`), so a memory error, undefined behavior or a leak fails the build.
