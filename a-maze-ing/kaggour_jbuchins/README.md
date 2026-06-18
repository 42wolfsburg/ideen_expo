*This project has been created as part of the 42 curriculum by jbuchins and kaggour*

---
# A-Maze-ing
---

## Description

A-Maze-ing is a Python maze generator and solver. Given a configuration file, it
generates a random maze, displays it in the terminal using Unicode block characters
and ANSI colours, solves it with BFS, and writes the result to an output file. The
project is built around a reusable `mazegen` package that can be installed via pip
and imported into any Python project.

Key features:
- Perfect and imperfect maze generation
- Two algorithms: Growing Tree and Wilson's
- Terminal rendering with coloured walls, entry/exit highlights, and solution path overlay
- Interactive menu: regenerate, toggle solution path, rotate colour palette, toggle animation, change algorithm, change seed
- BFS-based solver returning the shortest path as a direction string (`N`, `E`, `S`, `W`)
- Embedded "42" logo made of fully closed cells, centred in the maze

---

## Instructions

### Requirements

- Python 3.10 or later
- Dependencies listed in `mazegen-pkg/pyproject.toml`

### Installation

```bash
make install
```

This installs `flake8` and `mypy` for development linting.

To install the `mazegen` package itself from the pre-built wheel:

```bash
pip install mazegen-pkg/dist/mazegen-1.0.0-py3-none-any.whl
```

### Run

```bash
make run
# or directly:
python3 a_maze_ing.py config.txt
```

### Debug

```bash
make debug
```

### Lint

```bash
make lint
```

Runs `flake8 .` and `mypy` with the flags required by the subject.

### Clean

```bash
make clean
```

Removes `__pycache__`, `.mypy_cache`, and other temporary files.

---

## Interactive Menu

After generating the initial maze, the program displays an interactive menu with the following options:

| Choice | Description |
|---|---|
| 1 | Re-generate a new maze |
| 2 | Show/Hide solution path |
| 3 | Rotate maze wall colour |
| 4 | Enable/Disable animation |
| 5 | Change Algorithm (toggle between Growing Tree and Wilson's) |
| 6 | Change Seed (set a custom seed for reproducibility) |
| 7 | Prompt for a movement key |
| 8 | Quit |

You can also press `WASD` or the arrow keys directly at the menu prompt to move
without pressing Enter.

When the player reaches the exit, the program prints a prominent
`EXIT REACHED!` banner.
Use option `1` to regenerate a new maze or option `8` to quit.

---

## Configuration File Format

The configuration file uses `KEY=VALUE` pairs, one per line.
Lines starting with `#` are treated as comments and ignored.

| Key | Required | Description | Example |
|---|---|---|---|
| `WIDTH` | Yes | Maze width in cells | `WIDTH=20` |
| `HEIGHT` | Yes | Maze height in cells | `HEIGHT=15` |
| `ENTRY` | Yes | Entry coordinates `x,y` | `ENTRY=0,0` |
| `EXIT` | Yes | Exit coordinates `x,y` | `EXIT=19,14` |
| `OUTPUT_FILE` | Yes | Path to write the output file | `OUTPUT_FILE=maze.txt` |
| `PERFECT` | Yes | Generate a perfect maze (`True`/`False`) | `PERFECT=True` |
| `SEED` | No | Integer seed for reproducibility | `SEED=4242` |
| `ALGORITHM` | No | `growingtree` (default) or `wilson` | `ALGORITHM=growingtree` |

A default `config.txt` is provided at the root of the repository.

### Example

```
WIDTH=20
HEIGHT=15
ENTRY=0,0
EXIT=19,14
OUTPUT_FILE=maze.txt
PERFECT=True
SEED=4242
ALGORITHM=growingtree
```

---

## Output File Format

The output file contains one hexadecimal digit per cell, row by row.
Each digit encodes which walls are closed as a 4-bit bitmask:

| Bit | Direction |
|---|---|
| 0 (LSB) | North |
| 1 | East |
| 2 | South |
| 3 | West |

A set bit (`1`) means the wall is closed; a clear bit (`0`) means it is open.

After the grid rows, a blank line separates the footer, which contains three lines:
1. Entry coordinates (`x,y`)
2. Exit coordinates (`x,y`)
3. Shortest path from entry to exit as a sequence of `N`, `E`, `S`, `W` characters

---

## Maze Generation Algorithm

Two algorithms are implemented, selectable via the `ALGORITHM` config key.

### Growing Tree (default)

The Growing Tree algorithm maintains a list of visited cells and iteratively carves
passages to unvisited neighbours. The next cell to expand from is chosen at random,
which produces mazes with a mix of winding corridors and short dead-ends. It is
fast, memory-efficient, and easy to animate step by step.

We chose it as the default because it produces visually balanced mazes and its
burst-based stepping makes animation natural to implement.

### Wilson's Algorithm

Wilson's algorithm uses loop-erased random walks. Starting from a random unvisited
cell, it walks randomly until it hits the maze, erasing any loops formed along the
way, then carves the resulting path. This guarantees a **uniformly random spanning
tree**: every possible perfect maze is equally likely. It tends to produce mazes with
many short dead-ends and a very different visual texture from Growing Tree.

We included it as a bonus algorithm because it demonstrates a fundamentally
different approach to randomness in maze generation.

---

## Reusable Module

The `mazegen` package (located in `mazegen-pkg/`) is the reusable component of
this project. It can be installed independently via pip and imported into any
Python project.

### What is reusable

| Class / Symbol | Description |
|---|---|
| `Gen` | High-level facade — instantiate this to generate and render a maze |
| `Maze` | Core data model (grid, entry, exit, plugin registry) |
| `Grid` | 2-D bitmask grid with `carve`, `add_wall`, `clear_wall` |
| `Renderer` | Terminal renderer using Unicode block characters and ANSI colours |
| `GeneratorPlugin` | Abstract base class for custom generation algorithms |
| `GrowingTreePlugin` | Growing Tree algorithm implementation |
| `WilsonPlugin` | Wilson's algorithm implementation |
| `MazeSolver` | BFS solver; also reads maze output files via `from_output_file` |
| `MazeConfig` / `parse_config_file` | Config file parser and validated data model |

### Quick start

```python
from mazegen import Gen, MazeSolver

# Create and generate a 20x15 perfect maze
gen = Gen(width=20, height=15, seed=4242)
for _ in gen.generate():
    pass  # consume the generator to complete generation

# Access the raw grid
grid = gen.maze  # List[List[int]]

# Solve it
solver = MazeSolver(grid, entry=(0, 0), exit_point=(19, 14))
path = solver.solve()  # e.g. "SSSEEENNN..."
print(f"Shortest path ({len(path)} moves): {path}")

# Print to terminal
gen.print_maze(solution_path=path, show_path=True)
```

### Custom parameters

```python
# Imperfect maze with Wilson's algorithm
gen = Gen(
    width=30,
    height=20,
    seed=1234,
    perfect=False,
    algorithm="wilson",
)
```

### Install from wheel

```bash
pip install mazegen-pkg/dist/mazegen-1.0.0-py3-none-any.whl
```

### Rebuild from source

```bash
cd mazegen-pkg
pip install build
python -m build --wheel
# output: dist/mazegen-1.0.0-py3-none-any.whl
```

---

## Team and Project Management

### Roles

- **jbuchins:** Generator Base: Point/ Grid/ Maze Class - Generator Plugin, GrowingTreePlugin and Renderer Plugin
- **kaggour:** WilsonPlugin - Gen Class - Configuration file parsing - Solver - A_Maze_Ing entry point - Makefile    

### Planning

Initial planning split the project into four vertical slices: grid model → generation →
rendering → solver/I/O. In practice, the rendering and solver work overlapped with
integration earlier than expected, which required several rounds of type-hint fixes once
mypy was applied to the full codebase.

### What worked well

- The plugin architecture (`GeneratorPlugin`) made adding Wilson's algorithm
  straightforward without touching the core grid code.
- Keeping `Grid` as a pure data structure with explicit `carve`/`add_wall`/`clear_wall`
  methods made it easy to reason about correctness.
- BFS in the solver is simple, correct by construction, and easy to test.

---

## Resources

- [Maze generation algorithms — Wikipedia](https://en.wikipedia.org/wiki/Maze_generation_algorithm)
- [Jamis Buck — Mazes for Programmers](http://www.mazesforprogrammers.com/) — the
  definitive reference for Growing Tree, Wilson's, and many other algorithms
- [Wilson's algorithm — original paper](https://dl.acm.org/doi/10.1145/237814.237880)
- [Python `typing` module documentation](https://docs.python.org/3/library/typing.html)
- [mypy documentation](https://mypy.readthedocs.io/)
- [PEP 257 — Docstring conventions](https://peps.python.org/pep-0257/)
- [Python packaging guide — pyproject.toml](https://packaging.python.org/en/latest/guides/writing-pyproject-toml/)

### AI usage

Claude was used to assist with the following parts of the project:
- Fixing docstrings for classes and functions (we reviewed and adjusted all of them)
- Fixing mypy type errors after the codebase was assembled
- Wrapping long lines to comply with flake8's 79-character limit

In all cases the generated content was read, understood, and validated by the team
before being committed. No logic or algorithm was generated by AI.
