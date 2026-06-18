# IdeenExpo Hannover Demo Guide

This repository contains several small 42-style projects prepared for live demos
at IdeenExpo in Hannover. The goal is to make the projects easy to compile,
run, and tweak while visitors are watching.

Most C graphics projects use the shared libraries in `common/`:

- `common/minilibx-linux/` for classic MiniLibX projects.
- `common/mlx42/` for MLX42 projects.
- `common/libft*` for shared libft variants used by multiple projects.

Keep those shared folders in place. They avoid having a separate MiniLibX or
libft copy inside every project.

## General Workflow

For most C projects:

```bash
cd path/to/project
make
./program_name path/to/map
```

Common Makefile targets:

- `make`: build the normal executable.
- `make bonus`: build the bonus version when the project has one.
- `make clean`: remove object files.
- `make fclean`: remove object files and executables.
- `make re`: rebuild from scratch.

If you only edit a map or config file, usually you do not need to recompile. If
you edit `.c` or `.h` files, run `make re`.

## Quick Run Commands

Run commands from the project directory shown in the left column.

| Project | Build | Run example |
| --- | --- | --- |
| `a-maze-ing/ilobov_myaroshu` | `make install` | `make run` |
| `a-maze-ing/kaggour_jbuchins` | `make install` | `make run` |
| `so_long/nradin` | `make` | `./so_long maps/map_1.ber` |
| `so_long/nradin` bonus | `make bonus` | `./so_long maps/map_1_bonus.ber` |
| `so_long/jastomme` | `make` | `./so_long map/minimal.ber` |
| `so_long/pmichale` | `make` | `./so_long mini.ber` |
| `cub3d/triedel_mcruz-sa` | `make` or `make bonus` | `./cub3D lvl/level0.cub` or `./cub3D_bonus lvl/level0.cub` |
| `cub3d/alappas` | `make` or `make bonus` | `./cub3D maps/map1.cub` or `./cub3D_bonus maps/map_bonus.cub` |
| `cub3d/mperetia_dyarkovs` | `make` or `make bonus` | `./cub3D maps/map.cub` |
| `cub3d/robello_gkamanur` | `make` or `make bonus` | `make info` shows available maps and targets |
| `fdf/triedel` | `make` | `make run` or `./fdf m maps/42.fdf` |
| `fdf/dyarkovs` | `make` | `make run` |
| `fractol/cjakobs` | `make` | `./fractol 1 1` |
| `fractol/loandrad` | `make` | `./fractol mandelbrot` or `./fractol julia` |
| `push_swap/*` | `make` | Use the Godot visualiser; see the Push Swap section below |

If a map path is missing in one project, list the available maps:

```bash
find . -name "*.ber" -o -name "*.cub" -o -name "*.fdf"
```

## Simple Tweaks For Visitors

### 1. Change A Maze

For `a-maze-ing` projects, edit `config.txt`.

Example:

```text
WIDTH=20
HEIGHT=15
ENTRY=0,0
EXIT=19,14
OUTPUT_FILE=maze.txt
PERFECT=True
SEED=4242424242
```

Good demo tweaks:

- Change `WIDTH` and `HEIGHT` for a bigger or smaller maze.
- Change `ENTRY` and `EXIT` to move the start and goal.
- Change `SEED` to get a different maze while keeping it reproducible.

Then run:

```bash
make run
```

### 2. Change A so_long Map

Maps use simple characters:

- `1`: wall
- `0`: floor
- `P`: player start
- `E`: exit
- `C`: collectible
- `H` or `V`: enemies in bonus maps, for projects that support them

Example from `so_long/nradin/maps/map_1_bonus.ber`:

```text
111111
1EH001
101C01
100V01
1P0HC1
111111
```

Rules to keep:

- The map must be rectangular.
- The outside border should be walls.
- Keep exactly one `P` and one `E`.
- Keep at least one `C`.
- Use `make bonus` before running maps with `H` or `V` in `so_long/nradin`.

### 3. Change A cub3D Map

Cub3D maps are `.cub` files. The top part configures textures and colors; the
bottom part is the maze.

Common entries:

```text
NO textures/color_stone.xpm
SO textures/color_stone.xpm
EA textures/color_stone.xpm
WE textures/color_stone.xpm

F 0,0,0
C 200,200,200

111111
1000N1
111111
```

Safe demo tweaks:

- Change the maze layout by editing `1` walls and `0` floor tiles.
- Move the player by moving `N`, `S`, `E`, or `W`.
- Change floor and ceiling colors with `F R,G,B` and `C R,G,B`.

Do not replace or edit sprite/texture image files during the event. Many MLX
projects expect exact image dimensions, and a mismatched `.xpm` or `.png` can
break the demo. If a wall should look different, prepare the correctly sized
asset before the event rather than doing it live.

### 4. Change An FdF Shape

FdF maps are grids of numbers. Bigger numbers make higher points.

Example:

```text
0 0 0 0 0
0 1 2 1 0
0 2 4 2 0
0 1 2 1 0
0 0 0 0 0
```

Good demo tweaks:

- Raise one number to create a mountain.
- Use negative numbers to make a valley.
- Add colors in the standard FdF style when supported: `10,0xFF0000`.

Run examples:

```bash
cd fdf/triedel
make
./fdf m maps/42.fdf
```

```bash
cd fdf/dyarkovs
make
make run
```

### 5. Change Fractol Feel

For `fractol/cjakobs`, the zoom speed is intentionally easy to tweak:

```c
zoom_step = 0.08;
```

File:

```text
fractol/cjakobs/src/navigation.c
```

Smaller values feel smoother but require more scroll input. Larger values zoom
faster but can feel jumpy.

Run:

```bash
cd fractol/cjakobs
make
./fractol 1 1
```

The first number chooses the fractal type, and the second chooses a color
palette.

### 6. Run Push Swap With The Visualiser

For `push_swap`, do not demo it by reading the terminal output directly. Use the
Godot visualiser.

Build one of the `push_swap` projects first:

```bash
cd push_swap/radix_lflorin
make
```

Then start the visualiser:

```bash
cd ../Visualiser
./PushSwapVisualiser.x86_64
```

In the visualiser:

- Drag and drop the compiled `./push_swap` executable into the visualiser.
- Press the automation button.
- Let the visualiser run the executable and animate the operations.
- Repeat it several times for each algorithm and let them run in the background

The same workflow works for the other `push_swap/*` implementations after they
are compiled.

## Good Expo Demo Ideas

- Ask a visitor to draw a tiny `so_long` level using `1`, `0`, `P`, `E`, `C`.
- Let someone change `F` and `C` in a `.cub` file and immediately rerun cub3D.
- Change a maze `SEED` and show how the same seed creates the same maze again.
- In FdF, change a single height value and show the terrain spike.
- In Fractol, change `zoom_step`, rebuild, and compare how zooming feels.
- In Push Swap, drag a compiled executable into the visualiser and run the
  automation.

## Troubleshooting

If `make` cannot find MiniLibX, check that the shared library folder exists:

```bash
ls common/minilibx-linux
```

If MLX42 projects fail, check:

```bash
ls common/mlx42
```

If a graphical program opens no window, make sure you are running in a graphical
Linux session, not a plain SSH terminal without display forwarding.

If a `so_long` bonus map says it contains invalid characters, rebuild the bonus
version first:

```bash
make bonus
./so_long maps/map_1_bonus.ber
```

If you get lost during a live demo, return to a known-good state:

```bash
make fclean
make
```

Then run one of the examples from the table above.
