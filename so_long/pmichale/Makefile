
INCLIB=../../common/minilibx-linux
MLX_LIB=$(INCLIB)/libmlx.a

CFLAGS= -Werror -Wextra -Wall -g -fsanitize=address -I$(INCLIB)

NAME= so_long

SRC =	main.c \
		so_cool.c \
		so_funky.c \
		so_anime.c \
		./get_next_line/get_next_line.c \
		./get_next_line/get_next_line_utils.c \
		./ft_printf/ft_printf.c \
		./ft_printf/ft_printfsub.c \
		./ft_printf/ft_printfextra.c \
		./ft_printf/ft_printfitoa.c \
		./ft_printf/ft_printflib.c

OBJ = $(SRC:%.c=%.o)

LFLAGS = -L$(INCLIB) -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJ) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LFLAGS)

$(MLX_LIB):
	$(MAKE) -C $(INCLIB)

clean:
	rm $(OBJ)

re: clean all

fclean:
	rm -f $(NAME) $(OBJ)
