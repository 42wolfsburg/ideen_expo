
***This project has been created as part of the 42 curriculum by   gkamanur and robello-***



A 3D graphical representation of a maze using raycasting, inspired by the classic Wolfenstein 3D game engine.

---

## Description

Cub3D is a first-person perspective exploration of a maze rendered using raycasting techniques. 
The project implements a pseudo-3D game engine that creates the illusion of three-dimensional space from a 2D map, similar to how early 90s games like Wolfenstein 3D achieved their visual effects.

### Key Features

- **Raycasting Engine**: Real-time 3D rendering using the DDA (Digital Differential Analyzer) algorithm
- **Textured Walls**: Support for different textures on North, South, East, and West walls (XPM format)
- **Floor and Ceiling**: Customizable colors or textures for floor and ceiling
- **Player Movement**: Smooth WASD movement with arrow key rotation
- **Minimap**: Real-time minimap display showing player position and direction
- **Map Parsing**: Robust `.cub` file parser with comprehensive validation
- **Performance Optimizations**: FPS limiting, column duplication, and batch pixel operations

---

## Instructions

### Prerequisites

- Linux operating system - Ubuntu
- CC : clang default compiler or GCC
- Make
- X11 development libraries (`libx11-dev`, `libxext-dev`)
- MiniLibX library

### Compilation

```bash
# Clone the repository
git clone <repository-url>
cd cub3d

# Compile the project
make

# Clean object files
make clean

# Full clean (including executable)
make fclean

# Recompile
make re
```

### Execution

```bash
./cub3D <map_file.cub>
```

Example:
```bash
./cub3D maps/example.cub
```
# Memory leak check

```bash
valgrind ./cub3D maps/example.cub
```
     
### Map File Format (.cub)

The `.cub` configuration file must contain:

```
NO ./path_to_north_texture.xpm
SO ./path_to_south_texture.xpm
WE ./path_to_west_texture.xpm
EA ./path_to_east_texture.xpm

F 220,100,0       # Floor color (RGB) or texture path
C 225,30,0        # Ceiling color (RGB) or texture path

111111
100101
101001
1100N1
111111
```

Map characters:
- `0` - Empty space (walkable)
- `1` - Wall
- `N`, `S`, `E`, `W` - Player starting position and orientation

### Controls
-------------------------------------------------
| Key           | Action                        |
|---------------|-------------------------------|
| `W`           | Move forward                  |
| `S`           | Move backward                 |
| `A`           | Strafe right                  |
| `D`           | Strafe left                   |
| `Left Arrow`  | Rotate camera left            |
| `Right Arrow` | Rotate camera right           |
| `ESC`         | Exit the game                 |
|-----------------------------------------------|
---

## Project Structure

```
cub3d/
├── includes/
│   ├── cub3d.h          # Main header with structures and definitions
│   ├── parsing.h        # Parsing function prototypes
│   └── rendering.h      # Rendering function prototypes
├── src/
│   ├── main.c           # Entry point
│   ├── events/          # Input handling and window events
│   ├── parsing/         # Map and configuration file parsing
│   │   ├── colors_xpn/  # Color and texture parsing
│   │   ├── initialization/ # Data structure initialization
│   │   ├── map/         # Map loading and processing
│   │   ├── parse/       # Configuration parsing
│   │   ├── utils/       # Parsing utilities (GNL, etc.)
│   │   └── validation/  # Map validation
│   └── rendering/       # Graphics rendering
│       ├── minimap/     # Minimap rendering
│       ├── movement/    # Player movement logic
│       ├── performance/ # FPS and optimization
│       ├── raycast/     # Raycasting algorithm
│       └── render/      # Frame rendering
├── libft/               # Custom C library
├── minilibx-linux/      # MiniLibX graphics library
└── maps/                # Example map files
```

---

## Resources

### Documentation and References

- [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html) - Comprehensive raycasting tutorial
- [Wolfenstein 3D's Map Rendering Explained](https://fabiensanglard.net/wolf3d/) - Technical breakdown by Fabien Sanglard
- [42 Docs - Cub3D](https://harm-smits.github.io/42docs/projects/cub3d) - 42 project documentation
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) - Graphics library reference

### AI Usage Disclosure

AI tools were utilized in the following aspects of this project:

- **Code Documentation**: AI assisted in generating comprehensive inline comments and documentation for complex mathematical calculations in the raycasting algorithm.
- **Debugging Assistance**: AI was consulted to help identify and resolve edge cases in map parsing and validation logic.
- **README Generation**: This README file was created with AI assistance to ensure comprehensive coverage of project requirements.
- **Code Review**: AI was used to review code for potential memory leaks, norm compliance, and optimization opportunities.

All AI-generated suggestions were manually reviewed, tested, and adapted to fit the project requirements and 42 coding standards.

---

## Technical Details

### Raycasting Algorithm

The engine uses the DDA algorithm to cast rays from the player's position for each vertical screen column. Key calculations include:

- **Ray Direction**: Calculated based on player direction and camera plane
- **Wall Distance**: Perpendicular distance to avoid fisheye effect
- **Texture Mapping**: Wall hit position determines texture X coordinate

### Performance Optimizations

- **Column Duplication**: Adjacent columns with similar ray directions share calculations
- **Batch Pixel Operations**: Floor and ceiling rendered using optimized memory operations
- **FPS Limiting**: Configurable frame rate cap to reduce CPU usage

---

