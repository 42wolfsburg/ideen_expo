from .direction_constants import DIRECTIONS


class Cell:
    """Represents a single cell in the maze grid.

    Stores cell position, wall states, and metadata for maze generation.
    """

    def __init__(self, row: int, col: int) -> None:
        """Initialize a maze cell.

        Args:
            row: Row coordinate in the grid.
            col: Column coordinate in the grid.
        """
        self.row = row
        self.col = col
        self.walls = {"N": True, "S": True, "E": True, "W": True}
        self.visited: bool = False
        self.blocked: bool = False
        self.is_pattern: bool = False

    def remove_wall(self, direction: str) -> None:
        """Remove wall in specified direction.

        Args:
            direction: Direction ('N', 'S', 'E', or 'W').

        Raises:
            ValueError: If direction is invalid.
        """
        if direction not in DIRECTIONS:
            raise ValueError(
                f"Invalid direction {direction}." f"MUST BE ONE OF {DIRECTIONS}"  # noqa: E501
            )
        self.walls[direction] = False

    def has_wall(self, direction: str) -> bool:
        """Check if wall exists in specified direction.

        Args:
            direction: Direction ('N', 'S', 'E', or 'W').

        Returns:
            bool: True if wall exists, False otherwise.

        Raises:
            ValueError: If direction is invalid.
        """
        if direction not in DIRECTIONS:
            raise ValueError(
                f"Invalid direction {direction}. " f"MUST BE ONE OF {DIRECTIONS}"  # noqa: E501
            )
        return self.walls[direction]

    def to_bits(self) -> int:
        """Convert cell walls to hexadecimal representation.

        Bit mapping:
            Bit 0 (LSB): North wall
            Bit 1: East wall
            Bit 2: South wall
            Bit 3: West wall

        Returns:
            int: Wall configuration as integer (0-15).
        """
        result = 0
        if self.walls["N"]:
            result |= 1
        if self.walls["E"]:
            result |= 2
        if self.walls["S"]:
            result |= 4
        if self.walls["W"]:
            result |= 8
        return result
