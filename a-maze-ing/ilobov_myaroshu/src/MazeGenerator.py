from src.models.direction_constants import DIRECTION_DELTAS, OPPOSITE_DIRECTIONS  # noqa: E501
from src.models.pattern_constants import PATTERN_WIDTH, PATTERN_HEIGHT
from src.models.Cell import Cell
from src.models.Maze import Maze
from src.models.Pattern import Pattern
import random


class MazeGenerator:
    """Generates mazes using recursive backtracking algorithm.

    Supports perfect mazes (single path between any two points) and
    non-perfect mazes with multiple paths. Can optionally apply a '42' pattern
    and be seeded for reproducible generation.
    """

    _CELLS_PER_EXTRA_OPENING = 10

    def __init__(self, width: int, height: int, seed: int | None = None) -> None:  # noqa: E501
        """Initialize MazeGenerator with dimensions and optional seed.

        Args:
            width: Width of the maze in cells.
            height: Height of the maze in cells.
            seed: Optional seed for reproducible generation. Defaults to None.
        """
        self.width = width
        self.height = height
        self.rng = random.Random(seed)
        self.grid = []
        self.seed = seed

        for row in range(height):
            current_row = []
            for col in range(width):
                current_row.append(Cell(row, col))
            self.grid.append(current_row)

    def generate(
        self,
        entry: tuple[int, int],
        exit: tuple[int, int],
        perfect: bool = True
    ) -> Maze:
        """Generate a maze with specified entry and exit points.

        Args:
            entry: Entry coordinates as (x, y).
            exit: Exit coordinates as (x, y).
            perfect: If True, generates perfect maze. If False, adds cycles.

        Returns:
            Maze: Generated maze object.

        Raises:
            ValueError: If entry/exit are out of bounds or blocked by pattern.
        """

        self._apply_pattern_42()

        start_row, start_col = entry[0], entry[1]
        exit_row, exit_col = exit[0], exit[1]

        if not (0 <= start_row < self.height and 0 <= start_col < self.width):
            raise ValueError("Entry is out of maze bounds")
        if not (0 <= exit_row < self.height and 0 <= exit_col < self.width):
            raise ValueError("Exit is out of maze bounds")
        if (start_row, start_col) == (exit_row, exit_col):
            raise ValueError("Entry and exit must be different cells")

        start_cell = self.grid[start_row][start_col]
        exit_cell = self.grid[exit_row][exit_col]

        if start_cell.blocked:
            raise ValueError("Entry cell is blocked by pattern '42'")
        if exit_cell.blocked:
            raise ValueError("Exit cell is blocked by pattern '42'")

        for row in self.grid:
            for cell in row:
                cell.visited = False

        start_cell.visited = True
        stack = [start_cell]

        while stack:
            current = stack[-1]
            neighbours = self.get_unvisited_neighbours(current)

            if neighbours:
                nxt = self.rng.choice(neighbours)
                nxt.visited = True
                self.remove_wall(current, nxt)
                stack.append(nxt)
            else:
                stack.pop()

        if not perfect:
            self._add_random_loops()

        return Maze(
            width=self.width,
            height=self.height,
            grid=self.grid,
            entry=entry,
            exit=exit,
            seed=self.seed
        )

    def _apply_pattern_42(self) -> None:
        """Apply the '42' pattern to the maze grid, blocking specific cells."""
        offset_row = (self.height - PATTERN_HEIGHT) // 2
        offset_col = (self.width - PATTERN_WIDTH) // 2

        pattern = Pattern(self.grid, self.width, self.height)
        pattern.apply(offset_row, offset_col)

    def get_unvisited_neighbours(self, cell: Cell) -> list[Cell]:
        """Get list of unvisited and unblocked neighbors of a cell.

        Args:
            cell: The cell to get neighbors for.

        Returns:
            list: List of unvisited, unblocked neighbor cells.
        """
        neighbours: list[Cell] = []
        for direction, (dr, dc) in DIRECTION_DELTAS.items():
            new_row = cell.row + dr
            new_col = cell.col + dc
            if 0 <= new_row < self.height and 0 <= new_col < self.width:
                neighbour = self.grid[new_row][new_col]
                if not neighbour.visited and not neighbour.blocked:
                    neighbours.append(neighbour)
        return neighbours

    def remove_wall(self, current: Cell, neighbour: Cell) -> None:
        """Remove wall between two neighboring cells.

        Args:
            current: The current cell.
            neighbour: The neighboring cell.

        Raises:
            ValueError: If cells are not neighbors.
        """
        dr = neighbour.row - current.row
        dc = neighbour.col - current.col

        direction: str | None = None
        for d, delta in DIRECTION_DELTAS.items():
            if delta == (dr, dc):
                direction = d
                break

        if direction is None:
            raise ValueError(
                f"Cells are not neighbours: ({current.row},{current.col}) -> ({neighbour.row},{neighbour.col})"  # noqa: E501
            )

        current.remove_wall(direction)
        neighbour.remove_wall(OPPOSITE_DIRECTIONS[direction])

    def _add_random_loops(self) -> None:
        """Add random wall openings to create loops in the maze.

        This increases the complexity of the maze by allowing multiple paths
        from entry to exit, making it non-perfect.
        """
        target_openings = max(1, (self.width * self.height) // self._CELLS_PER_EXTRA_OPENING)  # noqa: E501
        removable_walls: list[tuple[Cell, Cell]] = []

        for r in range(self.height):
            for c in range(self.width):
                cell = self.grid[r][c]
                if cell.blocked:
                    continue

                for direction in ("E", "S"):
                    dr, dc = DIRECTION_DELTAS[direction]
                    nr, nc = r + dr, c + dc

                    if not (0 <= nr < self.height and 0 <= nc < self.width):
                        continue

                    neighbour = self.grid[nr][nc]
                    if neighbour.blocked:
                        continue

                    if cell.walls[direction]:
                        removable_walls.append((cell, neighbour))

        if not removable_walls:
            return

        self.rng.shuffle(removable_walls)
        for cell, neighbour in removable_walls[:target_openings]:
            self.remove_wall(cell, neighbour)
