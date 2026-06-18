from src.models.direction_constants import DIRECTION_DELTAS
from src.models.Cell import Cell
from collections import deque


class MazeValidator:
    """Validates maze structure for consistency and correctness.

    Checks connectivity of the maze and ensures no large open areas exist.
    """

    def __init__(
        self,
        grid: list[list[Cell]],
        width: int,
        height: int
    ) -> None:
        """Initialize MazeValidator.

        Args:
            grid: 2D list of Cell objects.
            width: Width of the maze.
            height: Height of the maze.
        """
        self.grid = grid
        self.height = height
        self.width = width

    def is_connected(self) -> bool:
        """Check if the entire maze is connected (reachable from start).

        Returns:
            bool: True if all cells are reachable from the starting cell.
        """
        start = self.grid[0][0]
        visited = set()
        visited.add(start)
        queue = deque([start])
        while queue:
            current = queue.popleft()
            for direction, (dr, dc) in DIRECTION_DELTAS.items():
                if current.has_wall(direction) is True:
                    continue
                else:
                    new_row = current.row + dr
                    new_col = current.col + dc
                    if 0 <= new_row < self.height and 0 <= new_col < self.width:  # noqa: E501
                        neighbour = self.grid[new_row][new_col]
                        if neighbour not in visited:
                            visited.add(neighbour)
                            queue.append(neighbour)
        return len(visited) == self.width * self.height

    def no_opened_3x3(self) -> bool:
        """Check that no 3x3 area is completely open (no walls).

        Returns:
            bool: True if no fully open 3x3 zone exists.
        """
        for r in range(self.height - 2):
            for c in range(self.width - 2):
                open_zone = True
                for wr in range(r, r + 3):
                    for wc in range(c, c + 2):
                        if self.grid[wr][wc].has_wall("E"):
                            open_zone = False
                            break
                for wr in range(r, r + 2):
                    for wc in range(c, c + 3):
                        if self.grid[wr][wc].has_wall("S"):
                            open_zone = False
                            break
                if open_zone:
                    return False
        return True

    def is_valid(self) -> bool:
        """Check if maze is valid (connected and no large open areas).

        Returns:
            bool: True if maze meets all validity constraints.
        """
        return self.is_connected() and self.no_opened_3x3()
