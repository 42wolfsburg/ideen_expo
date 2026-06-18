/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:30:43 by aputiev           #+#    #+#             */
/*   Updated: 2023/03/11 11:10:36 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
/*
	int	*a - pointer to stack a
	int	*b - pointer to stack b
	int	size_a - quantity of numbers in stack a;
	int	size_b - quantity of numbers in stack b;
*/

typedef struct s_stacks
{
	int	*a;
	int	*b;
	int	size_a;
	int	size_b;
}	t_stacks;

void	push_swap(char **av);
int		push_swap_strlen(char **av);
void	error_detected(int *stack);
int		push_swap_atoi(char *str, int *stack);
void	check_doubles(int *stack, int size);
//Instructions
void	swap_a(t_stacks *stack, int bonus);
void	swap_b(t_stacks *stack, int bonus);
void	swap_s(t_stacks *stack, int bonus);
void	rotate_a(t_stacks *stack, int bonus);
void	rotate_b(t_stacks *stack, int bonus);
void	rotate_r(t_stacks *stack, int bonus);
void	reverse_rotate_a(t_stacks *stack, int bonus);
void	reverse_rotate_b(t_stacks *stack, int bonus);
void	reverse_rotate_r(t_stacks *stack, int bonus);
void	push_b(t_stacks *stack, int bonus);
void	push_a(t_stacks *stack, int bonus);
//Sort
int		sort(t_stacks *stack, int size);
int		check_sorted(int *stack, int size, int order);
void	three_numbers_case_stack_a(t_stacks *three);
void	temporary_sort(int *stack_temporaire, int size);
//Quicksort
int		quicksort_stack_a(t_stacks *stack, int len, int count_r);
int		quicksort_stack_b(t_stacks *stack, int len, int count_r);
void	quicksort_three_stack_a_and_b(t_stacks *stack, int len);
int		sort_three_b(t_stacks *stack, int len);
int		ft_push(t_stacks *stack, int len, int pb);
int		axis_of_numbers(int *pivot, int *stack, int size);
//Bonus
void	scan_from_stdin(t_stacks *stack);
int		*c_errors(char **av);
void	exec_instruction(t_stacks *stack, char *instruction);
void	free_error(t_stacks *stack, int choix);
#endif
