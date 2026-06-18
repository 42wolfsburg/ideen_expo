from src.models.Maze import Maze


class MazeWriter:
    """Writes a maze to a file in hexadecimal format.

    Exports the maze structure, entry, exit, and solution path in the format
    specified by the project requirements.
    """

    def __init__(self, maze: Maze, path: str, output_file: str) -> None:
        """Initialize MazeWriter.

        Args:
            maze: The maze to write.
            path: Solution path as a string of directions (N/E/S/W).
            output_file: Path to the output file.
        """
        self._maze = maze
        self._path = path
        self._output_file = output_file

    def write(self) -> None:
        """Write maze to output file in hexadecimal format.

        Output format:
            - Maze grid as hex values (one row per line).
            - Empty line.
            - Entry coordinates.
            - Exit coordinates.
            - Shortest path as direction string.

        Raises:
            IOError: If writing to file fails.
        """
        try:
            with open(self._output_file, "w", encoding="utf-8") as f:
                for row in self._maze.grid:
                    hex_row = ""
                    for cell in row:
                        hex_row += format(cell.to_bits(), "X")
                    f.write(hex_row + "\n")

                f.write("\n")
                f.write(f"{self._maze.entry[1]},{self._maze.entry[0]}\n")
                f.write(f"{self._maze.exit[1]},{self._maze.exit[0]}\n")
                f.write(self._path + "\n")

        except IOError as e:
            raise IOError(f"Failed to write maze to {self._output_file}: {e}")
