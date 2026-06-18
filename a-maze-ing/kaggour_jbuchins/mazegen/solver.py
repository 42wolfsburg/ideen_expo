from typing import Dict, List, Optional, Tuple
import os

Point = Tuple[int, int]
Grid = List[List[int]]

NORTH = 1
EAST = 2
SOUTH = 4
WEST = 8

DIRECTIONS: List[Tuple[str, int, int, int]] = [
    ("N", 0, -1, NORTH),
    ("E", 1, 0, EAST),
    ("S", 0, 1, SOUTH),
    ("W", -1, 0, WEST),
]


class MazeSolver:
    """BFS-based solver that finds the shortest path through a maze grid."""

    def __init__(self, grid: Grid, entry: Point, exit_point: Point) -> None:
        self.grid = grid
        self.entry = entry
        self.exit = exit_point
        self.height = len(grid)
        self.width = len(grid[0]) if self.height > 0 else 0

    @classmethod
    def from_output_file(
        cls,
        file_path: str,
        default_entry: Optional[Point] = None,
        default_exit: Optional[Point] = None,
    ) -> "MazeSolver":
        """Construct a MazeSolver from a maze output file.
        Falls back to *default_entry* / *default_exit* when the file omits them."""  # noqa E501
        grid, file_entry, file_exit = cls._parse_output_file(file_path)

        entry = file_entry if file_entry is not None else default_entry
        exit_point = file_exit if file_exit is not None else default_exit

        if entry is None or exit_point is None:
            raise ValueError("Entry/ Exit not found in file, please provide them!")  # noqa E501
        return cls(grid, entry, exit_point)

    @staticmethod
    def _parse_output_file(
        file_path: str,
    ) -> Tuple[Grid, Optional[Point], Optional[Point]]:
        """Read a maze output file; return grid with optional entry/exit."""
        if not os.path.isabs(file_path):
            file_path = os.path.join(os.path.dirname(__file__), file_path)

        with open(file_path, "r") as file:
            raw_lines = [line.rstrip("\n") for line in file]
        if not raw_lines:
            raise ValueError("Maze file is empty!")

        maze_lines: List[str] = []
        footer_lines: List[str] = []
        blank_found = False

        for line in raw_lines:
            stripped = line.strip()

            if stripped == "":
                blank_found = True
                continue

            if blank_found:
                footer_lines.append(stripped)
            else:
                maze_lines.append(stripped)

        if not maze_lines:
            raise ValueError("Maze grid is missing from file!")

        expected_width = len(maze_lines[0])
        grid: Grid = []

        for line in maze_lines:
            if len(line) != expected_width:
                raise ValueError("Maze rows are not all the same width!")

            row: List[int] = []
            for char in line:
                try:
                    row.append(int(char, 16))
                except ValueError as exc:
                    raise ValueError(f"Invalid hexadecimal cell value: {char}") from exc  # noqa E501
            grid.append(row)

        entry: Optional[Point] = None
        exit_point: Optional[Point] = None

        if len(footer_lines) >= 1:
            entry = MazeSolver._parse_point(footer_lines[0])
        if len(footer_lines) >= 2:
            exit_point = MazeSolver._parse_point(footer_lines[1])

        return grid, entry, exit_point

    @staticmethod
    def _parse_point(line: str) -> Point:
        """Parse a 'x,y' string into a Point tuple."""
        parts = line.split(",")
        if len(parts) != 2:
            raise ValueError(f"Invalid coordinate line: {line}")

        try:
            x = int(parts[0].strip())
            y = int(parts[1].strip())
        except ValueError as exc:
            raise ValueError(f"Invalid coordinate values: {line}") from exc

        return (x, y)

    def solve(self) -> str:
        """Return a direction string for the shortest path from entry to exit.

        Raises ValueError when no path exists or the maze structure is invalid.
        """
        self.validate_base_structure()

        if self.entry == self.exit:
            return ""

        parents = self._bfs_shortest_path()
        if self.exit not in parents:
            raise ValueError("No valid path found from entry to exit!")

        return self._reconstruct_path(parents)

    def validate_base_structure(self) -> None:
        """Raise ValueError if the grid is malformed or entry/exit are out of bounds."""  # noqa E501
        if self.height == 0 or self.width == 0:
            raise ValueError("Maze grid cannot be empty!")
        for row in self.grid:
            if len(row) != self.width:
                raise ValueError("Maze grid must be rectangular!")
        if not self._in_bounds(self.entry[0], self.entry[1]):
            raise ValueError("Entry point is out of maze bounds!")

        if not self._in_bounds(self.exit[0], self.exit[1]):
            raise ValueError("Exit point is out of maze bounds!")

    def _bfs_shortest_path(
        self,
    ) -> Dict[Point, Tuple[Optional[Point], str]]:
        """Run BFS from entry to exit; return parent-map for path reconstruction."""  # noqa E501
        queue: List[Point] = [self.entry]
        front = 0

        visited: Dict[Point, bool] = {self.entry: True}
        parents: Dict[Point, Tuple[Optional[Point], str]] = {self.entry: (None, "")}  # noqa E501

        while front < len(queue):
            current = queue[front]
            front += 1

            if current == self.exit:
                break

            neighbors = self._get_open_neighbors(current[0], current[1])
            for next_point, move in neighbors:
                if next_point not in visited:
                    visited[next_point] = True
                    parents[next_point] = (current, move)
                    queue.append(next_point)

        return parents

    def _get_open_neighbors(self, x: int, y: int) -> List[Tuple[Point, str]]:
        """Return all passable neighbours of cell (x, y) with direction labels."""  # noqa E501
        neighbors: List[Tuple[Point, str]] = []
        cell_value = self.grid[y][x]

        for move, dx, dy, wall_bit in DIRECTIONS:
            nx = x + dx
            ny = y + dy

            if not self._in_bounds(nx, ny):
                continue

            if self._is_wall_closed(cell_value, wall_bit):
                continue

            if not self._neighbor_is_coherent(x, y, nx, ny, move):
                continue

            neighbors.append(((nx, ny), move))

        return neighbors

    def _neighbor_is_coherent(
        self, x: int, y: int, nx: int, ny: int, move: str
    ) -> bool:
        """Return True when both sides of the shared wall agree it is open."""
        current = self.grid[y][x]
        neighbor = self.grid[ny][nx]

        if move == "N":
            return not self._is_wall_closed(
                current, NORTH
            ) and not self._is_wall_closed(neighbor, SOUTH)
        if move == "E":
            return not self._is_wall_closed(current, EAST) and not self._is_wall_closed(  # noqa E501
                neighbor, WEST
            )
        if move == "S":
            return not self._is_wall_closed(
                current, SOUTH
            ) and not self._is_wall_closed(neighbor, NORTH)
        if move == "W":
            return not self._is_wall_closed(current, WEST) and not self._is_wall_closed(  # noqa E501
                neighbor, EAST
            )
        return False

    def _reconstruct_path(
        self,
        parents: Dict[Point, Tuple[Optional[Point], str]],
    ) -> str:
        """Walk the parent-map back from exit to entry; return the move string."""  # noqa E501
        path_parts: List[str] = []
        current = self.exit

        while current != self.entry:
            parent, move = parents[current]
            if parent is None:
                raise ValueError("Broken chain while reconstructing path!")
            path_parts.append(move)
            current = parent

        path_parts.reverse()
        return "".join(path_parts)

    def _in_bounds(self, x: int, y: int) -> bool:
        """Return True if (x, y) is within the grid dimensions."""
        return 0 <= x < self.width and 0 <= y < self.height

    def _is_wall_closed(self, cell_value: int, wall_bit: int) -> bool:
        """Return True if the given wall bit is set (wall present)."""
        return (cell_value & wall_bit) != 0


# solver = MazeSolver.from_output_file(
#     "output.txt",
#     default_entry=(0, 0),
#     default_exit=(19, 14),
# )
# path = solver.solve()
# print(path)
