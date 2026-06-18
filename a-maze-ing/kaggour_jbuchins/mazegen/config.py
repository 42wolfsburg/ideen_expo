from dataclasses import dataclass
from pathlib import Path
from typing import Final, Optional


MANDATORY_KEYS: Final[set[str]] = {
    "WIDTH",
    "HEIGHT",
    "ENTRY",
    "EXIT",
    "OUTPUT_FILE",
    "PERFECT",
}

OPTIONAL_KEYS: Final[set[str]] = {
    "SEED",
    "ALGORITHM",
    "DISPLAY_MODE",
}

ALLOWED_KEYS: Final[set[str]] = MANDATORY_KEYS | OPTIONAL_KEYS

DEFAULT_SEED: Final[int] = 4242


class ConfigError(Exception):
    """Raised when the maze configuration file is invalid or missing fields."""


@dataclass(frozen=True)
class Point:
    """An immutable (x, y) integer coordinate used in configuration."""

    x: int
    y: int


@dataclass(frozen=True)
class MazeConfig:
    """Validated, immutable snapshot of all maze configuration values."""

    width: int
    height: int
    entry: Point
    exit: Point
    output_file: str
    perfect: bool
    seed: int
    algorithm: Optional[str] = None
    display_mode: Optional[str] = None


def parse_config_file(file_path: str | Path) -> MazeConfig:
    """Read *file_path* and return a validated MazeConfig.

    Raises ConfigError on any parse or validation failure.
    """
    path = Path(file_path)
    if not path.is_file():
        raise ConfigError(f"Configuration File Path Not Found : {path}")
    raw_values = _read_raw_values(path)
    _validate_required_keys(raw_values)
    _validate_unknown_keys(raw_values)

    width = _parse_positive_int(raw_values["WIDTH"], "WIDTH")
    height = _parse_positive_int(raw_values["HEIGHT"], "HEIGHT")
    entry = _parse_point(raw_values["ENTRY"], "ENTRY")
    exit_point = _parse_point(raw_values["EXIT"], "EXIT")
    output_file = raw_values["OUTPUT_FILE"].strip()
    perfect = _parse_bool(raw_values["PERFECT"], "PERFECT")

    if not output_file:
        raise ConfigError("Output from maze cannot be empty!")

    _validate_coordinates(entry, width, height, "ENTRY")
    _validate_coordinates(exit_point, width, height, "EXIT")

    if entry == exit_point:
        raise ConfigError("ENTRY and EXIT must be different!")

    seed = DEFAULT_SEED
    if "SEED" in raw_values and raw_values["SEED"].strip() != "":
        seed = _parse_int(raw_values["SEED"], "SEED")

    algorithm = raw_values.get("ALGORITHM")
    if algorithm is not None:
        algorithm = algorithm.strip() or None

    display_mode = raw_values.get("DISPLAY_MODE")
    if display_mode is not None:
        display_mode = display_mode.strip() or None

    return MazeConfig(
        width=width,
        height=height,
        entry=entry,
        exit=exit_point,
        output_file=output_file,
        perfect=perfect,
        seed=seed,
        algorithm=algorithm,
        display_mode=display_mode,
    )


def _read_raw_values(path: Path) -> dict[str, str]:
    """Parse *path* into a flat KEY→value mapping.

    Ignores comments and blank lines.
    Raises ConfigError on duplicate keys, malformed lines, or I/O failures.
    """
    raw_values: dict[str, str] = {}

    try:
        with path.open("r") as handle:
            for line_number, raw_line in enumerate(handle, start=1):
                line = raw_line.strip()

                if not line or line.startswith("#"):
                    continue

                if "=" not in line:
                    raise ConfigError(
                        f"Line {line_number}: expected KEY=VALUE format"
                    )

                key, value = line.split("=", maxsplit=1)
                key = key.strip().upper()
                value = value.strip()

                if not key:
                    raise ConfigError(
                        f"Line {line_number}: missing key!"
                    )

                if not value:
                    raise ConfigError(
                        f"Line {line_number}: missing value for key : {key}!"
                    )

                if key in raw_values:
                    raise ConfigError(
                        f"Line {line_number}: duplicate key '{key}'"
                    )

                raw_values[key] = value

    except OSError as exc:
        raise ConfigError(
            f"Failed to read configuration file: {exc}"
        ) from exc

    return raw_values


def _validate_required_keys(raw_values: dict[str, str]) -> None:
    """Raise ConfigError if any mandatory key is absent from *raw_values*."""
    missing = sorted(MANDATORY_KEYS - raw_values.keys())
    if missing:
        missing_keys = ", ".join(missing)
        raise ConfigError(f"Missing mandatory key(s): {missing_keys}")


def _validate_unknown_keys(raw_values: dict[str, str]) -> None:
    """Raise ConfigError if *raw_values* contains keys outside ALLOWED_KEYS."""
    unknown = sorted(set(raw_values.keys()) - ALLOWED_KEYS)
    if unknown:
        unknown_keys = ", ".join(unknown)
        raise ConfigError(f"Unknown key(s): {unknown_keys}")


def _parse_positive_int(value: str, key: str) -> int:
    """Parse *value* as a positive integer for configuration key *key*."""
    parsed = _parse_int(value, key)
    if parsed <= 0:
        raise ConfigError(f"{key} must be greater than 0!")
    return parsed


def _parse_int(value: str, key: str) -> int:
    """Parse *value* as an integer for configuration key *key*."""
    try:
        return int(value)
    except ValueError as exc:
        raise ConfigError(f"{key} must be an integer!") from exc


def _parse_bool(value: str, key: str) -> bool:
    """Parse *value* as a boolean ('true' or 'false') for *key*."""
    lowered = value.strip().lower()
    if lowered == "true":
        return True
    if lowered == "false":
        return False
    raise ConfigError(f"{key} must be True or False!")


def _parse_point(value: str, key: str) -> Point:
    """Parse an 'x,y' string into a Point for configuration key *key*."""
    parts = [part.strip() for part in value.split(",")]
    if len(parts) != 2:
        raise ConfigError(f"{key} must be in x,y format!")
    try:
        x = int(parts[0])
        y = int(parts[1])
    except ValueError as exc:
        raise ConfigError(
            f"{key} coordinates must be integers!"
        ) from exc
    return Point(x=x, y=y)


def _validate_coordinates(
    point: Point, width: int, height: int, key: str
) -> None:
    """Raise ConfigError if *point* lies outside the maze bounds."""
    if point.x < 0 or point.x >= width or point.y < 0 or point.y >= height:
        raise ConfigError(
            f"{key} coordinates {point.x},{point.y} are outside maze bounds "
            f"(width={width}, height={height})."
        )
