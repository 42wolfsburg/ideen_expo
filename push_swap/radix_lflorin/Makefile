# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lflorin <lflorin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/29 10:50:43 by lflorin           #+#    #+#              #
#    Updated: 2026/05/29 11:12:13 by lflorin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f
MAKEFLAGS += --silent
SRC =	push_swap.c \
		atoi.c \
		errorhandling.c \
		free.c \
		ft_split_spaces_too_long.c \
		helper.c \
		lists.c \
		min_max.c \
		push.c \
		swap.c \
		rotate.c \
		reverse_rotate.c \
		radix.c \
		radix_helper.c \
		sort_2.c \
		sort_3.c \
		sort_5.c \
		split.c \


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re