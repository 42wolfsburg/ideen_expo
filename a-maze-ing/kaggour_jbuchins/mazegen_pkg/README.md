# mazegen

Reusable Python package for maze generation, solving, and terminal rendering.
Extracted from the A-Maze-ing 42 project.

---

## Contents

```
mazegen-pkg/
├── pyproject.toml
├── README.md               ← this file
├── mazegen/
│   ├── __init__.py
│   ├── generator.py        ← Gen, Maze, Grid, Renderer, plugins
│   ├── solver.py           ← MazeSolver
│   └── config.py           ← MazeConfig, parse_config_file
└── dist/
    └── mazegen-1.0.0-py3-none-any.whl
```

---

## Install

From the pre-built wheel:

```bash
pip install dist/mazegen-1.0.0-py3-none-any.whl
```

Rebuild from source:

```bash
pip install build
python -m build --wheel
```

---

## Quick start

```python
from mazegen import Gen, MazeSolver

# Generate a 20x15 perfect maze
gen = Gen(width=20, height=15, seed=4242)
for _ in gen.generate():
    pass

# Solve it
solver = MazeSolver(gen.maze, entry=(0, 0), exit_point=(19, 14))
path = solver.solve()
print(f"Path ({len(path)} moves): {path}")

# Render to terminal (with solution overlay)
gen.print_maze(solution_path=path, show_path=True)
```

---

## Key classes

| Class | Module | Purpose |
|---|---|---|
| `Gen` | `generator` | High-level facade: generate, render, animate |
| `MazeSolver` | `solver` | BFS solver; also parses output files |
| `MazeConfig` | `config` | Validated config data model |
| `parse_config_file` | `config` | Parse a `.txt` config file into `MazeConfig` |
| `GrowingTreePlugin` | `generator` | Growing Tree algorithm |
| `WilsonPlugin` | `generator` | Wilson's loop-erased random walk |
| `GeneratorPlugin` | `generator` | Abstract base for custom algorithms |

---

## Parameters

```python
Gen(
    width=20,           # maze width in cells
    height=15,          # maze height in cells
    entry=Point(0, 0),  # entry cell (default: top-left)
    exit_pt=Point(19, 14),  # exit cell (default: bottom-right)
    perfect=True,       # True = one unique path; False = loops allowed
    seed=4242,          # integer seed for reproducibility
    algorithm="growingtree",  # "growingtree" or "wilson"
)
```

---

## Requirements

- Python >= 3.10
- No third-party runtime dependencies (stdlib only)
