# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: robello <robello-@student.42.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/25 22:55:37 by robello           #+#    #+#              #
#    Updated: 2026/01/26 19:11:35 by robello          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Directories
SRC_DIR = source/src
OBJ_DIR = obj
INC_DIR = source/includes
MLX_DIR = ../../../common/minilibx-linux
LIBFT_DIR = ../../../common/libft-robello

# MiniLibX
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# Source files
# Core
SRC = $(SRC_DIR)/main.c \

SRC += $(SRC_DIR)/events/window.c \
	   $(SRC_DIR)/events/events.c \
	   $(SRC_DIR)/events/main_utils.c \
	   $(SRC_DIR)/events/keys.c \
	   $(SRC_DIR)/events/utils.c \
	   $(SRC_DIR)/events/debug.c \
	   $(SRC_DIR)/events/print_map.c \

# Parsing module
SRC += $(SRC_DIR)/parsing/colors_xpn/check_rgb.c \
       $(SRC_DIR)/parsing/colors_xpn/colors.c \
	   $(SRC_DIR)/parsing/colors_xpn/extract_texture.c \
	   $(SRC_DIR)/parsing/colors_xpn/f_c.c \
	   $(SRC_DIR)/parsing/colors_xpn/parse_rgb.c \
	   $(SRC_DIR)/parsing/colors_xpn/parse_textures.c \
	   $(SRC_DIR)/parsing/colors_xpn/valid_xpm_path.c \
	   $(SRC_DIR)/parsing/colors_xpn/xpm_file_check.c \
	   $(SRC_DIR)/parsing/initialization/init_data.c \
	   $(SRC_DIR)/parsing/initialization/init_player.c \
	   $(SRC_DIR)/parsing/map/alloc_free_grid.c \
	   $(SRC_DIR)/parsing/map/free_data.c \
	   $(SRC_DIR)/parsing/map/free_map.c \
	   $(SRC_DIR)/parsing/map/pad_and_copy.c \
	   $(SRC_DIR)/parsing/map/parser_map.c \
	   $(SRC_DIR)/parsing/map/read_map_utils.c \
	   $(SRC_DIR)/parsing/map/read_map.c \
	   $(SRC_DIR)/parsing/parse/check_enclosure.c \
	   $(SRC_DIR)/parsing/parse/parse_config_utils.c \
	   $(SRC_DIR)/parsing/parse/parse_config.c\
	   $(SRC_DIR)/parsing/parse/parse_cub_utils.c \
	   $(SRC_DIR)/parsing/parse/parser_cub.c \
	   $(SRC_DIR)/parsing/utils/gnl.c \
	   $(SRC_DIR)/parsing/utils/parser_utils.c \
	   $(SRC_DIR)/parsing/validation/borders.c \
	   $(SRC_DIR)/parsing/validation/column.c \
	   $(SRC_DIR)/parsing/validation/empty_column.c \
	   $(SRC_DIR)/parsing/validation/empty_row.c \
	   $(SRC_DIR)/parsing/validation/parser_validate.c \
	   $(SRC_DIR)/parsing/validation/rows.c \
	   $(SRC_DIR)/parsing/validation/valid_map.c \
	   $(SRC_DIR)/parsing/validation/valid_player.c \
	   
# Rendering module
SRC += $(SRC_DIR)/rendering/render/render_background.c \
	   $(SRC_DIR)/rendering/render/render_ceiling.c \
	   $(SRC_DIR)/rendering/render/render_floor.c \
	   $(SRC_DIR)/rendering/render/render_load.c \
	   $(SRC_DIR)/rendering/render/render_pixel.c \
	   $(SRC_DIR)/rendering/render/render.c \
	   $(SRC_DIR)/rendering/raycast/init_raycast.c \
	   $(SRC_DIR)/rendering/raycast/text_raycast.c \
	   $(SRC_DIR)/rendering/raycast/raycast.c \
	   $(SRC_DIR)/rendering/performance/perf_frame.c \
	   $(SRC_DIR)/rendering/performance/perf_column.c \
	   $(SRC_DIR)/rendering/performance/performance.c \
	   $(SRC_DIR)/rendering/smooth_render.c \
	   $(SRC_DIR)/rendering/movement/rotate.c \
	   $(SRC_DIR)/rendering/movement/straight.c \
	   $(SRC_DIR)/rendering/minimap/minimap.c \
	   $(SRC_DIR)/rendering/minimap/minimap_grid.c \

# Object files (in obj/ directory)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Colors for output
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
BLUE = \033[0;34m
NC = \033[0m # No Color

all: $(NAME)

$(MLX_LIB):
	@echo "$(YELLOW)Compiling MiniLibX...$(NC)"
	@make -C $(MLX_DIR) > /dev/null 2>&1 || true
	@echo "$(GREEN)✓ MiniLibX compiled$(NC)"

$(LIBFT_LIB):
	@echo "$(YELLOW)Compiling libft...$(NC)"
	@make -C $(LIBFT_DIR) > /dev/null 2>&1 || true
	@echo "$(GREEN)✓ libft compiled$(NC)"

# Create obj directory and subdirectories if they don't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/rendering
	@echo "$(BLUE)✓ Created $(OBJ_DIR) directory structure$(NC)"

$(NAME): $(MLX_LIB) $(LIBFT_LIB) $(OBJ_DIR) $(OBJ)
	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
	@$(CC) $(OBJ) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(NC)"

# Compilation rule: src/file.c -> obj/file.o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)/includes -c $< -o $@
	
clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)✓ Clean done$(NC)"

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(NC)"
	@rm -f $(NAME)
	@echo "$(GREEN)✓ Full clean done$(NC)"

re: fclean all

run: all
	@echo "$(GREEN)Running $(NAME)...$(NC)"
	@$(NAME) ../maps/test.cub

valgrind: all
	@echo "$(GREEN)Running $(NAME) with valgrind...$(NC)"
	@valgrind --leak-check=full --show-leak-kinds=all $(NAME) ../maps/test.cub

# Debug: show variables
debug:
	@echo "$(BLUE)===== Makefile Debug Info =====$(NC)"
	@echo "$(YELLOW)NAME:$(NC) $(NAME)"
	@echo "$(YELLOW)CC:$(NC) $(CC)"
	@echo "$(YELLOW)CFLAGS:$(NC) $(CFLAGS)"
	@echo "$(YELLOW)SRC_DIR:$(NC) $(SRC_DIR)"
	@echo "$(YELLOW)OBJ_DIR:$(NC) $(OBJ_DIR)"
	@echo "$(YELLOW)INC_DIR:$(NC) $(INC_DIR)"
	@echo "$(YELLOW)MLX_DIR:$(NC) $(MLX_DIR)"
	@echo "$(YELLOW)LIBFT_DIR:$(NC) $(LIBFT_DIR)"
	@echo "$(YELLOW)Number of source files:$(NC) $(words $(SRC))"
	@echo "$(YELLOW)Number of object files:$(NC) $(words $(OBJ))"

.PHONY: all clean fclean re run valgrind debug
