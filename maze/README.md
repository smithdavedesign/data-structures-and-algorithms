# Maze

A terminal maze game. Each maze is generated with **recursive division**: `Divide()` splits the area with a wall, leaves a random gap, and recurses into both halves. You move `O` with `w a s d` to reach the treasure `$`.

Project 3.

```sh
make && ./maze
```

**Changed in 2026:** the stubbed assignment operator returns `*this`, as every `operator=` must.
