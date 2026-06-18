# So Long

A 2D tile-based game project of the 42school curriculum in C using MinilibX graphics library: 

Navigate through a map, collect items, and reach the exit to win.

## Project Overview

**So Long** is a game where you:
- Move the player character through a rectangular map
- Collect all collectibles (`C`) on the map
- Reach the exit (`E`) after collecting everything
- Track your moves and see them printed to the terminal

The game uses tile-based graphics with custom textures and supports keyboard input for smooth movement.

## Requirements

### System Dependencies
- Linux with X11 support
- GCC compiler
- X11 development libraries (`libx11-dev`, `libxext-dev`)

### Project Structure
```
so_long/
├── libft/              # Custom C library (string, memory, I/O functions)
├── mlx/                # MinilibX graphics library (must unzip from provided .zip)
├── src/                # Game source code
├── map/                # Game maps (.ber files)
├── textures/           # Game sprite files (.xpm)
├── Makefile            # Build configuration
└── README.md           # This file
```

## Installation & Setup

### 1. Extract MinilibX

```bash
# Extract the provided mlx.zip to the project root
unzip mlx.zip -d /path/to/so_long/

# Verify the mlx directory exists
ls -la so_long/mlx/
```

### 2. Install System Dependencies (if needed)

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install libx11-dev libxext-dev
```

**Fedora/RHEL:**
```bash
sudo dnf install libX11-devel libXext-devel
```

## Building

### Compile the Project

```bash
cd /path/to/so_long
make
```

This will:
1. Build the custom `libft` library
2. Build the MinilibX library
3. Compile the game source files
4. Link everything into the `so_long` executable

### Other Make Commands

```bash
make re       # Clean and rebuild everything
make clean    # Remove object files
make fclean   # Remove all generated files (including executable)
```

## Usage

### Running the Game

```bash
./so_long map/minimal.ber
```

Provide a `.ber` map file as the argument. Available maps:
- `map/minimal.ber` - Smallest map (for testing)
- `map/mapsmall.ber` - Small map
- `map/test.ber` - Medium map
- `map/large.ber` - Large map

### Controls

| Key | Action |
|-----|--------|
| `W` / `↑` | Move up |
| `S` / `↓` | Move down |
| `A` / `←` | Move left |
| `D` / `→` | Move right |
| `ESC` | Exit game |

## Map Format

Map files use the `.ber` format:
- `1` = Wall
- `0` = Ground (walkable)
- `P` = Player starting position (exactly one required)
- `C` = Collectible (at least one required)
- `E` = Exit (exactly one required)

Maps must be:
- Rectangular (all rows same length)
- Surrounded by walls
- Valid and solvable

Example minimal map:
```
1111111111
1P0C00000E
1111111111
```

## Features

- ✓ Tile-based graphics rendering with MinilibX
- ✓ Keyboard controls (WASD + arrow keys)
- ✓ Collectible items
- ✓ Exit gate (opens when all items collected)
- ✓ Move counter displayed on window
- ✓ Terminal output for debugging
- ✓ Map validation (rectangular, closed walls, valid elements)
- ✓ Path validation (ensures exit is reachable)

## Game Libraries

### libft
Custom C library included in the project with:
- String manipulation functions
- Memory management utilities
- Character classification
- Printf implementation
- Get next line (file reading)

### MinilibX
Graphics library for X11 window management and image rendering.
- Window creation and management
- Image rendering
- Keyboard event handling

## Architecture

The game is organized into several modules:

| File | Purpose |
|------|---------|
| `main.c` | Entry point, map loading, validation |
| `initialise.c` | Game state initialization |
| `moving_it.c` | Player movement logic |
| `key_hooks.c` | Keyboard input handling |
| `checking_it.c` | Map validation functions |
| `freeing_it.c` | Memory cleanup |
| `terminal_it.c` | Terminal output/debugging |
| `utils.c` | Helper functions |

## Compilation Flags

The project uses strict compiler flags for code quality:
```
-Wall -Werror -Wextra
```

This ensures:
- All warnings are treated as errors
- No undefined behavior is tolerated
- Code quality is maintained

## Troubleshooting

### "cannot open shared object file" error
```bash
# Make sure X11 libraries are installed
ldconfig -p | grep libX11
```

### "Map not found" error
Ensure you're running from the project root directory and provide the correct map path:
```bash
./so_long map/minimal.ber  # Correct
./so_long minimal.ber      # Wrong - will not find the file
```

### Window doesn't appear
- Ensure X11 is running (should be automatic on Linux with display server)
- Check DISPLAY variable: `echo $DISPLAY`
- Verify MinilibX built correctly: `ls mlx/libmlx.a`

## Project Info

- **Created:** 2024
- **Author:** jastomme (42 Wolfsburg student)
- **School:** 42 School
- **Language:** C
- **Status:** Complete

## License

This is an educational project created as part of 42 School curriculum.
