SRCS		=	main.c parse_elements.c utils.c\
				utils2.c error_handle.c s_moves.c\
				r_moves.c rr_moves.c p_moves.c\
				small_moves.c main_sort.c small_moves_b.c\
				stack_values.c main_sort_utils.c

CC_FLAGS	=	-Wall -Wextra -Werror -g # -fsanitize=address -I
CC			=	gcc
SRCS_F		=	src/
OBJS_F		=	obj/

LIBFT		= inc/libft/
HEADER		= push_swap.h

OBJS		=	$(SRCS:.c=.o)
OBJS_P		=	$(addprefix $(OBJS_F), $(OBJS))
NAME		= 	push_swap

all:$(NAME)

$(OBJS_F)%.o: $(SRCS_F)%.c Makefile $(HEADER) | $(OBJS_F)
	@echo "Working on: $<"
	@$(CC) $(CC_FLAGS) -O3 -c $< -o $@ -I.

$(OBJS_F):
	@mkdir -p $(OBJS_F)

$(NAME): $(OBJS_P)
	@$(MAKE) -C $(LIBFT) 
	@$(CC) $(CC_FLAGS) -O3 -o $(NAME) $(OBJS_P) $(LIBFT)/libft.a 
	@echo "Push_swap compiled successfully!"

clean:
	@rm -rf $(OBJS_F)
	@$(MAKE) fclean -C $(LIBFT) 
	@echo "Push_swap objects removed!"

fclean:	clean
	@rm -rf $(NAME)
	@echo "Push_swap removed!"

re:		fclean all

.PHONY:	all clean fclean re