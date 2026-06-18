/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:57:32 by aputiev           #+#    #+#             */
/*   Updated: 2023/03/11 11:48:29 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../printf/ft_printf.h"

// -------------------------------------------------------------------
// sorts temporary stack using simple "swap"-method with temporary "bin"

void	temporary_sort(int *stack_temporaire, int size)
{
	int	i;
	int	j;
	int	temporaire;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (stack_temporaire[i] > stack_temporaire[j])
			{
				temporaire = stack_temporaire[i];
				stack_temporaire[i] = stack_temporaire[j];
				stack_temporaire[j] = temporaire;
			}
			j++;
		}
		i++;
	}
}

// -------------------------------------------------------------------
// sorts 3 numbers depending on the position of the digits:
// 1st case: 213 -> sa -> 123
// 2nd case: 321 -> sa -> 231 rra -> 123
// 3rd case: 312 -> ra -> 123
// 4th case: 132 -> sa -> 312 -> ra -> 123
// 5th case: 231 -> rra -> 123

void	three_numbers_case_stack_a(t_stacks *three)
{
	if (three->a[0] > three->a[1] && three->a[0] < three->a[2]
		&& three->a[1] < three->a[2])
		swap_a(three, 0);
	if (three->a[0] > three->a[1] && three->a[0] > three->a[2]
		&& three->a[1] > three->a[2])
	{
		swap_a(three, 0);
		reverse_rotate_a(three, 0);
	}
	if (three->a[0] > three->a[1] && three->a[0] > three->a[2]
		&& three->a[1] < three->a[2])
		rotate_a(three, 0);
	if (three->a[0] < three->a[1] && three->a[0] < three->a[2]
		&& three->a[1] > three->a[2])
	{
		swap_a(three, 0);
		rotate_a(three, 0);
	}
	if (three->a[0] < three->a[1] && three->a[0] > three->a[2]
		&& three->a[1] > three->a[2])
		reverse_rotate_a(three, 0);
}
	// -------------------------------------------------------------------------
	// initial process function;
	// Here we decide which sorting algorithm to use
	// (depends on quantity of numbers to sort: 2,3 or more):
	// check_sorted(stack->a, stack->size_a, 0)	-checks if numbers not-sorted

int	sort(t_stacks *stack, int size)
{
	if (check_sorted(stack->a, stack->size_a, 0) == 0)
	{
		if (size == 2)
			swap_a(stack, 0);
		else if (size == 3)
			three_numbers_case_stack_a(stack);
		else
			quicksort_stack_a(stack, size, 0);
	}
	return (0);
}
