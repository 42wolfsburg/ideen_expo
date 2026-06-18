SRC = \
	arg.c			\
	ft_printf.c		\
	put_int.c		\
	put_misc.c		\
	put_ptr.c		\
	putarg.c		\
	putfuncs.c	
OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wno-unused-value -Wall -Wextra -Werror -std=c99 -I..
ARFLAGS = rcs
RM = rm -rf

all: $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all bonus clean fclean re

# test:
# 	cc -c *.c
# 	c++ -std=c++14 $(shell pkg-config --cflags gtest) test.cc *.o $(shell pkg-config --libs gtest) libft/libft.a
