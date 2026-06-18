from src.ConfigParser import ConfigParser
from src.MazeVisualizer import MazeVisualizer
from src.MazeGenerator import MazeGenerator
from src.MazeSolver import MazeSolver
from src.MazeWriter import MazeWriter
from src.MazeValidator import MazeValidator
import sys


def main() -> None:
    """Main entry point for the maze generator and visualizer.

    Reads configuration from a file, generates a maze, finds the shortest path,
    writes the maze to an output file, and launches an interactive visualizer.

    The program expects exactly one command-line argument: the path to a
    configuration file containing maze generation parameters.
    """
    if len(sys.argv) != 2:
        print("Usage: python3 a_maze_ing.py <config.txt>")
        sys.exit(1)

    try:
        config = ConfigParser(sys.argv[1]).parse()
    except (FileNotFoundError, KeyError, ValueError) as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)

    try:
        mazegen = MazeGenerator(config.width, config.height, config.seed)
        maze = mazegen.generate(config.entry, config.exit, config.perfect)
        validator = MazeValidator(maze.grid, maze.width, maze.height)
        if not validator.is_valid():
            print(  # noqa: E501
                "Warning: maze structure is invalid (open 3x3 area detected)",
                file=sys.stderr
            )
        path = MazeSolver(maze).shortest_path()
        MazeWriter(maze, path, config.output_file).write()
    except ValueError as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)

    try:
        MazeVisualizer(config).run()
    except Exception as e:
        print(f"Fatal error: {e}", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()
