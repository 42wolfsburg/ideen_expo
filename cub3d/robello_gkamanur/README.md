*This project has been created as part of the 42 curriculum by gkamanur, robello-.*


##### cub3D Project #####
## DESCRIPTION.

	**cub3D** is a 3D graphical representation of a maze from a first-person perspective, inspired by the world-famous game **Wolfenstein 3D** (1992). This project explores raycasting techniques to render a 3D environment in real-time using the MiniLibX graphics library.




### GOAL.

The primary objective is to implement a raycasting engine that can:
	- Parse configuration files (`.cub`) defining map layout, textures, and colors
	- Render a 3D maze environment from a first-person view
	- Handle player movement and camera rotation
	- Apply wall textures based on orientation (North, South, East, West)
	- Display different colors for floor and ceiling




### PROJECT STRUCTURE.
```
	.
	├── cub3d                    # Mandatory executable
	├── cub3d-bonus              # Bonus executable
	├── cub3D/                   # Mandatory version source code
	├── cub3D_bonus/             # Bonus version source code
	├── libft/                   # Custom C library
	├── minilibx-linux/          # MiniLibX graphics library
	├── textures/                # Shared texture files (64 textures)
	├── maps/                    # Mandatory version maps
	├── maps_bonus/              # Bonus version maps
	└── Makefile                 # Unified build system
```




## INSTRUCTIONS.

### Prerequisites
	- **Operating System:** Linux (tested on Ubuntu)
	- **Compiler:** cc with C99 standard support
	- **Libraries:** X11, Xext (usually pre-installed on Linux)




### INSTALLATION.

1. Clone the repository:
```bash
git clone <repository-url> <folder_name>
cd <folder_name>
```
2. Build the project:
```bash
make
```
3. The executables will be created in the root directory:
   - `cub3d` - Mandatory version
   - `cub3d-bonus` - Bonus version (after `make bonus`)




### COMPILATION.

The project uses a unified Makefile that builds both mandatory and bonus versions:

```bash
make		= Builds mandatory version. (cub3d)

make bonus	= Builds bonus version. (cub3d-bonus)

make clean	= Clean object files.

make fclean	= Full clean (remove binaries).

make re		= Rebuild everything.

```




### EXECUTION.
**Mandatory Version:**
```bash
	./cub3d maps/test.cub
```
**Bonus Version:**
```bash
	./cub3d-bonus maps_bonus/stars.cub
```




### CONTROLS
**Movement:**
	- `W`		- Move forward.
	- `A`		- Strafe left.
	- `S`		- Move backward.
	- `D`		- Strafe right.

**Camera:**
	- `←` (Left Arrow)	- Rotate camera left.
	- `→` (Right Arrow)	- Rotate camera right.
	- `mouse`			- Rotate Camera (bonus version).

**Other:**
	- `ESC`					- Exit program
	- `X` (Close button)	- Exit program
	- ALT + TAB				- Releases mouse from game (bonus version).





### MAP FILE FORMAT

Maps are defined in `.cub` files with the following format:

```
	NO textures/north.xpm
	SO textures/south.xpm
	WE textures/west.xpm
	EA textures/east.xpm

	F 100,69,19
	C 230,133,63

	111111111111111
	100000000000011
	100001110000011
	111000010000011
	100000000000001
	11111111111N001
	100000000000001
	101010101010101
	111100001111001
	111111111111111
```

**Configuration:**
	- `NO/SO/WE/EA`		= Texture paths for each wall orientation.
	- `F`				= Floor color (R,G,B)
	- `C`				= Ceiling color (R,G,B)
	- Map grid:
		`0`				= Empty space.
		`1`				= Wall.
		`N/S/E/W`		= Player starting position.
		`X`				= Enemy.
		`C`				= Collectible.
		`D`				= Door.
		`T`				= Secret door.




### BONUS FEATURES

The bonus version includes additional features:
	- Minimap display.
	- Mouse rotation.
	- Animated sprites.
	- Door mechanics.
	- Enemy.
	- Multiple difficulty levels.
	- Enhanced textures.
	- Performance optimizations.

**Bonus Difficulty Levels:**
```bash
	make easy		= DIFFICULTY=1
	make medium		= DIFFICULTY=2
	make hard		= DIFFICULTY=3
```




## FEATURES

### Mandatory Part
	- ✅ Raycasting engine implementation.
	- ✅ Wall texture mapping (4 directions).
	- ✅ Floor and ceiling color rendering.
	- ✅ Smooth player movement (WASD).
	- ✅ Camera rotation (arrow keys).
	- ✅ Wall collision detection.
	- ✅ Map parsing and validation.
	- ✅ Error handling.
	- ✅ Window management (ESC, X button).

### Bonus Part
	- ✅ Minimap rendering.
	- ✅ Wall collisions detection.
	- ✅ Animated sprites.
	- ✅ Doors that can open/close.
	- ✅ Mouse rotation.
	- ✅ Performance optimizations.
	- ✅ Multiple difficulty settings.
	- ✅ Resolution selection.




## TECHNICAL CHOICES

### Raycasting Algorithm
The project implements the **DDA (Digital Differential Analysis)** algorithm for raycasting:
	1. Cast rays from player position for each screen column.
	2. Calculate distance to nearest wall.
	3. Project wall height based on distance.
	4. Apply textures based on wall orientation.
	5. Render floor and ceiling.

### Graphics Library
**MiniLibX** - A simple X-Window programming API designed for graphics programming education. It provides:
	- Window creation and management.
	- Image manipulation.
	- Event handling (keyboard, mouse).
	- XPM image loading.

### Memory Management
	- All heap allocations are properly freed.
	- No memory leaks (verified with valgrind).
	- Proper cleanup on exit.

### Code Organization
	- **Modular structure:** Separated into parsing, rendering, loading, freeing memory and event handling modules.
	- **Shared libraries:** Both mandatory and bonus versions share libft and MiniLibX.
	- **Single repository:** Consolidated from multiple git repositories for easier management.




## RESOURCES
### Classic References
**Raycasting:**
- [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html) - Comprehensive guide to raycasting with code examples
- [Ray-Casting Tutorial For Game Development And Other Purposes](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/) - Detailed mathematical explanation
- [Wolfenstein 3D Source Code](https://github.com/id-Software/wolf3d) - Original implementation by id Software

**MiniLibX:**
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) - Unofficial but comprehensive documentation
- [42 Docs - Getting started with MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html)

**Graphics Programming:**
- [Computer Graphics from Scratch](https://www.gabrielgambetta.com/computer-graphics-from-scratch/) - Gabriel Gambetta
- [3D Math Primer for Graphics and Game Development](https://gamemath.com/book/) - Fletcher Dunn

**C Programming:**
- [The C Programming Language](https://en.wikipedia.org/wiki/The_C_Programming_Language) - Kernighan & Ritchie
- [Modern C](https://modernc.gforge.inria.fr/) - Jens Gustedt




### AI USAGE

**Tasks where AI assistance was used:**
1. **Bug Fixing:**
	- Identified and fixed buffer overflow in `ft_strtrim` function.
	- Diagnosed texture path resolution issues.
	- Fixed segmentation faults related to memory management.

2. **Code Restructuring:**
	- Unified build system creation (single Makefile for both versions).
	- Git repository consolidation (removing submodules).
	- Project structure reorganization (shared resources).

3. **Documentation:**
	- README.md creation and formatting.
	- Error analysis documentation.
	- Setup and configuration guides.

4. **Testing and Analysis:**
	- Texture compatibility testing.
	- Path resolution debugging.
	- Validation of program execution.




## GENERAL Project INFORMATION.
**School:** 	42 Network.
**Project:** 	cub3D.
**Language:** 	C.
**Graphics:** 	MiniLibX.
**Norm:** 		42 Coding Standard.



## AUTHORS
- **gkamanur** - Mandatory version development.
- **robello-** - Bonus version development.




## ACKNOWLEDGMENTS

	- 42 School for the project subject and resources.
	- id Software for Wolfenstein 3D inspiration.
	- Lode Vandevenne for the raycasting tutorial.
	- The 42 community for testing and feedback.
