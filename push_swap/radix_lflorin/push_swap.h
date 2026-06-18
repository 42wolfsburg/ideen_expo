/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorin <lflorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:24:33 by lflorin           #+#    #+#             */
/*   Updated: 2026/05/29 13:29:21 by lflorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_stack
{
	long int		value;
	int				index;
	struct s_stack	*next;
}	t_stack;

//swap
void	swap(t_stack **s);
void	sa(t_stack **stack_a);
void	sb(t_stack **stack_b);
void	ss(t_stack **stack_a, t_stack **stack_b);

// push
void	push(t_stack **stack_a, t_stack **stack_b);
void	pb(t_stack **stack_a, t_stack **stack_b);
void	pa(t_stack **stack_a, t_stack **stack_b);

// rotate
void	rotate(t_stack **r);
void	ra(t_stack **r);
void	rb(t_stack **r);
void	rr(t_stack **ra, t_stack **rb);

// reverse rotate
void	reverse_rotate(t_stack **rr);
void	rra(t_stack **r);
void	rrb(t_stack **r);
void	rrr(t_stack **rra, t_stack **rrb);

//helper
int		ft_putstr(const char *str);
int		ft_lstsize(t_stack *lst);
int		is_sorted(t_stack *stack_a);
int		dublicate_check(t_stack *stack_a, long int value);
size_t	ft_strlen(char *str);

//atoi
long	ft_atol(char *str);

//errorhandling
int		error(void);
int		is_valid_input(char *string);

//min_max
t_stack	*get_min(t_stack *stack_a);
t_stack	*get_max(t_stack *stack_a);

//push_swap
// static int	handle_tokens(char **tokens, t_stack **stack_a);
// static int	parse_arguments(int argc, char **argv, t_stack **stack_a);
// static void	init_stacks(t_stack **stack_a, t_stack **stack_b);
int		calling_function(t_stack **stack_a, t_stack **stack_b);
int		main(int argc, char **argv);

// lists
t_stack	*ft_newlist(int content);
t_stack	*ft_last(t_stack *stack_a);

// sort_2
void	sort_2(t_stack **stack_a);

//sort_3
void	sort_3(t_stack **stack_a);

//sort_5
void	sort_5(t_stack **stack_a, t_stack **stack_b);
void	sort_5_helper(t_stack **stack_a);

// radix_helper
int		find_index(int *sorted, int size, int value);
void	sort_int_array(int *array, int size);
void	assign_indexes(t_stack *stack_a);
int		get_max_amount_bits(t_stack *stack_a);

// radix
void	radix_sort(t_stack **stack_a, t_stack **stack_b);

// free
void	free_all(t_stack **stack);

// split
int		process_token(char *token, t_stack **stack_a);
void	free_split(char **split);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);

// ft_split_spaces
// static int	count_words(char *str);
// static int	next_word_start(char *str, int i);
// static int	next_word_end(char *str, int i);
// static char	**fill_split(char **result, char *str);
char	**ft_split_spaces(char *str);

#endif
