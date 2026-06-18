/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmorvai <bmorvai@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:31:06 by bmorvai           #+#    #+#             */
/*   Updated: 2026/03/18 09:18:16 by bmorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_stack_node
{
	int					value;
	int					index;
	struct s_stack_node	*next;
}						t_stack_node;

// Stack Handling and Testing
void					init_stacks(int argc, char **argv, t_stack_node **a);
void					add(int value, t_stack_node **a);
void					print_stack(t_stack_node *stack);
void					print_index(t_stack_node *stack);
int						stack_size(t_stack_node **stack);
void					free_stack(t_stack_node **stack);
void					free_args(char **args);

// Libft Utilities
int						ft_atoi(const char *nptr);
int						ft_isdigit(int d);
char					**ft_split(char const *s, char c);
char					*ft_wordcopy(char *start, char *end);
void					*ft_calloc(size_t nmemb, size_t size);
void					*ft_bzero(void *s, size_t n);

// Error checks
void					check_duplicates(t_stack_node **stack, char **args, int argc);
void					check_overflow(long number, t_stack_node **a, char **args, int argc);
void					check_numeric(char *argument, t_stack_node **a, char **args, int argc);

// Algorhythm - Indexing - Searching;
int						find_min(t_stack_node **stack);
int						find_min_i(t_stack_node **a);
int						find_max(t_stack_node **b);
void					find_index(t_stack_node **stack);

// Algorhythm - Sorting
int						is_sorted(t_stack_node **a);
int						chunk_size(int ac);
void					sort(t_stack_node **a, t_stack_node **b, int argc);
void					go_home(t_stack_node **a, t_stack_node **b);
int						distance(t_stack_node **b,
							int (*f)(t_stack_node **stack));

// Algorhythm - Sorting Low Argc Count
void					sort_two(t_stack_node **a);
void					sort_three(t_stack_node **a, t_stack_node **b);
void					sort_three_low(t_stack_node **a, t_stack_node **b,
							int second, int third);
void					sort_three_mid(t_stack_node **a,
							int first, int second);
void					sort_three_high(t_stack_node **a, t_stack_node **b,
							int first, int second);
void					sort_four(t_stack_node **a, t_stack_node **b);
void					sort_five(t_stack_node **a, t_stack_node **b);

// Operations
void					pa(t_stack_node **a, t_stack_node **b);
void					pb(t_stack_node **a, t_stack_node **b);
void					ra(t_stack_node **a);
void					rb(t_stack_node **b);
void					rr(t_stack_node **a, t_stack_node **b);
void					rra(t_stack_node **a);
void					rrb(t_stack_node **b);
void					rrr(t_stack_node **a, t_stack_node **b);
void					sa(t_stack_node **a);
void					sb(t_stack_node **b);
void					ss(t_stack_node **a, t_stack_node **b);