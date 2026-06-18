NAME		= so_long
LIBFT_DIR	= ./libft
MLX_DIR		= ../../common/minilibx-linux
MLX_LIB		= $(MLX_DIR)/libmlx.a

SRCS = src/main.c \
	   src/check_utils.c \
	   src/checking_it.c \
	   src/freeing_it.c \
	   src/initialise.c \
	   src/key_hooks.c \
	   src/moving_it.c \
	   src/terminal_it.c \
	   src/utils.c

CC			= cc
RM			= rm -f
CFLAGS		= -g -Wall -Werror -Wextra -I$(MLX_DIR)
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
LIBFT		= $(LIBFT_DIR)/libft.a
OBJS		= $(SRCS:.c=.o)
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(NAME)

valgrind: all
	valgrind $(VALGRIND_FLAGS) ./$(NAME) map/minimal.ber

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all run valgrind clean fclean re
