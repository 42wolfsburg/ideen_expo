import select
import random
import sys
import termios
import tty
from typing import Optional, Tuple

from mazegen.config import ConfigError, MazeConfig, parse_config_file
from mazegen.generator import E, N, S, W, Gen, Grid, Point
from mazegen.solver import MazeSolver


MOVE_KEYS = {
    "W": N,
    "\x1b[A": N,
    "D": E,
    "\x1b[C": E,
    "S": S,
    "\x1b[B": S,
    "A": W,
    "\x1b[D": W,
}


def _read_single_key() -> str:
    """Read one terminal key immediately, falling back to line input."""
    if not sys.stdin.isatty():
        return input().strip()

    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setcbreak(fd)
        key = sys.stdin.read(1)
        if key == "\x1b":
            while select.select([sys.stdin], [], [], 0.02)[0]:
                key += sys.stdin.read(1)
                if len(key) >= 3:
                    break
        print()
        return key
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)


def print_exit_banner() -> None:
    """Print a noticeable completion message."""
    print()
    print("+-----------------------------------------------+")
    print("|                 EXIT REACHED!                 |")
    print("|        Press 1 to regenerate or 8 to quit     |")
    print("+-----------------------------------------------+")
    print()


def write_output_file(
    file_path: str,
    maze: list,
    entry: Tuple[int, int],
    exit_point: Tuple[int, int],
    solution: Optional[str],
) -> None:
    """Write the maze grid, entry/exit coords, and
    optional solution to *file_path*."""
    with open(file_path, "w") as fd:
        for row in maze:
            for cell in row:
                fd.write(format(cell, "X"))
            fd.write("\n")
        fd.write("\n")
        fd.write(f"{entry[0]},{entry[1]}\n")
        fd.write(f"{exit_point[0]},{exit_point[1]}\n")
        if solution is not None:
            fd.write(f"{solution}\n")


def _print_menu(
    show_path_active: bool,
    animate_active: bool,
    gen: Gen,
    player: Point,
) -> None:
    """Print the interactive menu, reflecting current toggle states."""
    print("\n=== A-Maze-ing ===")
    print(f"Player: ({player.x},{player.y})")
    if player == gen.exit:
        print_exit_banner()
    print("1. Re-generate a new maze")
    path_label = (
        "Hide solution path" if show_path_active else "Show solution path"
    )  # noqa E501
    print(f"2. {path_label}")
    print("3. Rotate maze wall colour")
    anim_label = "Disable animation" if animate_active else "Enable animation"
    print(f"4. {anim_label}")
    print("5. Change Algorithm")
    print(f"6. Change Seed: {gen.seed}")
    print("7. Prompt for a movement key")
    print("8. Quit")
    print("Choice (1-8, or WASD): ", end="", flush=True)


def build_generator(cfg: MazeConfig) -> Gen:
    """Construct a Gen instance from *cfg*, randomising the seed slightly."""
    new_seed = cfg.seed
    return Gen(
        width=cfg.width,
        height=cfg.height,
        entry=Point(cfg.entry.x, cfg.entry.y),
        exit_pt=Point(cfg.exit.x, cfg.exit.y),
        perfect=cfg.perfect,
        seed=new_seed,
        algorithm=cfg.algorithm,
    )


# def new_seed(gen: Gen, new_seed: int) -> Gen:
#     gen.new_maze_seed(new_seed)
#     return gen


def generate_maze(gen: Gen, animate: bool = False) -> None:
    """Run maze generation on *gen*, optionally rendering each step."""
    if animate:
        gen.animate_generation()
    else:
        for _ in gen.generate():
            pass

    if not gen.perfect:
        gen.imperfect_maze()


def solve_maze(
    maze: list,
    entry: Tuple[int, int],
    exit_point: Tuple[int, int],
) -> str:
    """Return the shortest-path direction
    string between *entry* and *exit_point*."""
    solver = MazeSolver(maze, entry, exit_point)
    return solver.solve()


def move_player(gen: Gen, player: Point, move_key: str) -> Point:
    """Return the next player position if movement is possible."""
    wall_bit = MOVE_KEYS.get(move_key.upper(), MOVE_KEYS.get(move_key))
    if wall_bit is None:
        print("Use W/A/S/D or arrow keys to move!")
        return player

    cell = gen.maze[player.y][player.x]
    if cell & wall_bit:
        print("A wall blocks the way!")
        return player

    offset = Grid.offset[wall_bit]
    next_player = player + offset

    if not (0 <= next_player.x < gen.width and 0 <= next_player.y < gen.height):  # noqa E501
        print("You cannot leave the maze!")
        return player

    if next_player in gen.get_fourty_two():
        print("The 42 logo blocks the way!")
        return player

    next_cell = gen.maze[next_player.y][next_player.x]
    if next_cell & Grid.opposite[wall_bit]:
        print("A wall blocks the way!")
        return player

    return next_player


def interactive_loop(
    cfg: MazeConfig,
    gen: Gen,
    solution: Optional[str],
) -> None:
    """Run the interactive menu loop for regeneration,
    display, and colour toggles."""
    entry: Tuple[int, int] = (cfg.entry.x, cfg.entry.y)
    exit_point: Tuple[int, int] = (cfg.exit.x, cfg.exit.y)

    show_path = False
    animate = False
    player = Point(entry[0], entry[1])

    while True:
        _print_menu(show_path, animate, gen, player)
        try:
            choice = _read_single_key().strip()
        except (EOFError, KeyboardInterrupt):
            print("\nGoodbye!")
            break

        if choice == "1":
            # Regenerate
            print("Generating new maze...")
            if not gen:
                gen = build_generator(cfg)
            else:
                gen.new_maze_seed(random.randint(0, 2**31))
            generate_maze(gen, animate=animate)
            player = Point(entry[0], entry[1])

            try:
                solution = solve_maze(gen.maze, entry, exit_point)
            except Exception as exc:
                solution = None
                print(
                    f"Warning: unable to solve regenerated maze: {exc}!",
                    file=sys.stderr,
                )

            try:
                write_output_file(
                    cfg.output_file, gen.maze, entry, exit_point, solution
                )
            except OSError as exc:
                print(
                    f"Could not write output file: {exc}!",
                    file=sys.stderr,
                )

            gen.print_maze(
                solution_path=solution or "",
                show_path=show_path,
                player=player,
            )

        elif choice == "2":
            # Toggle solution path
            if solution is None:
                print("No solution available for the current maze!")
            else:
                show_path = not show_path
                gen.print_maze(
                    solution_path=solution,
                    show_path=show_path,
                    player=player,
                )

        elif choice == "3":
            # Rotate wall colour
            gen.rotate_colours()
            gen.print_maze(
                solution_path=solution or "",
                show_path=show_path,
                player=player,
            )

        elif choice == "4":
            # Toggle animation
            animate = not animate
            status = "enabled" if animate else "disabled"
            gen.new_maze_seed(gen.seed)
            generate_maze(gen, animate=animate)
            player = Point(entry[0], entry[1])
            print(f"Animation {status}!")

        elif choice == "5":
            current = gen._active_key
            for item in gen.generator.keys():
                if item != current:
                    gen._active_key = item
                    print(gen._active_key)
            gen.new_maze_seed(gen.seed)
            generate_maze(gen, animate=animate)
            player = Point(entry[0], entry[1])

        elif choice == "6":
            new_seed = ask_for_seed(gen, animate)
            gen.new_maze_seed(int(new_seed))
            generate_maze(gen, animate=animate)
            player = Point(entry[0], entry[1])
            gen.print_maze(player=player)

        elif choice == "7":
            print("Move (W/A/S/D or arrow): ", end="", flush=True)
            move_key = _read_single_key().strip()
            if player == gen.exit:
                print_exit_banner()
            else:
                player = move_player(gen, player, move_key)
            gen.print_maze(
                solution_path=solution or "",
                show_path=show_path,
                player=player,
            )
            if player == gen.exit:
                print_exit_banner()

        elif choice.upper() in MOVE_KEYS:
            if player == gen.exit:
                print_exit_banner()
            else:
                player = move_player(gen, player, choice)
            gen.print_maze(
                solution_path=solution or "",
                show_path=show_path,
                player=player,
            )
            if player == gen.exit:
                print_exit_banner()

        elif choice == "8":
            print("Goodbye!")
            break

        else:
            print("Invalid choice, please enter 1-8!")


def ask_for_seed(gen: Gen, animate: bool) -> int:
    """Asks the user to enter a seed and retries until a valid key is given"""
    seed_string = input("Enter new seed: ")
    try:
        new_seed = int(seed_string)
        if new_seed <= 0:
            raise ValueError("Seed must be bigger than 0!")
    except ValueError as exc:
        print(f"{exc}")
        return ask_for_seed(gen, animate)
    return new_seed


def main() -> None:
    """Parse args, generate the first maze, write output, start the loop."""
    if len(sys.argv) != 2:
        print(
            "Usage: python3 a_maze_ing.py <config_file>",
            file=sys.stderr,
        )
        sys.exit(1)

    config_path = sys.argv[1]

    # Parse config
    try:
        cfg = parse_config_file(config_path)
    except ConfigError as exc:
        print(f"Configuration error: {exc}", file=sys.stderr)
        sys.exit(1)

    entry: Tuple[int, int] = (cfg.entry.x, cfg.entry.y)
    exit_point: Tuple[int, int] = (cfg.exit.x, cfg.exit.y)

    # Generate
    gen = build_generator(cfg)
    generate_maze(gen)

    # Solve
    solution: Optional[str]
    try:
        solution = solve_maze(gen.maze, entry, exit_point)
    except Exception as exc:
        solution = None
        print(
            f"Warning: generated maze could not be solved: {exc}",
            file=sys.stderr,
        )

    # Write output file
    try:
        write_output_file(
            cfg.output_file, gen.maze, entry, exit_point, solution
        )  # noqa E501
        print(f"Maze written to '{cfg.output_file}'.")
    except OSError as exc:
        print(f"Could not write output file: {exc}", file=sys.stderr)
        sys.exit(1)

    if solution is not None:
        print(f"Solution ({len(solution)} moves): {solution}")
    else:
        print("Warning: no solution found for this maze.", file=sys.stderr)

    gen.print_maze(
        solution_path=solution or "",
        show_path=False,
        player=Point(entry[0], entry[1]),
    )
    interactive_loop(cfg, gen, solution)


if __name__ == "__main__":
    main()
