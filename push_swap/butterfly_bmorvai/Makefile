NAME = push_swap

SRCS = libft/ft_split.c libft/ft_calloc.c libft/ft_atoi.c \
	   libft/ft_isdigit.c libft/ft_bzero.c \
	   sort_small/sort_2.c sort_small/sort_3.c sort_small/sort_4.c \
	   sort_small/sort_5.c \
	   src/sort.c src/is_sorted.c\
       src/push.c src/reverse.c src/swap.c \
	   src/checks.c src/init_stacks.c \
       utils/stack_utils2.c \
	   utils/sort_utils.c utils/stack_utils.c \
	   main.c
       
	   
	
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re