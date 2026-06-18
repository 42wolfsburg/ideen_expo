from typing import Final

DIRECTIONS: Final[set[str]] = {"N", "S", "E", "W"}

OPPOSITE_DIRECTIONS: Final[dict[str, str]] = {
    "N": "S",
    "S": "N",
    "E": "W",
    "W": "E"
}

DIRECTION_DELTAS: Final[dict[str, tuple[int, int]]] = {
    "N": (-1, 0),
    "S": (1, 0),
    "E": (0, 1),
    "W": (0, -1),
}
