from dataclasses import dataclass
from .cell import Cell


@dataclass
class Maze:
    """Represents a generated maze.

    Attributes:
        width: Width of the maze in cells.
        height: Height of the maze in cells.
        grid: 2D grid of Cell objects.
        entry: Entry coordinates as (x, y).
        exit: Exit coordinates as (x, y).
        seed: Optional seed used for reproducible generation.
    """
    width: int
    height: int
    grid: list[list[Cell]]
    entry: tuple[int, int]
    exit: tuple[int, int]
    seed: int | None = None
