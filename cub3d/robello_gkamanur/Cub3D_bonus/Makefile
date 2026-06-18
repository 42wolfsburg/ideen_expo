# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: robello- <<robello-@student.42.fr>>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/16 01:32:50 by robello-          #+#    #+#              #
#    Updated: 2025/12/16 01:32:50 by robello-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ../cub3D_bonus
CC			= cc
CFLAGS		= -Wall -Wextra
OBJ_DIR		= obj
SRC_DIR     = src
LIBFT_DIR	= ../../../common/libft-robello
GNL_DIR		= gnl
MLX_DIR		= ../../../common/minilibx-linux

DIFFICULTY	?= 1
CFLAGS      += -DDIFFICULTY=$(DIFFICULTY)

SRCS =	$(SRC_DIR)/main_bonus.c \
		$(SRC_DIR)/init_bonus.c \
		$(SRC_DIR)/parse_bonus.c \
		$(SRC_DIR)/parse_color_bonus.c \
		$(SRC_DIR)/parse_color1_bonus.c \
		$(SRC_DIR)/parse_header_bonus.c \
		$(SRC_DIR)/copy_map_bonus.c \
		$(SRC_DIR)/parse_map_bonus.c \
		$(SRC_DIR)/check_borders_bonus.c \
		$(SRC_DIR)/validate_chars_bonus.c \
		$(SRC_DIR)/validate_map_bonus.c \
		$(SRC_DIR)/padding_bonus.c \
		$(SRC_DIR)/unreachable_bonus.c \
		$(SRC_DIR)/init_player_bonus.c \
		$(SRC_DIR)/print_map_bonus.c \
		$(SRC_DIR)/print_error_bonus.c \
		$(SRC_DIR)/clean_up_bonus.c \
		$(SRC_DIR)/clean_up1_bonus.c \
		$(SRC_DIR)/load_text_bonus.c \
		$(SRC_DIR)/main_load_bonus.c \
		$(SRC_DIR)/allocate_sprites_bonus.c \
		$(SRC_DIR)/door_anim_bonus.c \
		$(SRC_DIR)/move_bonus.c \
		$(SRC_DIR)/loop_bonus.c \
		$(SRC_DIR)/collision_bonus.c \
		$(SRC_DIR)/resolution_bonus.c \
		$(SRC_DIR)/set_speed_bonus.c \
		$(SRC_DIR)/door1_bonus.c \
		$(SRC_DIR)/reset_bonus.c \
		$(SRC_DIR)/player_range_bonus.c \
		$(SRC_DIR)/render_win_bonus.c \
		$(SRC_DIR)/draw_floor_bonus.c \
		$(SRC_DIR)/draw_sprite_bonus.c \
		$(SRC_DIR)/minimap_bonus.c \
		$(SRC_DIR)/minimap1_bonus.c \
		$(SRC_DIR)/close_bonus.c \
		$(SRC_DIR)/update_bonus.c \
		$(SRC_DIR)/blend_bonus.c \
		$(SRC_DIR)/window_bonus.c \
		$(SRC_DIR)/ray_bonus.c \
		$(SRC_DIR)/ray1_bonus.c \
		$(SRC_DIR)/render_bonus.c \
		$(SRC_DIR)/door_bonus.c \
		$(SRC_DIR)/restart_bonus.c \
		$(GNL_DIR)/get_next_line_bonus.c \
		$(GNL_DIR)/get_next_line_utils_bonus.c

OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

INCLUDES	= -I. -I$(LIBFT_DIR)/includes -I$(GNL_DIR) -I$(MLX_DIR)
LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)
	@echo "\033[0;32m*** cub3D_bonus compiled ***\033[0m"
	@echo "\033[0;35m    Difficulty:    $(shell \
		if [ $(DIFFICULTY) -eq 1 ]; then echo "EASY"; \
		elif [ $(DIFFICULTY) -eq 2 ]; then echo "MEDIUM"; \
		elif [ $(DIFFICULTY) -eq 3 ]; then echo "HARD"; \
		else echo "CUSTOM ($(DIFFICULTY))"; fi)\033[0m"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

easy:
	@$(MAKE) DIFFICULTY=1

medium:
	@$(MAKE) DIFFICULTY=2

hard:
	@$(MAKE) DIFFICULTY=3

difficulty:
	@echo "Current difficulty setting: $(DIFFICULTY)"
	@echo "Usage: make [easy|medium|hard]"
	@echo "Or: make DIFFICULTY=1|2|3"

.PHONY: all clean fclean re easy medium hard difficulty
