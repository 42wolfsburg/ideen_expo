# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/02 21:59:51 by yyakuben          #+#    #+#              #
#    Updated: 2024/04/28 21:55:40 by yyakuben         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

SRC_DIR		=		src
SRCS		=		$(SRC_DIR)/main.c \
								$(SRC_DIR)/srrrp.c \
								$(SRC_DIR)/utilities.c \
								$(SRC_DIR)/list.c \
								$(SRC_DIR)/swappush.c \
								$(SRC_DIR)/rotate.c \
								$(SRC_DIR)/reverserotate.c \
								$(SRC_DIR)/utilities1.c \
								$(SRC_DIR)/simplesort.c \
								$(SRC_DIR)/f_sort.c \
								$(SRC_DIR)/big_sort.c \



OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -rf

all: ${NAME}

${NAME}: ${OBJS}
		@${MAKE} -C inc/libft
		@${MAKE} -C inc/ft_printf
		@${CC} ${CFLAGS} ${OBJS} inc/libft/libft.a inc/ft_printf/libftprintf.a -o ${NAME}
		
clean:
		@${MAKE} -C inc/libft fclean
		@${MAKE} -C inc/ft_printf fclean
		@${RM} ${OBJS}

fclean: clean
		@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re