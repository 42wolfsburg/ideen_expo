from .direction_constants import DIRECTION_DELTAS
from .maze import Maze


class MazeSolver:
    """Solves a maze by finding the shortest path from entry to exit.

    Uses breadth-first search (BFS) to find the shortest path in the maze grid.
    """

    def __init__(self, maze: Maze) -> None:
        """Initialize MazeSolver with a maze.

        Args:
            maze: The maze to solve.
        """
        self.maze = maze

    def shortest_path(self) -> str:
        """Find the shortest path from maze entry to exit.

        Returns:
            str: Path as a string of directions (N/E/S/W).

        Raises:
            ValueError: If no valid path exists from entry to exit.
        """
        start = self.maze.entry
        end = self.maze.exit

        # Queue used for BFS traversal
        queue: list[tuple[int, int]] = [start]
        queue_index = 0

        # Set of visited cells
        visited = {start}

        # Maps cell -> (previous_cell, direction_taken)
        parent: dict[tuple[int, int], tuple[tuple[int, int], str]] = {}

        while queue_index < len(queue):
            row, col = queue[queue_index]
            queue_index += 1

            # Stop if we reached the exit
            if (row, col) == end:
                break

            cell = self.maze.grid[row][col]

            # Explore neighbors
            for direction, (d_row, d_col) in DIRECTION_DELTAS.items():
                if cell.walls[direction]:
                    continue

                next_row = row + d_row
                next_col = col + d_col
                next_cell = (next_row, next_col)

                # Skip cells outside the maze
                if not (0 <= next_row < self.maze.height and 0 <= next_col < self.maze.width):  # noqa: E501
                    continue

                # Skip visited cells
                if next_cell in visited:
                    continue

                # Skip blocked cells
                if getattr(self.maze.grid[next_row][next_col], "blocked", False):  # noqa: E501
                    continue

                visited.add(next_cell)
                parent[next_cell] = ((row, col), direction)
                queue.append(next_cell)

        # If exit wasn't reached
        if end not in visited:
            raise ValueError(
                f"No valid path from entry {self.maze.entry} to exit {self.maze.exit}."  # noqa: E501
            )

        # Reconstruct path from exit to start
        path: list[str] = []
        current_cell = end

        while current_cell != start:
            previous_cell, direction = parent[current_cell]
            path.append(direction)
            current_cell = previous_cell

        path.reverse()
        return "".join(path)
