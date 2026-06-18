from src.models.Cell import Cell
from src.models.pattern_constants import PATTERN_4, PATTERN_2


class Pattern:
    """Applies the '42' pattern to a maze grid.

    The pattern blocks specific cells to form the visual representation
    of the digits '4' and '2'.
    """

    def __init__(
        self,
        grid: list[list[Cell]],
        width: int,
        height: int
    ) -> None:
        """Initialize Pattern applier.

        Args:
            grid: 2D grid of Cell objects.
            width: Width of the maze.
            height: Height of the maze.
        """
        self.grid = grid
        self.width = width
        self.height = height

    def _close_cell(self, r: int, c: int) -> None:
        """Block a cell and synchronize walls with neighbors.

        Args:
            r: Row coordinate.
            c: Column coordinate.
        """
        # close all 4 walls of the pattern cell itself
        cell = self.grid[r][c]
        cell.walls = {"N": True, "S": True, "E": True, "W": True}
        cell.is_pattern = True
        cell.blocked = True

        # When we close a cell as part of a pattern_42, we mark it with a flag.
        # This is the only line where is_pattern becomes True.
        if c - 1 >= 0:
            self.grid[r][c - 1].walls["E"] = True  # ліво
        # render_ascii draws top boundary from top neighbour's S wall
        if r - 1 >= 0:
            self.grid[r - 1][c].walls["S"] = True  # верх
        if c + 1 < self.width:
            self.grid[r][c + 1].walls["W"] = True   # право
        if r + 1 < self.height:
            self.grid[r + 1][c].walls["N"] = True   # низ

    def apply(self, offset_row: int = 1, offset_col: int = 1) -> bool:
        """Apply the '42' pattern to the maze grid.

        Args:
            offset_row: Row offset for pattern placement.
            offset_col: Column offset for pattern placement.

        Returns:
            bool: True if pattern was applied successfully, False if maze
                  is too small.
        """
        min_height = offset_row + 5
        min_width = offset_col + 7  # 3 + 1 gap + 3

        if self.height < min_height or self.width < min_width:
            print("Warning: maze is too small to display '42' pattern")
            return False

        for row, col in PATTERN_4:
            r = offset_row + row
            c = offset_col + col
            if 0 <= r < self.height and 0 <= c < self.width:
                self._close_cell(r, c)

        for row, col in PATTERN_2:
            r = offset_row + row
            c = offset_col + 4 + col
            if 0 <= r < self.height and 0 <= c < self.width:
                self._close_cell(r, c)

        return True
