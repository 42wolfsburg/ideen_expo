/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:33:43 by alappas           #+#    #+#             */
/*   Updated: 2024/04/14 01:11:45 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "inc/libft/libft.h"
# include <limits.h>

typedef struct s_stack
{
	int				data;
	int				index;
	int				position;
	int				initial_cost;
	int				final_cost;
	int				target_pos;
	char			sign;
	struct s_stack	*next;
}	t_stack;

long	ft_toi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_listadd_back(t_stack **lst, t_stack *next);
t_stack	*ft_listnew(int data);
t_stack	*ft_lilast(t_stack *lst);
t_stack	*ft_prelilast(t_stack *lst);
t_stack	*parse_elements(char **argv);
int		error_handle(char **argv);
int		zero_handle(char **argv);
int		dup_handle(char **argv);
int		symbol_handle(char **argv);
int		limit_handle(char **argv);
void	sa_sb(t_stack **stack);
void	sa(t_stack **stack_a);
void	sb(t_stack **stack_b);
void	ss(t_stack **stack_a, t_stack **stack_b);
void	ra_rb(t_stack **stack);
void	ra(t_stack **stack_a);
void	rb(t_stack **stack_b);
void	rr(t_stack **stack_a, t_stack **stack_b);
void	rra_rrb(t_stack **stack);
void	rra(t_stack **stack_a);
void	rrb(t_stack **stack_b);
void	rrr(t_stack **stack_a, t_stack **stack_b);
void	pa_pb(t_stack **stack_dest, t_stack **stack_source);
void	pa(t_stack **stack_a, t_stack **stack_b);
void	pb(t_stack **stack_a, t_stack **stack_b);
void	all_moves(int argc, t_stack **stack_a, t_stack **stack_b);
void	small_moves(int argc, t_stack **stack_a);
void	small_moves_b(int argc, t_stack **stack_a, t_stack **stack_b);
void	three_digits(t_stack **stack_a);
void	two_digits(t_stack **stack_a);
void	two_digits_b(t_stack **stack_b);
void	four_digits(t_stack **stack_a, t_stack **stack_b);
void	five_digits(t_stack **stack_a, t_stack **stack_b);
void	ft_listclear(t_stack **stack);
void	stack_index(t_stack **stack, int argc);
void	stack_position(t_stack **stack);
void	stack_sign(t_stack **stack);
int		node_max(t_stack **stack);
int		node_min(t_stack **stack);
void	index_helper(t_stack **temp, t_stack **stack, int value);
void	index_reset(t_stack **stack);
void	index_parse(t_stack **stack);
int		main_sort(t_stack **stack_a, t_stack **stack_b);
int		sort_check_a(t_stack *stack_a);
int		sort_a(t_stack **stack_a, t_stack **stack_b);
void	semi_sort(t_stack **stack_a, t_stack **stack_b);
void	sign_reset(t_stack **stack);
void	stack_cost_a(t_stack **stack_a);
void	stack_cost_b(t_stack **stack_b);
void	stack_cost_b_helper(t_stack **stack_b, int *final_plus);
void	stack_final_cost(t_stack **stack_a, t_stack **stack_b);
void	stack_final_cost_helper(t_stack **stack_a, t_stack **stack_b,
			t_stack **target_node, t_stack *head_a);
void	inside_push_helper(t_stack **stack_a, t_stack **stack_b,
			t_stack *target_node, t_stack *inner_node);
void	final_sort(t_stack **stack_a, t_stack **stack_b);
void	inside_push(t_stack **stack_a, t_stack **stack_b, t_stack *target_node);
void	double_rotate(t_stack *inner_node, t_stack *target_node,
			t_stack **stack_a, t_stack **stack_b);

#endif