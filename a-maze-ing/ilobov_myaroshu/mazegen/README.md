*This project has been created as part of the 42 curriculum by ilobov, myaroshu*

# mazegen

Reusable Python package for maze generation used in the **A-Maze-ing** project.

## Description

`mazegen` provides a standalone `MazeGenerator` class that can be imported in other projects.

Main features:
- Random maze generation with configurable `width`, `height`
- Optional deterministic generation via `seed`
- Support for perfect / non-perfect mazes
- Access to generated maze structure (cells, walls, entry, exit)
- Access to a valid shortest path (see usage below)

---

## Installation

### From source (development)

```bash
python3 -m venv .venv
. .venv/bin/activate
python -m pip install --upgrade pip build
python -m build
python -m pip install dist/mazegen-*.whl
```

### Quick import test

```bash
python -c "from mazegen.maze_generator import MazeGenerator; print('ok')"
```

---

## Basic usage

```python
from mazegen.maze_generator import MazeGenerator

generator = MazeGenerator(width=20, height=15, seed=42)
maze = generator.generate(entry=(0, 0), exit=(19, 14), perfect=True)

print(maze.width, maze.height)
print(maze.entry, maze.exit)
print(maze.seed)  # if exposed by your Maze model
```

---

## Custom parameters

```python
from mazegen.maze_generator import MazeGenerator

# Reproducible generation
g1 = MazeGenerator(30, 20, seed=12345)
m1 = g1.generate(entry=(0, 0), exit=(29, 19), perfect=True)

# Non-perfect maze
g2 = MazeGenerator(30, 20, seed=12345)
m2 = g2.generate(entry=(0, 0), exit=(29, 19), perfect=False)
```

---

## Accessing generated structure

Typical structure access:

```python
cell = maze.grid[row][col]
print(cell.walls)    # dict with N/E/S/W wall states
print(cell.blocked)  # True/False if blocked cells are used
```

---

## Accessing a solution (shortest path)

```python
from mazegen.maze_generator import MazeGenerator
from mazegen.maze_solver import MazeSolver

gen = MazeGenerator(width=20, height=15, seed=42)
maze = gen.generate(entry=(0, 0), exit=(19, 14), perfect=True)

solver = MazeSolver(maze)
path = solver.shortest_path()
print(path)  # e.g. "EESSNNW..."
```

---

## Notes

- Same `(width, height, entry, exit, perfect, seed)` => same maze (deterministic).
- Different seed => different maze.
- Coordinates are expected as `(x, y)`.
- Keep borders and wall coherence consistent between neighboring cells.