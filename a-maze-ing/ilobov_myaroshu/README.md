*This project has been created as part of the 42 curriculum by ilobov, myaroshu.*

# A-Maze-ing

## Description

A-Maze-ing is a Python project that generates mazes from a simple configuration
file, computes the shortest path between an entry and an exit, writes the maze
to an output file using the hexadecimal wall encoding specified in the subject,
and provides an interactive terminal visualization (via `curses`). The project
supports both perfect mazes (a single path between any two cells) and
non-perfect mazes (with additional loops), and allows reproducible generation
via an optional `SEED` parameter.

This repository contains two parts:

- the application layer (`src/`) that implements CLI parsing, file writer,
	visualization and glue code;
- the reusable core (`mazegen/`) that provides `MazeGenerator`, `MazeSolver`,
	and the basic models (`Cell`, `Maze`, pattern utilities) suitable for
	publishing as a Python package.

---

## Features

- Generate perfect and non-perfect mazes of arbitrary dimensions.
- Optional deterministic generation through `SEED`.
- Embed a visual "42" pattern in the maze as required by the subject.
- Compute shortest path (BFS) and export it together with the maze.
- Export maze in the required hex format (one hex digit per cell).
- Interactive terminal visualization with keyboard controls.

---

## Instructions

### 1) Requirements

- Python 3.10+
- A POSIX terminal (Linux/macOS/WSL) for `curses` visualization

### 2) Installation

Fast setup via `Makefile`:

```bash
make install
```

Manual setup (equivalent):

```bash
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
```

### 3) Execution

Main script usage:

```bash
python3 a_maze_ing.py <config.txt>
```

Example with the default config:

```bash
python3 a_maze_ing.py config.txt
```

Or via `Makefile` target:

```bash
make run
```

What happens during execution:

1. Config is parsed and validated.
2. Maze is generated.
3. Shortest path is solved (BFS).
4. Output file is written in the required format.
5. Interactive visualizer is launched.


### 4) Debugging and quality checks

Run with debugger:

```bash
make debug
```

Run static analysis:

```bash
.venv/bin/mypy .
.venv/bin/flake8 . --exclude=.venv
```

Or use the bundled target:

```bash
make lint
```

### 5) Build and packaging

Build source distribution and wheel:

```bash
make build
```

Install built wheel locally:

```bash
pip install dist/mazegen-*.whl
```

### 6) Cleanup

Remove caches:

```bash
make clean
```

Remove caches and build artifacts (`dist/`, `build/`, `*.egg-info`):

```bash
make fclean
```

### 7) Common issues

- If installation fails, recreate the environment:

```bash
rm -rf .venv
make install
```

## Reusable code and packaging

The core generator and solver are implemented in the `mazegen/` package which
is structured to be pip-installable. The intended
reusable surface:

`mazegen.maze_generator.MazeGenerator(width, height, seed=None)` — create
	generator instance and call `.generate(entry, exit, perfect)` to obtain a
	`Maze` object.
`mazegen.maze_solver.MazeSolver(maze).shortest_path()` — returns the
	shortest path as `N/E/S/W` string.

The CLI-specific code (`src/ConfigParser.py`, `src/MazeWriter.py`,
`src/MazeVisualizer.py`) remains in `src/` and is not required for the
package installation, keeping the package minimal and focused.

To build locally:

```bash
make build
```

Install the generated wheel in a venv for testing:

```bash
python -m pip install dist/mazegen-*.whl
```

## Interactive visualization

The project ships a `MazeVisualizer` that uses `curses` to draw the maze using
ASCII characters and colors. Keyboard controls:

- `R` — regenerate a new maze
- `P` — toggle shortest path overlay
- `C` — cycle wall color palettes
- Arrow keys / `WASD` — move the player through open passages
- `Q` — quit

The visualizer highlights the player (`@`), entry (`S`), exit (`E`) and path
(`o`) when enabled. Reaching the exit shows a prompt to regenerate with `R`
or quit with `Q`, including a prominent `EXIT REACHED!` banner.

---

## Resources
- YouTube playlist - Python Curses module tutorial: https://www.youtube.com/watch?v=Db4oc8qc9RU
-  Python Curses: https://docs.python.org/3/howto/curses.html
- YouTube - Maze Generation Algorithm: https://www.youtube.com/watch?v=ioUl1M77hww&pp=ygUObWF6ZSBnZW5lcmF0b3I%3D
- YouTube - Maze Generation Algorithm on Python: https://www.youtube.com/watch?v=jZQ31-4_8KM&t=392s&pp=ygUObWF6ZSBnZW5lcmF0b3I%3D
- Python dataclasses: https://docs.python.org/3/library/dataclasses.html
- DFS (Deep First Search) algorithm: https://www.geeksforgeeks.org/dsa/depth-first-search-or-dfs-for-a-graph/
- Depth First Search in Python (with Code) | DFS Algorithm - https://favtutor.com/blogs/depth-first-search-python
- DFS with stack: www.datacamp.com/tutorial/depth-first-search-in-python
                  https://dev.to/shahrouzlogs/day-64-python-depth-first-search-dfs-on-tree-stack-based-iterative-traversal-for-deep-4gej
- Breadth-First Search (BFS): https://www.geeksforgeeks.org/dsa/breadth-first-search-or-bfs-for-a-graph/
- How to implement a ​breadth-first search in Python: https://www.educative.io/answers/how-to-implement-a-breadth-first-search-in-python
- Maze Generator: https://inventwithpython.com/recursion/chapter11.html
- Python’s Path Through Mazes: A Journey of Creation and Solution: https://medium.com/@msgold/using-python-to-create-and-solve-mazes-672285723c96
- Mazes: https://reeborg.ca/docs/en/reference/mazes.html

## How AI was used

AI was used in several stages of our project and served mainly as a learning, support, and problem-solving tool throughout the development process.

First of all, AI helped us better understand the theoretical foundations that were necessary for the project. In particular, it was used to explain the DFS (Depth-First Search) and BFS (Breadth-First Search) algorithms. In addition to explaining how these algorithms work, AI also demonstrated other common algorithms used for working with graphs and grid-based structures. This allowed us to compare different approaches and consciously choose the algorithms that best suited our task. AI also helped us understand the concept of graphs in general - what they are, how they are structured (vertices, edges, connectivity), and how typical graph traversal and pathfinding algorithms operate. This theoretical background made it easier for us to design and implement our maze generation logic.

Another important area where AI was helpful was improving our workflow and collaboration. With its help, we strengthened our skills in working with Git, which significantly simplified teamwork. Before actively starting development, we spent time learning how to properly organize our work with branches, how to switch between them, how to merge changes, and how to structure commits. AI also helped explain the purpose of tags, the logic behind branching strategies, and the typical workflow used in collaborative development. In addition, we learned how to resolve common merge conflicts and how to roll back changes when something went wrong. These skills turned out to be very valuable during the development process and helped us avoid losing important work.

AI was also useful when we encountered technical issues that were not immediately obvious. For example, during collaborative development we ran into an indentation problem caused by different formatting styles. One developer used tab indentation while another used four spaces. As a result, the codebase ended up containing a mixture of both styles, which caused formatting inconsistencies and indentation errors that were difficult to diagnose at first. AI helped us identify the root cause of the issue and explained why mixing tabs and spaces can lead to such problems, as well as how to standardize formatting across the project.

As the project grew larger and more complex, AI also helped us think about software architecture and best development practices. Our project eventually consisted of several separate components, such as ConfigParser, MazeGenerator, and MazeVisualizer. At that stage we faced an important architectural question: how data should be passed between these components. In an early version of the project, components accessed each other directly, often retrieving data through methods such as get(). While this approach worked initially, it created tight coupling between modules and made the code harder to maintain and extend. AI suggested using the DTO (Data Transfer Object) concept as a more structured way of transferring data between components. Following this idea, we introduced new data structures based on Python dataclass objects that stored parsed or generated data. This approach made the architecture cleaner, reduced dependencies between modules, and simplified further development.

AI was also helpful when working with development tools and static analysis utilities. For example, we used mypy for static type checking, and sometimes it produced errors or warnings that were not immediately clear to us. AI helped interpret these messages, explain the underlying type-checking logic, and suggest ways to fix the issues.

In addition, AI supported us while learning new development tools. For instance, it helped us understand how to use the Python debugger, which allowed us to step through the code, inspect variables, and better understand how the program behaves during execution. This significantly improved our ability to debug complex parts of the project.

Finally, AI also assisted us in troubleshooting specific implementation issues. For example, when we attempted to integrate a visual “42” pattern into the maze generator, we encountered a problem where the pattern was not visible in the final maze. After investigation, it turned out that the maze generation algorithm was unintentionally overwriting the pattern during its execution. AI helped us analyze the problem and guided us toward identifying the part of the code responsible for this behavior.

Overall, AI acted as a supportive tool throughout the project. It helped us deepen our understanding of algorithms and data structures, improve our development workflow, adopt better architectural practices, and efficiently solve technical problems that arose during implementation.

---

## The complete structure and format of the config file


### Project structure

```
A-Maze-ing/
├── a_maze_ing.py              — application entry point
├── config.txt                 — example configuration file
├── Makefile                   — build and run targets (install, run, lint, build, clean)
├── pyproject.toml             — package metadata for mazegen
├── requirements.txt           — Python dependencies (mypy, flake8)
├── README.md                  — this file
│
├── src/                       — application-specific code
│   ├── ConfigParser.py        — parses and validates config.txt
│   ├── MazeGenerator.py       — maze generation orchestration
│   ├── MazeSolver.py          — BFS shortest path solver
│   ├── MazeWriter.py          — writes maze to output file (hex format)
│   ├── MazeVisualizer.py      — interactive terminal UI (curses)
│   ├── MazeValidator.py       — validates maze structure
│   │
│   └── models/                — internal dataclasses and constants
│       ├── Maze.py            — main Maze data structure
│       ├── MazeConfig.py      — parsed configuration holder
│       ├── Cell.py            — individual maze cell model
│       ├── Pattern.py         — "42" pattern logic
│       ├── direction_constants.py  — N/E/S/W deltas
│       └── pattern_constants.py    — pattern dimensions
│
└── src/mazegen/               — reusable Python package
    ├── __init__.py
    ├── generator.py           — MazeGenerator (reproducible via seed)
    ├── solver.py              — MazeSolver (BFS for shortest path)
    ├── cell.py                — Cell model with wall encoding
    ├── maze.py                — Maze model with regenerate()
    ├── pattern_42.py          — pattern application logic
    └── constants.py           — shared constants (directions, patterns)
```

**Key files:**
- `a_maze_ing.py` — main entry point; orchestrates config → generation → solve → visualize
- `src/` — CLI-specific code (parsing, I/O, UI); **not** part of the reusable package
- `src/mazegen/` — reusable core library; can be installed as `pip install dist/mazegen-*.whl`



### Configuration file format

The configuration file is a plain text file containing one `KEY=VALUE` pair per
line. Lines starting with `#` are treated as comments and ignored. Inline
comments after a `#` on a line are also ignored.

Required keys:

- `WIDTH` — maze width in cells (positive integer)
- `HEIGHT` — maze height in cells (positive integer)
- `ENTRY` — entry coordinates as `x,y` (zero-based)
- `EXIT` — exit coordinates as `x,y` (zero-based)
- `OUTPUT_FILE` — path where the output file will be written
- `PERFECT` — `True` or `False` (generate perfect maze if True)

Optional keys:

- `SEED` — non-negative integer seed for reproducible generation. If omitted,
	generation is non-deterministic.

Example `config.txt`:

```ini
# Basic example
WIDTH=30
HEIGHT=20
ENTRY=0,0
EXIT=16,15
OUTPUT_FILE=maze.txt
PERFECT=True
SEED=42
```


## Output file format

The output file (`OUTPUT_FILE`) follows the subject specification:

1. A rectangular grid: one line per row, each character is a single
	 hexadecimal digit encoding the closed walls for that cell (N/E/S/W
	 mapped to bits 0..3 respectively).
2. A blank line.
3. The entry coordinates as `x,y` on a single line.
4. The exit coordinates as `x,y` on a single line.
5. The shortest path from entry to exit as a contiguous string of letters
	 `N`, `E`, `S`, `W` followed by a newline.

Wall bit mapping for each cell (LSB = bit 0):

- bit 0 (1): North closed
- bit 1 (2): East closed
- bit 2 (4): South closed
- bit 3 (8): West closed

Example (conceptual): a cell with North and East walls closed has bits `0b0011` = `3`.

---

## Maze generation algorithm chose

Chosen algorithm: Recursive Backtracker (depth-first search with an explicit
stack). Implementation outline:

1. Start from the entry cell.
2. Repeatedly choose a random unvisited neighbor, knock down the wall between
	 the cells, and push the new cell onto the stack.
3. If the current cell has no unvisited neighbors, pop from the stack (backtrack).
4. Continue until the stack is empty.

For `PERFECT=False` the implementation collects candidate walls and opens a
small percentage of them (configurable constant) to create loops.

### Why this algorithm?

- **Simple and compact to implement.** The Recursive Backtracker is one of the
	most straightforward maze generation algorithms to code. It requires only a
	stack data structure and basic grid traversal logic, making it ideal for
	learning and understanding maze generation concepts without excessive
	complexity.

- **Provides good maze aesthetics for typical sizes used in the project.**
	Unlike some other algorithms (e.g., Prims or Kruskal's), the Recursive
	Backtracker naturally produces mazes with long, winding corridors and
	relatively few branching points. This creates visually appealing mazes
	that feel more like traditional hand-drawn mazes, which is desirable for
	interactive visualization.

## Reusable code

The project is structured with **separation of concerns** in mind: application-specific
code (CLI, I/O, visualization) lives in `src/`, while the core generation and solving
logic is packaged in `mazegen/` for reuse in other projects.

### What is reusable?

The `mazegen/` package contains the fundamental maze operations:

- **`MazeGenerator`** — Generates mazes using the Recursive Backtracker algorithm.
	Takes width, height, optional seed, and produces a `Maze` object. Supports both
	perfect (single path between any two cells) and non-perfect (with loops) modes.
	Example usage:

	```python
	from mazegen.maze_generator import MazeGenerator
	
	gen = MazeGenerator(width=30, height=20, seed=42)
	maze = gen.generate(entry=(0, 0), exit=(15, 10), perfect=True)
	```

- **`MazeSolver`** — Finds the shortest path between two points using BFS.
	Returns the path as a string of cardinal directions (`N`, `E`, `S`, `W`).
	Raises `ValueError` if no path exists.
	Example usage:

	```python
	from mazegen.maze_solver import MazeSolver
	
	solver = MazeSolver(maze)
	path = solver.shortest_path()  # Returns e.g., "EESSNWW"
	```

- **`Maze` dataclass** — A container holding the grid, dimensions, entry/exit points,
	and seed. The `regenerate()` method allows creating a new maze with an incremented
	seed while keeping other parameters.

- **`Cell` model** — Represents individual grid cells with wall state and a `to_bits()`
	method that encodes walls as a 4-bit integer (matching the assignment specification).

- **Pattern utilities** — Logic for embedding the "42" pattern in the maze.

### What is application-specific?

The `src/` directory contains code tied to the CLI and assignment requirements:

- **`ConfigParser.py`** — Parses the `config.txt` file with validation. Not reusable
	outside this specific assignment format.

- **`MazeWriter.py`** — Writes maze data to a file in the hex format specified by
	the subject. Reusable if you need that specific output format.

- **`MazeVisualizer.py`** — Interactive terminal UI using `curses`. Specific to this
	project's interactive experience.

- **`a_maze_ing.py`** — Application entry point; orchestrates the entire workflow
	(config → generate → solve → visualize → export).

### How to reuse `mazegen/`

Install the `mazegen` package in your own project:

```bash
# Build the wheel
python3 -m build

# Install in a new environment
pip install dist/mazegen-*.whl

# In your code:
from mazegen.maze_generator import MazeGenerator
from mazegen.maze_solver import MazeSolver

gen = MazeGenerator(50, 40, seed=123)
maze = gen.generate(entry=(0, 0), exit=(25, 20), perfect=False)
path = MazeSolver(maze).shortest_path()

# Access maze data
print(f"Maze: {maze.width}x{maze.height}")
print(f"Grid: {maze.grid}")
print(f"Path: {path}")
```

This separation makes it easy to build different applications (games, visual editors,
analysis tools, etc.) on top of the same core maze logic without inheriting CLI
baggage.

## Team and priject management

### Planning and evolution

We initially planned a simple linear pipeline (parse → generate → output), but as
the project grew we introduced a proper architecture with separated models, a
reusable `mazegen` package, and an interactive visualizer — all of which emerged
iteratively rather than being planned upfront.

### What worked well and what could be improved

Git branching and regular commits made parallel work straightforward and kept the
history clean, which was the main thing that worked well. On the other hand, we
underestimated the time needed for edge-case validation (e.g., oversized maze
inputs crashing the generator), and adding proper input guards earlier would have
saved debugging time later.

### Tools used

**mypy** and **flake8** were used for static analysis,
**Python debugger (pdb / VS Code debugger)** for stepping through generation logic.

### Team roles

- `ilobov` — CLI, `ConfigParser`, `MazeSolver`, visualizer `MazeVisualizer` and UX , integration,
	documentation and packaging.
- `myaroshu` — core generation code, pattern handling (42),  `MazeGenerator`, `MazeWriter`.
