# Shared Libraries

`minilibx-linux/` is the shared Linux MiniLibX copy used by projects in this
workspace.

Use this for classic 42 MiniLibX projects on Linux. Do not use it for MLX42 or
macOS MiniLibX projects; those are different libraries with different build and
linking requirements.

`mlx42/` is the shared MLX42 copy used by projects that use the MLX42 API, such
as `so_long/nradin`'s bonus target.

`libft/` is the shared flat-layout libft used by `fdf/triedel`,
`cub3d/triedel_mcruz-sa`, and `cub3d/alappas`.

`libft-dyarkovs/` is the shared libft variant with the `src/ft_printf` and
`src/get_next_line` layout used by `fdf/dyarkovs` and
`cub3d/mperetia_dyarkovs`.

`libft-robello/` is the shared libft variant with the `includes/` and `srcs/`
layout used by `cub3d/robello_gkamanur`.
