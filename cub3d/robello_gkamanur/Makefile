# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: robello <robello-@student.42.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/26 12:58:59 by robello           #+#    #+#              #
#    Updated: 2026/01/26 19:12:16 by robello          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#                                                                              #
#                      Unified cub3D Makefile                                  #
#                                                                              #
# **************************************************************************** #

MANDATORY_DIR = Cub3D
BONUS_DIR = Cub3D_bonus
LIBFT_DIR = ../../common/libft-robello
MLX_DIR = ../../common/minilibx-linux
TEXTURE_DIR = textures
MAPS_DIR = maps
MAPS_BONUS_DIR = maps_bonus

LIBFT_A = $(LIBFT_DIR)/libft.a
MLX_A = $(MLX_DIR)/libmlx.a
MLX_SO = $(MLX_DIR)/libmlx.so

MANDATORY_BIN = cub3D
BONUS_BIN = cub3D_bonus

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
NC = \033[0m

all: libft mlx mandatory

mandatory: $(LIBFT_A) $(MLX_A)
	@echo "$(YELLOW)═══════════════════════════════════════════════$(NC)"
	@echo "$(CYAN)   Building cub3D (Mandatory)$(NC)"
	@echo "$(YELLOW)═══════════════════════════════════════════════$(NC)"
	@$(MAKE) -C $(MANDATORY_DIR)
	@echo "$(GREEN)✓ cub3D mandatory compiled successfully!$(NC)"
	@echo ""

bonus: $(LIBFT_A) $(MLX_A)
	@echo "$(YELLOW)═══════════════════════════════════════════════$(NC)"
	@echo "$(PURPLE)   Building cub3D_bonus$(NC)"
	@echo "$(YELLOW)═══════════════════════════════════════════════$(NC)"
	@$(MAKE) -C $(BONUS_DIR)
	@echo "$(GREEN)✓ cub3D_bonus compiled successfully!$(NC)"
	@echo ""

easy: $(LIBFT_A) $(MLX_A)
	@$(MAKE) -C $(BONUS_DIR) easy

medium: $(LIBFT_A) $(MLX_A)
	@$(MAKE) -C $(BONUS_DIR) medium

hard: $(LIBFT_A) $(MLX_A)
	@$(MAKE) -C $(BONUS_DIR) hard

libft: $(LIBFT_A)

$(LIBFT_A):
	@echo "$(BLUE)Building libft...$(NC)"
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null 2>&1
	@echo "$(GREEN)✓ libft ready$(NC)"

mlx: $(MLX_A)

$(MLX_A):
	@echo "$(BLUE)Building MiniLibX...$(NC)"
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1 || true
	@if [ -f "$(MLX_A)" ]; then \
		echo "$(GREEN)✓ MiniLibX ready (static library)$(NC)"; \
	elif [ -f "$(MLX_SO)" ]; then \
		echo "$(GREEN)✓ MiniLibX ready (shared library)$(NC)"; \
	else \
		echo "$(YELLOW)⚠  MiniLibX build may have failed$(NC)"; \
	fi

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@$(MAKE) -C $(MANDATORY_DIR) clean
	@$(MAKE) -C $(BONUS_DIR) clean
	@echo "$(GREEN)✓ Clean done$(NC)"

fclean: clean
	@echo "$(RED)Removing binaries and libraries...$(NC)"
	@$(MAKE) -C $(MANDATORY_DIR) fclean
	@$(MAKE) -C $(BONUS_DIR) fclean
	@echo "$(GREEN)✓ Full clean done$(NC)"

re: fclean all

status:
	@echo "$(CYAN)Build status:$(NC)"
	@if [ -f "./$(MANDATORY_BIN)" ]; then \
		echo "$(GREEN)✓ $(MANDATORY_BIN) exists$(NC)"; \
	else \
		echo "$(YELLOW)⚠ $(MANDATORY_BIN) not built$(NC)"; \
	fi
	@if [ -f "./$(BONUS_BIN)" ]; then \
		echo "$(GREEN)✓ $(BONUS_BIN) exists$(NC)"; \
	else \
		echo "$(YELLOW)⚠ $(BONUS_BIN) not built$(NC)"; \
	fi
	@if [ -f "$(LIBFT_A)" ]; then \
		echo "$(GREEN)✓ libft.a exists$(NC)"; \
	else \
		echo "$(YELLOW)⚠ libft.a not built$(NC)"; \
	fi
	@if [ -f "$(MLX_A)" ] || [ -f "$(MLX_SO)" ]; then \
		echo "$(GREEN)✓ MiniLibX exists$(NC)"; \
	else \
		echo "$(YELLOW)⚠ MiniLibX not built$(NC)"; \
	fi

info:
	@echo "$(CYAN)═══════════════════════════════════════════════$(NC)"
	@echo "$(CYAN)   cub3D Project Structure$(NC)"
	@echo "$(CYAN)═══════════════════════════════════════════════$(NC)"
	@echo "$(YELLOW)Directories:$(NC)"
	@echo "  • Mandatory:    $(MANDATORY_DIR)/"
	@echo "  • Bonus:        $(BONUS_DIR)/"
	@echo "  • Shared textures: $(TEXTURE_DIR)/ ($(shell ls $(TEXTURE_DIR) 2>/dev/null | wc -l) files)"
	@echo "  • Mandatory maps:  $(MAPS_DIR)/ ($(shell ls $(MAPS_DIR) 2>/dev/null | wc -l) files)"
	@echo "  • Bonus maps:      $(MAPS_BONUS_DIR)/ ($(shell ls $(MAPS_BONUS_DIR) 2>/dev/null | wc -l) files)"
	@echo ""
	@echo "$(YELLOW)Libraries:$(NC)"
	@if [ -f "$(LIBFT_A)" ]; then \
		echo "  • $(GREEN)libft.a$(NC) - $(shell stat -c %y $(LIBFT_A) 2>/dev/null || echo "unknown")"; \
	else \
		echo "  • $(RED)libft.a$(NC) - Not built"; \
	fi
	@if [ -f "$(MLX_A)" ]; then \
		echo "  • $(GREEN)libmlx.a$(NC) - $(shell stat -c %y $(MLX_A) 2>/dev/null || echo "unknown")"; \
	elif [ -f "$(MLX_SO)" ]; then \
		echo "  • $(GREEN)libmlx.so$(NC) - $(shell stat -c %y $(MLX_SO) 2>/dev/null || echo "unknown")"; \
	else \
		echo "  • $(RED)MiniLibX$(NC) - Not built"; \
	fi
	@echo ""
	@echo "$(YELLOW)Available targets:$(NC)"
	@echo "  • $(GREEN)make$(NC) or $(GREEN)make mandatory$(NC)    - Build mandatory version"
	@echo "  • $(GREEN)make bonus$(NC)                - Build bonus version"
	@echo "  • $(GREEN)make easy/medium/hard$(NC)     - Build bonus with difficulty"
	@echo "  • $(GREEN)make status$(NC)               - Check build status"
	@echo "  • $(GREEN)make clean$(NC)                - Remove object files"
	@echo "  • $(GREEN)make fclean$(NC)               - Full clean"
	@echo "  • $(GREEN)make re$(NC)                   - Rebuild all"
	@echo "  • $(GREEN)make info$(NC)                 - Show this info"
	@echo "$(CYAN)═══════════════════════════════════════════════$(NC)"

.PHONY: all mandatory bonus easy medium hard libft mlx clean fclean re status info
