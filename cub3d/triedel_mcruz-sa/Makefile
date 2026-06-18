# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: triedel <triedel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/13 17:07:50 by triedel           #+#    #+#              #
#    Updated: 2024/08/15 14:26:09 by triedel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 				= cub3D
NAME_BONUS			= cub3D_bonus

CC					= cc
CFLAGS_COMMON		= -Wall -Wextra -Werror
CFLAGS_COMMON		= -O3
CFLAGS_COMMON		+= $(INC)
CFLAGS				= $(CFLAGS_COMMON) -Icub3d/inc
CFLAGS_BONUS		= $(CFLAGS_COMMON) -Icub3d_bonus/inc
# CFLAGS_COMMON				+= -DTEST=1
# CFLAGS_COMMON		+= -g
# CFLAGS_COMMON		+= -fsanitize=leak,address

# for gcc, disable function cast warning
ifeq ($(CC),gcc)
	CFLAGS_COMMON		+= -Wno-cast-function-type
endif

LDLIBS				+= -lm

SRC					= cub3d/src/color.c \
 						cub3d/src/display.c \
						cub3d/src/game/game_actions.c \
						cub3d/src/game/game.c \
						cub3d/src/game/game_deinit.c \
						cub3d/src/game/game_draw.c \
						cub3d/src/game/game_draw_frame.c \
						cub3d/src/game/game_draw_overlays.c \
						cub3d/src/game/game_floor.c \
						cub3d/src/game/game_hooks.c \
						cub3d/src/game/game_init.c \
						cub3d/src/game/game_init_textures.c \
						cub3d/src/game/game_init_utils.c \
						cub3d/src/game/game_input.c \
						cub3d/src/game/game_minimap.c \
						cub3d/src/game/game_mouse.c \
						cub3d/src/game/game_object.c \
						cub3d/src/game/game_object_pixel.c \
						cub3d/src/game/game_object_pixel2.c \
						cub3d/src/game/game_ray.c \
						cub3d/src/game/game_render.c \
						cub3d/src/game/game_update_collisions.c \
						cub3d/src/game/game_update_move.c \
						cub3d/src/game/game_update_obj.c \
						cub3d/src/game/game_update_physics.c \
						cub3d/src/hitlist.c \
						cub3d/src/img/img.c \
						cub3d/src/img/img_draw.c \
						cub3d/src/img/img_fade.c \
						cub3d/src/img/img_put.c \
						cub3d/src/img/img_pxl.c \
						cub3d/src/img/img_text.c \
						cub3d/src/input.c \
						cub3d/src/main.c \
						cub3d/src/map/map_allocation.c \
						cub3d/src/map/map.c \
						cub3d/src/map/map_checks_2.c \
						cub3d/src/map/map_checks.c \
						cub3d/src/map/map_color.c \
						cub3d/src/map/map_coordinates_2.c \
						cub3d/src/map/map_coordinates.c \
						cub3d/src/map/map_error_handling.c \
						cub3d/src/map/map_ft_atof.c \
						cub3d/src/map/map_plane_parsing.c \
						cub3d/src/map/map_squares.c \
						cub3d/src/map/map_utils_2.c \
						cub3d/src/map/map_utils.c \
						cub3d/src/matrix_texture.c \
						cub3d/src/raycast.c \
						cub3d/src/raymarch.c \
						cub3d/src/utils/utils_bits.c \
						cub3d/src/utils/utils.c \
						cub3d/src/utils/utils_direction.c \
						cub3d/src/utils/utils_file.c \
						cub3d/src/utils/utils_float.c \
						cub3d/src/utils/utils_rect.c \
						cub3d/src/utils/utils_str.c \
						cub3d/src/vector/init.c \
						cub3d/src/vector/vector.c \
						cub3d/src/vector/vector_ops_basic.c \
						cub3d/src/vector/vector_ops_extra.c
SRC_BONUS			= cub3d_bonus/src/color.c \
						cub3d_bonus/src/display.c \
						cub3d_bonus/src/game/game_actions.c \
						cub3d_bonus/src/game/game.c \
						cub3d_bonus/src/game/game_deinit.c \
						cub3d_bonus/src/game/game_draw.c \
						cub3d_bonus/src/game/game_draw_frame.c \
						cub3d_bonus/src/game/game_draw_overlays.c \
						cub3d_bonus/src/game/game_floor.c \
						cub3d_bonus/src/game/game_hooks.c \
						cub3d_bonus/src/game/game_init.c \
						cub3d_bonus/src/game/game_init_textures.c \
						cub3d_bonus/src/game/game_init_utils.c \
						cub3d_bonus/src/game/game_input.c \
						cub3d_bonus/src/game/game_minimap.c \
						cub3d_bonus/src/game/game_mouse.c \
						cub3d_bonus/src/game/game_object.c \
						cub3d_bonus/src/game/game_object_pixel2.c \
						cub3d_bonus/src/game/game_object_pixel.c \
						cub3d_bonus/src/game/game_ray.c \
						cub3d_bonus/src/game/game_render.c \
						cub3d_bonus/src/game/game_update_collisions.c \
						cub3d_bonus/src/game/game_update_move.c \
						cub3d_bonus/src/game/game_update_obj.c \
						cub3d_bonus/src/game/game_update_physics.c \
						cub3d_bonus/src/hitlist.c \
						cub3d_bonus/src/img/img.c \
						cub3d_bonus/src/img/img_draw.c \
						cub3d_bonus/src/img/img_fade.c \
						cub3d_bonus/src/img/img_put.c \
						cub3d_bonus/src/img/img_pxl.c \
						cub3d_bonus/src/img/img_text.c \
						cub3d_bonus/src/input.c \
						cub3d_bonus/src/main.c \
						cub3d_bonus/src/map/map_allocation.c \
						cub3d_bonus/src/map/map.c \
						cub3d_bonus/src/map/map_checks_2.c \
						cub3d_bonus/src/map/map_checks.c \
						cub3d_bonus/src/map/map_color.c \
						cub3d_bonus/src/map/map_coordinates_2.c \
						cub3d_bonus/src/map/map_coordinates.c \
						cub3d_bonus/src/map/map_error_handling.c \
						cub3d_bonus/src/map/map_ft_atof.c \
						cub3d_bonus/src/map/map_plane_parsing.c \
						cub3d_bonus/src/map/map_squares.c \
						cub3d_bonus/src/map/map_utils_2.c \
						cub3d_bonus/src/map/map_utils.c \
						cub3d_bonus/src/matrix_texture.c \
						cub3d_bonus/src/raycast.c \
						cub3d_bonus/src/raymarch.c \
						cub3d_bonus/src/utils/utils_bits.c \
						cub3d_bonus/src/utils/utils.c \
						cub3d_bonus/src/utils/utils_direction.c \
						cub3d_bonus/src/utils/utils_file.c \
						cub3d_bonus/src/utils/utils_float.c \
						cub3d_bonus/src/utils/utils_rect.c \
						cub3d_bonus/src/utils/utils_str.c \
						cub3d_bonus/src/vector/init.c \
						cub3d_bonus/src/vector/vector.c \
						cub3d_bonus/src/vector/vector_ops_basic.c \
						cub3d_bonus/src/vector/vector_ops_extra.c

ASSETS_DIR			= assets
ASSETS_CODE			= $(ASSETS_DIR)/src.all
ASSETS				= $(ASSETS_DIR)

# object files in separate dir
OBJ					= $(SRC:.c=.o)
OBJ_BONUS			= $(SRC_BONUS:.c=.o)

# mandatory
all: $(NAME)

include libmlx.mk
include libft.mk

run: $(NAME_BONUS)
	./$(NAME_BONUS) lvl/level0.cub

mrun: $(NAME)
	./$(NAME) test.cub

$(NAME): $(LIBMLX) $(LIBFT) $(ASSETS) $(OBJ)
	$(CC) -o "$@" $(CFLAGS) $(CPPFLAGS) $(OBJ) $(LDFLAGS) $(LDLIBS)

$(NAME_BONUS): $(LIBMLX) $(LIBFT) $(ASSETS) $(OBJ_BONUS)
	$(CC) -o "$@" $(CFLAGS) $(CPPFLAGS) $(OBJ_BONUS) $(LDFLAGS) $(LDLIBS)

bonus: $(NAME_BONUS)

# compile object file for bonus with their respective include flags
%.o: %.c
	if [ "$(filter $@,$(OBJ))" = "$@" ]; then \
		$(CC) -c -o "$@" $(CFLAGS) $(CPPFLAGS) $^; \
	else \
		$(CC) -c -o "$@" $(CFLAGS_BONUS) $(CPPFLAGS) $^; \
	fi

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean
	$(MAKE) $(NAME)

# extra tooling
assets:
	echo "===== Downloading assets from GoogleDrive - this will take a moment ====="
	curl -o assets.tgz 'https://drive.usercontent.google.com/download?id=12bpZEJ5idxobmoOThvQ4Y7HMVNoCDrWk&export=download&authuser=0'
	tar xvf assets.tgz && rm assets.tgz
	-mv assets/textures ./
	-ln -s ./textures ./textures/wolfenstein

$(ASSETS_CODE): $(SRC_BONUS)
	cat $(SRC_BONUS) >$@

doc:
	docker build -t doc .
	docker run --rm -v $(PWD):/mnt -it doc doxygen Doxyfile
	@firefox doc/html/annotated.html

header:
	cproto $(INC) $(SRC) | sed s/_Bool/bool/ | \
		python3 tools/filter.py

norm:
	norminette cub3d cub3d_bonus

mleak: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) test.cub

leak: $(NAME_BONUS)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME_BONUS) test.cub

.PHONY: all clean fclean re doc leak mleak run mrun header
