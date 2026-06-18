from dataclasses import dataclass


@dataclass
class MazeConfig:
    """Configuration parameters for maze generation.

    Attributes:
        width: Maze width in cells.
        height: Maze height in cells.
        entry: Entry coordinates as (x, y).
        exit: Exit coordinates as (x, y).
        output_file: Path to output file for maze data.
        perfect: If True, generate perfect maze. If False, add cycles.
        seed: Optional seed for reproducible generation.
    """
    width: int
    height: int
    entry: tuple[int, int]
    exit: tuple[int, int]
    output_file: str
    perfect: bool
    seed: int | None = None
