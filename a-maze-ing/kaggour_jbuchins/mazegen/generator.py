from abc import ABC, abstractmethod
import random
import time
from mazegen.config import MazeConfig
from typing import Generator, List, Optional, Tuple, Dict

CLEAR = chr(27) + "[2J"
RESET = "\033[0m"


NULL = 0
N = 1 << 0
E = 1 << 1
S = 1 << 2
W = 1 << 3

COLOUR_PALETTES: List[Tuple[int, int]] = [
    (50, 200),  # default: bright-cyan walls / magenta 42
    (226, 93),  # yellow walls  / orange 42
    (196, 46),  # green walls   / red 42
    (255, 105),  # white walls   / purple 42
    (55, 204),  # purple walls  / pink 42
    (226, 20),  # yellow walls  / blue 42
    (255, 208),  # white walls  / yellow 42
]


class Point:
    """A 2D integer coordinate used throughout maze generation and solving."""

    def __init__(self, x: int, y: int) -> None:
        self.x: int = x
        self.y: int = y

    def __add__(self, offset: "Point") -> "Point":
        return Point(self.x + offset.x, self.y + offset.y)

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, Point):
            return NotImplemented
        if self.x == other.x and self.y == other.y:
            return True
        return False

    def __hash__(self) -> int:
        return hash((self.x, self.y))

    def __str__(self) -> str:
        return f"Point({self.x},{self.y})"

    def cp(self) -> "Point":
        """Return a copy of this point."""
        return Point(self.x, self.y)


DIGIT_42 = [
    Point(0, 0),
    Point(0, 1),
    Point(0, 2),
    Point(1, 2),
    Point(2, 2),
    Point(2, 3),
    Point(2, 4),
    Point(4, 0),
    Point(5, 0),
    Point(6, 0),
    Point(6, 1),
    Point(4, 2),
    Point(5, 2),
    Point(6, 2),
    Point(4, 3),
    Point(4, 4),
    Point(5, 4),
    Point(6, 4),
]

print_dict = {
    N: "▔",
    E: "▕",
    S: "▁",
    W: "▏",
    W | N: "🭽",
    N | E: "🭾",
    E | S: "🭿",
    S | W: "🭼",
    NULL: " ",
}


class Grid:
    """Underlying grid of bitmask cells representing wall states per cell."""

    opposite = {N: S, E: W, S: N, W: E}
    offset = {
        N: Point(0, -1),
        E: Point(+1, 0),
        S: Point(0, +1),
        W: Point(-1, 0),
    }

    def __init__(
        self,
        width: int,
        height: int,
        fourtytwo: Optional[List[Point]],
    ) -> None:
        self.width = width
        self.height = height
        self.grid = self._init_grid()
        self.fourtytwo: List[Point] = (
            fourtytwo if fourtytwo is not None else []
        )  # noqa E501

    def _init_grid(self, value: int = 15) -> List[List[int]]:
        """Initialise all cells with all walls present."""
        maze = [[value for _ in range(self.width)] for _ in range(self.height)]
        return maze

    def carve(self, position: Point, direction: int) -> None:
        """Remove the wall between *position* and its neighbour in *direction*."""  # noqa E501
        self.clear_wall(position, direction)
        next_pos = position + Grid.offset[direction]
        self.clear_wall(next_pos, Grid.opposite[direction])

    def is_valid(self, position: Point) -> bool:
        """Return True if *position* is modifiable; raise IndexError otherwise."""  # noqa E501
        if position in self.fourtytwo:
            raise IndexError(f"Can't modify into the 42 logo from {position}")
        if not (
            0 <= position.x < self.width and 0 <= position.y < self.height
        ):  # noqa E501
            raise IndexError(f"Can't modify out of bounds from {position}")
        return True

    def __add_bit(self, position: Point, bit: int) -> None:
        self.grid[position.y][position.x] |= bit

    def __rm_bit(self, position: Point, bit: int) -> None:
        self.grid[position.y][position.x] &= ~bit

    def clear_wall(self, position: Point, direction: int) -> None:
        """Open the wall at *position* in *direction* if the cell is valid."""
        if self.is_valid(position):
            self.__rm_bit(position, direction)

    def add_wall(self, position: Point, direction: int) -> None:
        """Close the wall at *position* in *direction* if the cell is valid."""
        if self.is_valid(position):
            self.__add_bit(position, direction)

    def get(self) -> List[List[int]]:
        """Return the raw 2-D grid of cell bitmasks."""
        return self.grid

    def reset_grid(self) -> None:
        """Reset all cells to fully walled state."""
        self.grid = self._init_grid()


class Maze:
    """Core maze data model: grid, entry/exit points, and plugin registries."""

    random_module = random

    def __init__(
        self,
        width: int,
        height: int,
        entry: Point,
        exit: Point,
        perfect: bool,
        seed: int,
        Digit_42: List[Point] = DIGIT_42,
    ) -> None:
        self.width: int = width
        self.height: int = height
        self.entry: Point = entry
        self.exit: Point = exit
        self.perfect: bool = perfect
        self.seed = seed
        self.random_module.seed(seed)
        self.fourtytwo: Optional[List[Point]] = self.move_fourtytwo(Digit_42)
        self.grid: Grid = Grid(width, height, self.fourtytwo)
        self.generator: Dict[str, "GeneratorPlugin"] = {}

    @classmethod
    def init_from_config(cls, c: MazeConfig) -> "Maze":
        """Construct a Maze from a MazeConfig instance."""
        return cls(
            c.width,
            c.height,
            Point(c.entry.x, c.entry.y),
            Point(c.exit.x, c.exit.y),
            c.perfect,
            c.seed,
        )

    def validate_fourtytwo(self, fourtytwo: List[Point]) -> None:
        """Raise ValueError if entry or exit overlaps with the 42 logo cells."""  # noqa E501
        if self.entry in fourtytwo:
            raise ValueError(f"Entry({self.entry}) can't be in the 42 Logo")
        if self.exit in fourtytwo:
            raise ValueError(f"Exit({self.exit}) can't be in the 42 Logo")

    def move_fourtytwo(self, Digit_42: List[Point]) -> Optional[List[Point]]:
        """Centre the 42 logo; return None if the maze is too small."""
        fourty_two = []
        x_42 = (self.width // 2) - 3
        y_42 = (self.height // 2) - 2
        if self.width < 9 or self.height < 7:
            return None
        else:
            for point in Digit_42:
                fourty_two.append(Point(point.x + x_42, point.y + y_42))
            self.validate_fourtytwo(fourty_two)
            return fourty_two

    def add_generator(self, key: str, generator: "GeneratorPlugin") -> None:
        """This function adds a generator mapped to a certain key,
        no protection, old ones can be overwritten"""
        self.generator[key] = generator

    def apply_generator(self, generator_key: str) -> None:
        """This function generates all steps to complete a maze"""
        for _ in self.generator[generator_key].generate_step(self.grid):
            pass

    def new_maze_seed(self, new_seed: int) -> None:
        """Update the seed on the maze and all registered generator plugins."""
        self.seed = new_seed
        for gen in self.generator.values():
            gen.update_seed(new_seed)


# ---------------------------------------#
#              Renderer                  #
# ---------------------------------------#


class Renderer:
    """Renders a Maze to the terminal using Unicode block chars and ANSI colours."""  # noqa E501

    def __init__(
        self,
        wall_color: int = 50,
        fourtytwo_color: int = 200,
        dict: Dict = print_dict,
        size: int = 2,
    ) -> None:
        if size < 2:
            self.size = 2
        else:
            self.size = size
        self.dict = dict
        self.cell_x = size * self.mult.x
        self.cell_y = size * self.mult.y
        self.cell_x_index_max = self.cell_x - 1
        self.cell_y_index_max = self.cell_y - 1
        self.wall_color = wall_color
        self.fourtytwo_color = fourtytwo_color
        self.background: Dict = {}

    class mult:
        x = 2
        y = 1

    @classmethod
    def init_from_maze(cls, maze: Maze) -> "Renderer":
        """Construct a default Renderer for the given maze."""
        return cls()

    def get_pos_mask(self, x: int, y: int) -> int:
        """Return a bitmask of which borders a sub-cell position touches."""
        mask = 0
        if x == 0:
            mask |= W
        if x == self.cell_x_index_max:
            mask |= E
        if y == 0:
            mask |= N
        if y == self.cell_y_index_max:
            mask |= S
        return mask

    def __color_layer(
        self,
        maze: Maze,
        path: Optional[List[Point]] = None,
        player: Optional[Point] = None,
    ) -> dict:
        background = {}
        if path is not None:
            for p in path:
                background[p] = 45  # CYAN
        if maze.fourtytwo is not None:
            for p in maze.fourtytwo:
                background[p] = self.fourtytwo_color
        background[maze.entry] = 46  # GREEN
        background[maze.exit] = 88  # RED
        if player is not None:
            background[player] = 231  # WHITE
        return background

    def wall_color_code(self) -> str:
        """Return the ANSI escape code for the current wall foreground colour."""  # noqa E501
        return f"\033[38;5;{self.wall_color}m"

    def back_color_code(self, code: int) -> str:
        """Return the ANSI escape code for background colour *code*."""
        return f"\033[48;5;{code}m"

    def set_wall_color(self, new_color_id: int) -> None:
        """Update the wall foreground colour."""
        self.wall_color = new_color_id

    def set_fourtytwo_color(self, new_color_id: int) -> None:
        """Update the 42 logo background colour."""
        self.fourtytwo_color = new_color_id

    def get_colors(self, chunkmask: int, grid_point: Point) -> str:
        """Return combined ANSI colour prefix for a sub-cell."""
        colors = ""
        if grid_point in self.background.keys():
            colors += self.back_color_code(self.background[grid_point])
        if chunkmask != 0:
            colors += self.wall_color_code()
        return colors

    def render(
        self,
        maze: Maze,
        path: Optional[List[Point]] = None,
        player: Optional[Point] = None,
    ) -> None:
        """Print the maze to stdout, optionally highlighting *path* cells."""
        grid = maze.grid.get()
        self.background = self.__color_layer(maze, path, player)
        for y_grid, line in enumerate(grid):
            print_line = ["" for _ in range(self.cell_y)]
            for x_grid, cell in enumerate(line):
                for y in range(self.cell_y):
                    for x in range(self.cell_x):
                        chunkmask = cell & self.get_pos_mask(x, y)
                        print_line[y] += self.get_colors(
                            chunkmask, Point(x_grid, y_grid)
                        )
                        print_line[y] += self.dict[chunkmask]
                        print_line[y] += RESET
            for row in print_line:
                print(row)


# ---------------------------------------#
#              Generator                 #
# ---------------------------------------#


class GeneratorPlugin(ABC):
    """Plugin base that modifies a maze via carve/add_wall/clear_wall.

    Subclasses receive a seeded Random instance and must implement
    init_from_maze and generate_step.
    """

    def __init__(self, rand: random.Random) -> None:
        self.rand = rand

    def update_seed(self, new_seed: int) -> None:
        """Re-seed the plugin's random instance."""
        self.rand.seed(new_seed)

    @classmethod
    @abstractmethod
    def init_from_maze(cls, maze: Maze) -> "GeneratorPlugin":
        """Return an initialized generator from the Maze Class Object."""
        pass

    @abstractmethod
    def generate_step(
        self, grid: Grid
    ) -> Generator[Optional[List[Point]], None, None]:  # noqa E501
        """Yield after every modification step.

        The generator modifies the maze directly via
        carve(), add_wall(), clear_wall().
        """
        pass


class GrowingTreePlugin(GeneratorPlugin):
    """Growing-tree maze generation algorithm.

    Carves passages by maintaining a list of active cells and expanding
    from a randomly selected one until all cells are visited.
    """

    def __init__(
        self,
        rand_mod: random.Random,
        width: int,
        height: int,
        entry: Point,
        exit: Point,
        Logo_42: Optional[List[Point]] = None,
    ) -> None:
        super().__init__(rand_mod)
        self.burst = width * height // 20
        if self.burst <= 2:
            self.burst = 3
        self.avaliable: Optional[List[Point]] = None
        self.entry = entry
        self.exit: Point = exit
        self.width = width
        self.height = height
        self.fourtytwo: List[Point] = Logo_42 if Logo_42 is not None else []
        self.position: Optional[Point] = None
        self.visited: Optional[List[Point]] = None

    def _base(self) -> None:
        """Initialise the available cell list and visited tracking."""
        self.avaliable = [
            Point(x, y)
            for x in range(self.width)
            for y in range(self.height)
            if Point(x, y) not in self.fourtytwo and Point(x, y) != self.entry
        ]
        self.position = Point(self.entry.x, self.entry.y)
        self.visited = [self.position]

    @classmethod
    def init_from_maze(cls, maze: Maze) -> "GrowingTreePlugin":
        """Construct a GrowingTreePlugin from a Maze instance."""
        return cls(
            random.Random(maze.seed),
            maze.width,
            maze.height,
            maze.entry,
            maze.exit,
            maze.fourtytwo,
        )

    def choose(self, neighbours: List[int]) -> int:
        """Select the next direction from *neighbours* at random."""
        return self.rand.choice(neighbours)

    def free_neighbours(self) -> List[int]:
        """Return direction bits for unvisited neighbours of current position."""  # noqa E501
        ret = 0
        for bit, off in Grid.offset.items():
            if self.position is not None:
                if (self.position + off) in (self.avaliable or []):
                    ret |= bit
        return [1 << shift for shift in range(4) if ret & 1 << shift]

    def new_pos(self) -> Optional[Point]:
        """Pick a random point from the visited list, or None if empty."""
        if self.visited:
            return self.rand.choice(self.visited)
        else:
            return None

    def generate_step(
        self, grid: Grid
    ) -> Generator[Optional[List[Point]], None, None]:  # noqa E501
        """Yield the current path after each carved passage."""
        self._base()
        # maze.grid.reset_grid()
        path: List[Point] = []
        while self.avaliable:
            for b in range(self.burst):
                neighbours = self.free_neighbours()
                if len(neighbours) == 0:
                    if (
                        b == 0
                        and self.visited is not None
                        and self.position is not None
                    ):  # noqa E501
                        self.visited.remove(self.position)
                    break
                direction = self.choose(neighbours)
                if self.position is not None:
                    grid.carve(self.position, direction)
                    self.position = self.position + Grid.offset[direction]
                    if self.visited is not None:
                        self.visited.append(self.position)
                    if self.avaliable is not None:
                        self.avaliable.remove(self.position)
                    path.append(self.position)
                yield path
            path.clear()
            self.position = self.new_pos()
        path.clear()
        yield None


class WilsonPlugin(GeneratorPlugin):
    """Wilson's algorithm (loop-erased random walk).

    Generates a uniformly random spanning tree: every possible perfect maze
    of the given dimensions is equally probable.  Tends to produce mazes with
    many short dead-ends rather than long winding corridors
    """

    def __init__(
        self,
        seed: random.Random,
        width: int,
        height: int,
        entry: Point,
        exit_pt: Point,
        logo_42: Optional[List[Point]] = None,
    ) -> None:
        super().__init__(seed)
        self.width = width
        self.height = height
        self._entry: Point = entry
        excluded: set = set(logo_42) if logo_42 else set()
        self._excluded: set = excluded  # also used by _random_neighbour
        all_cells: List[Point] = [
            Point(x, y)
            for y in range(height)
            for x in range(width)
            if Point(x, y) not in excluded
        ]
        self.in_maze: set = {entry}
        self.remaining: List[Point] = [p for p in all_cells if p != entry]

    @classmethod
    def init_from_maze(cls, maze: Maze) -> "WilsonPlugin":
        """Initialise from a Maze instance."""
        return cls(
            random.Random(maze.seed),
            maze.width,
            maze.height,
            maze.entry,
            maze.exit,
            maze.fourtytwo,
        )

    def _random_neighbour(self, pos: Point) -> Optional[Point]:
        """Return a random neighbour of *pos*, excluding 42 logo and out-of-bounds."""  # noqa E501
        candidates: List[Point] = []
        for off in Grid.offset.values():
            nb = pos + off
            if (
                0 <= nb.x < self.width
                and 0 <= nb.y < self.height
                and nb not in self._excluded
            ):
                candidates.append(nb)
        return self.rand.choice(candidates) if candidates else None

    def _direction(self, frm: Point, to: Point) -> int:
        """Return the direction bit that leads from frm to to."""
        dx = to.x - frm.x
        dy = to.y - frm.y
        if dy == -1:
            return N
        if dy == 1:
            return S
        if dx == 1:
            return E
        return W

    def _reset(self) -> None:
        all_cells: List[Point] = [
            Point(x, y)
            for y in range(self.height)
            for x in range(self.width)
            if Point(x, y) not in self._excluded
        ]
        self.in_maze = {self._entry}
        self.remaining = [p for p in all_cells if p != self._entry]

    def generate_step(
        self, grid: Grid
    ) -> Generator[Optional[List[Point]], None, None]:  # noqa E501
        """Yield after each passage carved during Wilson's walk."""
        self._reset()
        while self.remaining:
            start = self.rand.choice(self.remaining)
            walk: List[Point] = [start]
            walk_index: Dict = {start: 0}

            current = start
            while current not in self.in_maze:
                nb = self._random_neighbour(current)
                if nb is None:
                    break
                if nb in walk_index:
                    # Loop erasure
                    idx = walk_index[nb]
                    walk = walk[: idx + 1]
                    walk_index = {p: i for i, p in enumerate(walk)}
                else:
                    walk.append(nb)
                    walk_index[nb] = len(walk) - 1
                current = nb

            # Carve the loop-erased walk into the maze
            for i in range(len(walk) - 1):
                frm = walk[i]
                to = walk[i + 1]
                direction = self._direction(frm, to)
                try:
                    grid.carve(frm, direction)
                except IndexError:
                    pass  # 42-logo cell - skip silently
                self.in_maze.add(frm)
                if frm in self.remaining:
                    self.remaining.remove(frm)
                yield list(walk)

            if walk:
                last = walk[-1]
                self.in_maze.add(last)
                if last in self.remaining:
                    self.remaining.remove(last)


class Gen(Maze):
    """High-level facade over Maze: wires generation, rendering, and solving."""  # noqa E501

    def __init__(
        self,
        config: Optional[MazeConfig] = None,
        *,
        width: int,
        height: int,
        entry: Optional[Point] = None,
        exit_pt: Optional[Point] = None,
        perfect: bool = True,
        seed: int = 4242,
        algorithm: Optional[str] = None,
    ) -> None:

        if config is not None:
            width = config.width
            height = config.height
            entry = Point(config.entry.x, config.entry.y)
            exit_pt = Point(config.exit.x, config.exit.y)
            perfect = config.perfect
            seed = config.seed
            algorithm = config.algorithm

        if entry is None:
            entry = Point(0, 0)
        if exit_pt is None:
            exit_pt = Point(width - 1, height - 1)

        algorithm = (algorithm or "growingtree").lower()

        super().__init__(
            width=width,
            height=height,
            entry=entry,
            exit=exit_pt,
            perfect=perfect,
            seed=seed,
        )

        self._algorithm: str = algorithm
        self._colour_index: int = 0
        self._current_path: List[Point] = []

        self.add_generator("wilson", WilsonPlugin.init_from_maze(self))
        self.add_generator(
            "growingtree",
            GrowingTreePlugin.init_from_maze(self))

        self._active_key: str = algorithm

        wall_col, ft_col = COLOUR_PALETTES[self._colour_index]
        self._renderer: Renderer = Renderer(
            wall_color=wall_col,
            fourtytwo_color=ft_col,
        )

    def get_fourty_two(self) -> List[Point]:
        """Return the list of 42-logo cell positions, or an empty list if absent."""  # noqa E501
        return self.fourtytwo if self.fourtytwo is not None else []

    def generate(self) -> Generator[None, None, None]:
        """Reset the grid and run the active generator, yielding each step."""
        self.grid.reset_grid()
        for path in self.generator[self._active_key].generate_step(self.grid):
            if path is not None:
                self._current_path = path
            yield

    @property
    def maze(self) -> List[List[int]]:
        """Return the raw grid of cell bitmasks."""
        return self.grid.get()

    def imperfect_maze(self) -> None:
        """Remove random interior walls to create loops (imperfect mode)."""
        if self.perfect:
            return

        grid = self.grid
        logo_set: set[Point] = set(self.fourtytwo) if self.fourtytwo else set()

        candidate_walls: List[Tuple[Point, int]] = []
        for y in range(self.height):
            for x in range(self.width):
                p = Point(x, y)
                if p in logo_set:
                    continue
                if x + 1 < self.width:
                    neighbour = Point(x + 1, y)
                    if neighbour not in logo_set:
                        cell_val = self.grid.get()[y][x]
                        if cell_val & E:
                            candidate_walls.append((p, E))
                if y + 1 < self.height:
                    neighbour = Point(x, y + 1)
                    if neighbour not in logo_set:
                        cell_val = self.grid.get()[y][x]
                        if cell_val & S:
                            candidate_walls.append((p, S))

        if not candidate_walls:
            return

        extra = max(1, min(30, len(candidate_walls) // 5))
        chosen = self.random_module.sample(
            candidate_walls, min(extra, len(candidate_walls))
        )
        for point, direction in chosen:
            try:
                grid.carve(point, direction)
            except IndexError:
                pass

    def print_maze(
        self,
        solution_path: str = "",
        show_path: bool = False,
        player: Optional[Point] = None,
    ) -> None:
        """Clear terminal and render maze, optionally overlaying the solution."""  # noqa E501
        path_points: Optional[List[Point]] = None
        if show_path and solution_path:
            path_points = self._path_string_to_points(solution_path)
        print(CLEAR)
        self._renderer.render(self, path=path_points, player=player)

    def _path_string_to_points(self, solution_path: str) -> List[Point]:
        """Convert a direction string (e.g. 'NESW') into a list of Points."""
        dir_map = {"N": N, "S": S, "E": E, "W": W}
        cur = Point(self.entry.x, self.entry.y)
        points: List[Point] = [cur]
        for ch in solution_path.upper():
            bit = dir_map.get(ch)
            if bit is not None:
                cur = cur + Grid.offset[bit]
                points.append(cur)
        return points

    def rotate_colours(self) -> None:
        """Cycle to the next colour palette for walls and the 42 logo."""
        self._colour_index = (self._colour_index + 1) % len(COLOUR_PALETTES)
        wall_col, ft_col = COLOUR_PALETTES[self._colour_index]
        self._renderer.set_wall_color(wall_col)
        self._renderer.set_fourtytwo_color(ft_col)

    def animate_generation(self, delay: float = 0.01) -> None:
        """Run generation while rendering each step with an optional delay."""
        for _ in self.generate():
            self._renderer.render(self, path=self._current_path)
            if delay > 0:
                time.sleep(delay)
        self._renderer.render(self, path=None)


# if __name__ == "__main__":
#     maze = Maze(10, 10, Point(1, 1), Point(9, 9), True, 424242)
#     maze.add_generator("GT", GrowingTreePlugin.init_from_maze(maze))
#     maze.renderer = Renderer.init_from_maze(maze)
#     for step in maze.generator["GT"].generate_step(maze.grid):
#         maze.renderer.render(maze,step)
#         time.sleep(0.01)
#         print()
#     maze.renderer.render(maze)
#     maze.renderer.set_fourtytwo_color(105)
#     maze.renderer.set_wall_color(80)
#     maze.renderer.render(maze)
#     maze.renderer.set_fourtytwo_color(42)
#     maze.renderer.set_wall_color(211)
#     maze.renderer.render(maze)
