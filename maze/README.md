# Maze

A terminal maze game. Each maze is generated with **recursive division**: `Divide()` splits the area with a wall, leaves a random gap, and recurses into both halves. You move `O` with `w a s d` to reach the treasure `$`.

Project 3.

```sh
make && ./maze
```

**Changed in 2026:**
- The grid was never freed: one leak per game. `Maze` now follows the rule of three (destructor, deep copy constructor, deep assignment).
- Closing the input (Ctrl-D or a closed pipe) made the move loop spin forever. It now quits.
