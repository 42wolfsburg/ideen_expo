from src.models.MazeConfig import MazeConfig
from typing import Any


class ConfigParser:
    """Parser for maze configuration files in KEY=VALUE format.

    Reads, validates, and parses configuration files containing maze generation
    parameters such as width, height, entry point, exit point, output file,
    and optional seed value.
    """

    _MAX_WIDTH: int = 400
    _MAX_HEIGHT: int = 400
    _MAX_CELLS: int = 100_000

    def __init__(self, config_file: str) -> None:
        """Initialize ConfigParser with path to configuration file.

        Args:
            config_file: Path to the configuration file.
        """
        self._config_file: str = config_file
        self._params: dict[str, Any] = {}
        self._REQUIRED_PARAMS: tuple[str, ...] = (
            "WIDTH",
            "HEIGHT",
            "ENTRY",
            "EXIT",
            "OUTPUT_FILE",
            "PERFECT",
        )

    def parse(self) -> MazeConfig:
        """Parse configuration file and return MazeConfig object.

        Returns:
            MazeConfig: Validated maze configuration object.

        Raises:
            FileNotFoundError: If configuration file does not exist.
            KeyError: If required parameters are missing.
            ValueError: If parameters are invalid.
        """
        self._read_file()
        self._validate()
        return MazeConfig(
            width=self._params["WIDTH"],
            height=self._params["HEIGHT"],
            entry=self._params["ENTRY"],
            exit=self._params["EXIT"],
            output_file=self._params["OUTPUT_FILE"],
            perfect=self._params["PERFECT"],
            seed=self._params["SEED"],
        )

    def _validate(self) -> None:
        """Validate all configuration parameters and parse their values."""
        for key in self._REQUIRED_PARAMS:
            if key not in self._params:
                raise KeyError(f"Missing required key: {key}")

        self._params["WIDTH"] = self._parse_int("WIDTH")
        self._params["HEIGHT"] = self._parse_int("HEIGHT")
        self._params["ENTRY"] = self._parse_coordinates("ENTRY")
        self._params["EXIT"] = self._parse_coordinates("EXIT")
        self._params["PERFECT"] = self._parse_bool("PERFECT")
        self._params["SEED"] = self._parse_seed()

        self._validate_maze_size()
        self._check_bounds("ENTRY")
        self._check_bounds("EXIT")

        if self._params["ENTRY"] == self._params["EXIT"]:
            raise ValueError("ENTRY and EXIT must be different cells")

    def _parse_seed(self) -> int | None:
        """Parse SEED parameter, which is optional.

        Returns:
            int | None: Parsed seed value or None if not provided.

        Raises:
            ValueError: If seed is not a non-negative integer.
        """
        if "SEED" not in self._params:
            return None

        try:
            value = int(self._params["SEED"])
            if value < 0:
                raise ValueError
            return value
        except ValueError:
            raise ValueError(
                f"'SEED' must be a non-negative integer, got '{self._params['SEED']}'"  # noqa: E501
            )

    def _validate_maze_size(self) -> None:
        """Validate maze dimensions against maximum allowed constraints.

        Raises:
            ValueError: If width, height, or total cells exceed limits.
        """
        width = self._params["WIDTH"]
        height = self._params["HEIGHT"]
        cells = width * height

        if width > self._MAX_WIDTH:
            raise ValueError(
                f"WIDTH is too large: {width}. Maximum allowed is {self._MAX_WIDTH}"  # noqa: E501
            )
        if height > self._MAX_HEIGHT:
            raise ValueError(
                f"HEIGHT is too large: {height}. Maximum allowed is {self._MAX_HEIGHT}"  # noqa: E501
            )
        if cells > self._MAX_CELLS:
            raise ValueError(
                f"Maze is too large: {width}x{height} = {cells} cells. "
                f"Maximum allowed is {self._MAX_CELLS}"
            )

    def _read_file(self) -> None:
        """Read configuration file and parse KEY=VALUE pairs.

        Ignores comments (lines starting with #) and empty lines.

        Raises:
            FileNotFoundError: If configuration file does not exist.
            ValueError: If file format is invalid.
        """
        try:
            with open(self._config_file, "r", encoding="utf-8") as f:
                for line in f:
                    line = line.strip()

                    if not line or line.startswith("#"):
                        continue

                    line = line.split("#", 1)[0].strip()
                    if not line:
                        continue

                    if "=" not in line:
                        raise ValueError(
                            f"Error: invalid format '{line}', expected KEY=VALUE"  # noqa: E501
                        )

                    key, value = map(str.strip, line.split("=", 1))
                    if not key:
                        raise ValueError("Error: empty key")
                    if not value:
                        raise ValueError(f"Error: empty value for key '{key}'")

                    self._params[key] = value

        except FileNotFoundError:
            raise FileNotFoundError(f"Config file {self._config_file} not found.")  # noqa: E501

    def _check_bounds(self, key: str) -> None:
        """Check if coordinates are within maze bounds.

        Args:
            key: Configuration key (e.g., 'ENTRY' or 'EXIT').

        Raises:
            ValueError: If coordinates are out of bounds.
        """
        row, col = self._params[key]   # stored as (row, col) = (y, x)
        w, h = self._params["WIDTH"], self._params["HEIGHT"]
        if col >= w or row >= h:
            raise ValueError(
                f"'{key}' ({col},{row}) is out of bounds ({w}x{h})"
            )

    def _parse_int(self, key: str) -> int:
        """Parse integer parameter.

        Args:
            key: Configuration key to parse.

        Returns:
            int: Parsed positive integer.

        Raises:
            ValueError: If value is not a positive integer.
        """
        try:
            value = int(self._params[key])
            if value <= 0:
                raise ValueError
            return value
        except ValueError:
            raise ValueError(
                f"'{key}' must be a positive integer, got '{self._params[key]}'"  # noqa: E501
            )

    def _parse_coordinates(self, key: str) -> tuple[int, int]:
        """Parse coordinates in 'x,y' format and return as (row, col).

        Args:
            key: Configuration key (e.g., 'ENTRY' or 'EXIT').

        Returns:
            tuple[int, int]: Coordinates as (row, col).

        Raises:
            ValueError: If format is invalid or coordinates are negative.
        """
        try:
            coordinates = self._params[key].split(",")
            if len(coordinates) != 2:
                raise ValueError

            x = int(coordinates[0].strip())
            y = int(coordinates[1].strip())
            if x < 0 or y < 0:
                raise ValueError

            return (y, x)
        except ValueError:
            raise ValueError(
                f"'{key}' must be 'x,y' format, got '{self._params[key]}'"
            )

    def _parse_bool(self, key: str) -> bool:
        """Parse boolean parameter ('true' or 'false').

        Args:
            key: Configuration key to parse.

        Returns:
            bool: Parsed boolean value.

        Raises:
            ValueError: If value is not 'true' or 'false' (case-insensitive).
        """
        value = self._params[key].strip().lower()

        if value == "true":
            return True
        if value == "false":
            return False
        raise ValueError(f"'{key}' must be True/False, got '{self._params[key]}'")  # noqa: E501
