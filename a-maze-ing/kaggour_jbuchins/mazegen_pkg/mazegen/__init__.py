"""mazegen – maze generation, solving, and configuration package."""

__version__ = "1.0.0"
__author__ = "A-Maze-ing team"


# Core generation
from mazegen.generator import (
    Gen,
    Maze,
    Point,
    Grid,
    Renderer,
    GeneratorPlugin,
    GrowingTreePlugin,
    WilsonPlugin,
    COLOUR_PALETTES,
    DIGIT_42,
    NULL,
    N,
    E,
    S,
    W,
)

# Config parsing
from mazegen.config import (
    MazeConfig,
    ConfigError,
    parse_config_file,
    DEFAULT_SEED,
)

# Solver
from mazegen.solver import MazeSolver

__all__ = [
    # Generation
    "Gen",
    "Maze",
    "Point",
    "Grid",
    "Renderer",
    "GeneratorPlugin",
    "GrowingTreePlugin",
    "WilsonPlugin",
    "COLOUR_PALETTES",
    "DIGIT_42",
    "NULL",
    "N",
    "E",
    "S",
    "W",
    # Config
    "MazeConfig",
    "ConfigError",
    "parse_config_file",
    "DEFAULT_SEED",
    # Solver
    "MazeSolver",
]
