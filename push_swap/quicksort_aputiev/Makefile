# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 13:30:12 by aputiev           #+#    #+#              #
#    Updated: 2023/03/10 21:00:39 by aputiev          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
BONUS_NAME = checker
LIBFT = libft.a
PRINTF = libftprintf.a

SRC_FILES =	push_swap.c sort.c Utils_functions.c \
			quicksort.c op_push.c op_rotate.c \
			op_swap.c  op_reverse_rotate.c
BONUS_FILES = checker.c
SRC_DIR = source/
BONUS_DIR = bonus/
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
BONUS = $(addprefix $(BONUS_DIR), $(BONUS_FILES))
OBJ = ${SRC:.c=.o}
OBJB = ${BONUS:.c=.o}
OBJBB = ${filter-out source/push_swap.o ,${OBJ}}
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
INCLUDE = -I include
RM = rm -rf

all:		$(NAME)

$(NAME) : $(OBJ)
		@make -C libft
		@cp libft/libft.a .
		@make -C printf
		@cp printf/libftprintf.a .
		$(CC) $(CFLAGS) $(OBJ) $(INCLUDE) $(LIBFT) $(PRINTF) -o $(NAME)

bonus : $(NAME) $(OBJB)
		$(CC) $(CFLAGS) $(OBJBB) $(OBJB) $(INCLUDE) $(LIBFT) $(PRINTF) -o $(BONUS_NAME)

clean :
		make clean -C libft
		make clean -C printf
		${RM} ${OBJ}
		${RM} ${OBJB}

fclean : clean
		@make fclean -C libft
		@make fclean -C printf
		${RM} $(NAME)
		${RM} $(BONUS_NAME)
		${RM} $(LIBFT)
		${RM} libft/$(PRINTF)
		${RM} $(PRINTF)
		${RM} printf/$(PRINTF)

re : fclean all

.PHONY:		all clean fclean re
