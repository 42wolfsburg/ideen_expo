NAME = fractol

CC = gcc

CFLAGS = -Werror -Wall -Wextra -fsanitize=address

RM = rm -rf

UNAME = $(shell uname -s)

SRCS = 	color.c\
		events.c\
		fractol.c\
		init.c\
		parse.c\
		render.c\
		utils.c\
		utils2.c\

ifeq ($(UNAME), Darwin)
	MLX_DIR = mlx
	MLX_LIB = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
	MLX_DIR = ../../common/minilibx-linux
	MLX_LIB = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm
	CFLAGS += -D LINUX
endif

INCLUDES = -I$(MLX_DIR)

$(NAME) : $(SRCS) $(MLX_DIR)/libmlx.a
	$(CC) $(SRCS) -o $(NAME) $(CFLAGS) $(INCLUDES) $(MLX_LIB)

$(MLX_DIR)/libmlx.a:
	$(MAKE) -C $(MLX_DIR)


all : $(NAME)

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(NAME)

re : fclean all
