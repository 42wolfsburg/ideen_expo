# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/09 12:22:11 by gkamanur          #+#    #+#              #
#    Updated: 2024/11/20 15:48:12 by gkamanur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the library
NAME = libft.a

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directories for source files and includes
SRCDIR = srcs
INCDIR = includes

# Source files and corresponding object files
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(SRCDIR)/%.o)

# Default rule to create the library
all: $(NAME)

# Rule to create the library from object files
$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
	@echo "Library $(NAME) created."

# Rule to compile each .c file to .o file
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@

# Rule to clean object files
clean:
	rm -f $(OBJ)
	@echo "Object files removed."

# Rule to clean object files and the library
fclean: clean
	rm -f $(NAME)
	@echo "Library $(NAME) removed."

# Rule to recompile everything
re: fclean all

# Rule to run the code 
run: $(NAME)
	$(CC) -I $(INCDIR) *.c -L. -lft -o a.out && ./a.out