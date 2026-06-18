import curses
import random
import sys

from src.MazeGenerator import MazeGenerator
from src.MazeSolver import MazeSolver
from src.models.Maze import Maze
from src.models.MazeConfig import MazeConfig
from src.models.direction_constants import DIRECTION_DELTAS


class MazeVisualizer:
    """Interactive terminal-based maze visualization using curses.

    Allows users to view, regenerate, and explore a maze with keyboard
    controls.
    """

    # Available color palettes for maze walls
    _WALL_PALETTES = [
        curses.COLOR_BLUE,
        curses.COLOR_CYAN,
        curses.COLOR_MAGENTA,
        curses.COLOR_GREEN,
        curses.COLOR_YELLOW,
    ]

    def __init__(self, config: MazeConfig) -> None:
        """Initialize MazeVisualizer with configuration.

        Args:
            config: Maze configuration object.
        """
        self.config = config

        # UI state
        self.show_solution_path = False
        self.palette_index = 0

        # Maze state
        self.maze: Maze | None = None
        self.solution_path = ""
        self.player_position: tuple[int, int] | None = None
        self.exit_reached = False

        # First seed is taken from config, later seeds are random
        self._initial_seed = config.seed

    def _next_seed(self) -> int:
        """Get next seed for maze generation.

        Uses initial seed once, then switches to random generation.

        Returns:
            int: Seed value for generation.
        """
        if self._initial_seed is not None:
            seed = self._initial_seed
            self._initial_seed = None
            return seed

        return random.randint(0, 10**9)

    def _build(self) -> None:
        """Generate and solve a new maze."""
        seed = self._next_seed()

        # Generate maze
        generator = MazeGenerator(self.config.width, self.config.height, seed)
        maze = generator.generate(
            self.config.entry,
            self.config.exit,
            self.config.perfect
        )

        self.maze = maze
        self.player_position = maze.entry
        self.exit_reached = False

        # Solve maze
        solver = MazeSolver(maze)
        self.solution_path = solver.shortest_path()

    def _require_maze(self) -> Maze:
        """Ensure maze has been generated.

        Returns:
            Maze: The generated maze object.

        Raises:
            RuntimeError: If maze has not been built yet.
        """
        if self.maze is None:
            raise RuntimeError("Maze is not built yet")

        return self.maze

    def _path_cells(self) -> set[tuple[int, int]]:
        """Get set of cells that form the solution path.

        Returns:
            set[tuple[int, int]]: Cells on the shortest path.
        """
        maze = self._require_maze()

        row, col = maze.entry
        path_cells = {(row, col)}

        # Walk through solution directions and collect visited cells
        for direction in self.solution_path:
            d_row, d_col = DIRECTION_DELTAS[direction]
            row += d_row
            col += d_col
            path_cells.add((row, col))

        return path_cells

    def _move_player(self, direction: str) -> None:
        """Move player one cell if the selected direction is open."""
        maze = self._require_maze()

        if self.exit_reached:
            return

        if self.player_position is None:
            self.player_position = maze.entry

        row, col = self.player_position
        cell = maze.grid[row][col]

        if cell.walls[direction]:
            return

        d_row, d_col = DIRECTION_DELTAS[direction]
        next_row = row + d_row
        next_col = col + d_col

        if not (0 <= next_row < maze.height and 0 <= next_col < maze.width):
            return

        next_cell = maze.grid[next_row][next_col]
        if next_cell.blocked:
            return

        self.player_position = (next_row, next_col)
        self.exit_reached = self.player_position == maze.exit

    def _init_colors(self) -> None:
        """Initialize curses color pairs for maze rendering."""
        curses.start_color()
        curses.use_default_colors()

        curses.init_pair(1, self._WALL_PALETTES[self.palette_index], -1)
        curses.init_pair(2, curses.COLOR_GREEN, -1)   # start
        curses.init_pair(3, curses.COLOR_RED, -1)     # exit
        curses.init_pair(4, curses.COLOR_BLUE, -1)    # default
        curses.init_pair(5, curses.COLOR_YELLOW, -1)  # path
        curses.init_pair(6, curses.COLOR_WHITE, -1)   # player

    def _build_wall_canvas(self) -> list[str]:
        """Build ASCII representation of the maze.

        Returns:
            list[str]: Lines of ASCII art representing the maze.
        """
        maze = self._require_maze()

        height = maze.height
        width = maze.width

        lines: list[str] = []

        # Top border
        top_border = "+" + "".join(
            ("---" if maze.grid[0][col].walls["N"] else "   ") + "+"
            for col in range(width)
        )
        lines.append(top_border)

        # Maze rows
        for row in range(height):

            # Vertical walls and cell contents
            row_line = ""
            for col in range(width):
                cell = maze.grid[row][col]

                if col == 0:
                    row_line += "|" if cell.walls["W"] else " "

                row_line += "###" if cell.blocked else "   "
                row_line += "|" if cell.walls["E"] else " "

            lines.append(row_line)

            # Bottom walls
            bottom_border = "+" + "".join(
                ("---" if maze.grid[row][col].walls["S"] else "   ") + "+"
                for col in range(width)
            )
            lines.append(bottom_border)

        # Convert to mutable canvas
        canvas = [list(line) for line in lines]

        entry_row, entry_col = maze.entry
        exit_row, exit_col = maze.exit

        entry_pos = (2 * entry_row + 1, 4 * entry_col + 2)
        exit_pos = (2 * exit_row + 1, 4 * exit_col + 2)

        # Draw solution path
        if self.show_solution_path:
            for cell_row, cell_col in self._path_cells():
                canvas_row = 2 * cell_row + 1
                canvas_col = 4 * cell_col + 2

                if (canvas_row, canvas_col) not in (entry_pos, exit_pos):
                    if 0 <= canvas_row < len(canvas) and 0 <= canvas_col < len(canvas[canvas_row]):  # noqa: E501
                        if canvas[canvas_row][canvas_col] == " ":
                            canvas[canvas_row][canvas_col] = "o"

        # Draw start and exit markers
        for pos, char in ((entry_pos, "S"), (exit_pos, "E")):
            row, col = pos
            if 0 <= row < len(canvas) and 0 <= col < len(canvas[row]):
                canvas[row][col] = char

        # Draw player
        if self.player_position is not None:
            player_row, player_col = self.player_position
            canvas_row = 2 * player_row + 1
            canvas_col = 4 * player_col + 2
            if 0 <= canvas_row < len(canvas) and 0 <= canvas_col < len(canvas[canvas_row]):  # noqa: E501
                canvas[canvas_row][canvas_col] = "@"

        return ["".join(row) for row in canvas]

    def _draw_wall_canvas(self, stdscr: curses.window) -> None:
        """Draw the maze to the terminal screen.

        Args:
            stdscr: curses window object.
        """

        # Character → color mapping
        color_map = {
            frozenset("+-|#"): curses.color_pair(1),
            "S": curses.color_pair(2) | curses.A_BOLD,
            "E": curses.color_pair(3) | curses.A_BOLD,
            "o": curses.color_pair(2),
            "@": curses.color_pair(6) | curses.A_BOLD,
        }

        default_color = curses.color_pair(4)

        for y, line in enumerate(self._build_wall_canvas()):
            for x, ch in enumerate(line):

                if ch in "+-|#":
                    color = curses.color_pair(1)
                elif ch in color_map:
                    color = color_map[ch]
                else:
                    color = default_color

                try:
                    stdscr.addstr(y, x, ch, color)
                except curses.error:
                    pass

    def _draw_exit_banner(self, stdscr: curses.window, start_y: int) -> None:
        """Draw a prominent message after the player reaches the exit."""
        lines = [
            "+-----------------------------------------------+",
            "|                 EXIT REACHED!                 |",
            "|        Press R to regenerate or Q to quit     |",
            "+-----------------------------------------------+",
        ]

        try:
            max_y, max_x = stdscr.getmaxyx()
        except curses.error:
            return

        for offset, line in enumerate(lines):
            y = start_y + offset
            if y >= max_y:
                break
            text = line[:max_x]
            try:
                stdscr.addstr(y, 0, text, curses.A_REVERSE | curses.A_BOLD)
            except curses.error:
                pass

    def run(self) -> None:
        """Start the interactive maze visualization."""
        curses.wrapper(self._loop)

    def _loop(self, stdscr: curses.window) -> None:
        """Main event loop for the visualization.

        Handles user input and updates the display.

        Args:
            stdscr: curses window object.
        """
        curses.curs_set(0)
        stdscr.keypad(True)

        # Build first maze
        self._build()
        self._init_colors()

        while True:
            maze = self._require_maze()

            stdscr.clear()
            self._draw_wall_canvas(stdscr)

            info_y = maze.height * 2 + 1
            if self.exit_reached:
                self._draw_exit_banner(stdscr, info_y)
                info_y += 5

            try:
                stdscr.addstr(
                    info_y,
                    0,
                    "Exit reached. Press [R] to regenerate or [Q] to quit"
                    if self.exit_reached
                    else "Move: arrows/WASD  [R]egenerate  [P]ath  [C]olor  [Q]uit",  # noqa: E501
                    curses.A_BOLD
                )

                stdscr.addstr(
                    info_y + 1,
                    0,
                    f"seed={maze.seed}  perfect={self.config.perfect}  path_len={len(self.solution_path)}  position={self.player_position}"  # noqa: E501
                )

            except curses.error:
                pass

            stdscr.refresh()

            try:
                key = stdscr.getch()
            except KeyboardInterrupt:
                sys.exit(0)

            # Handle keyboard input
            if key in (ord("q"), ord("Q")):
                break

            elif key in (ord("p"), ord("P")):
                self.show_solution_path = not self.show_solution_path

            elif key in (ord("c"), ord("C")):
                self.palette_index = (self.palette_index + 1) % len(self._WALL_PALETTES)  # noqa: E501
                self._init_colors()

            elif key in (ord("r"), ord("R")):
                self._build()

            elif key in (curses.KEY_UP, ord("w"), ord("W")):
                self._move_player("N")

            elif key in (curses.KEY_DOWN, ord("s"), ord("S")):
                self._move_player("S")

            elif key in (curses.KEY_RIGHT, ord("d"), ord("D")):
                self._move_player("E")

            elif key in (curses.KEY_LEFT, ord("a"), ord("A")):
                self._move_player("W")
