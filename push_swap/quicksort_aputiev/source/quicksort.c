/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:29:02 by aputiev           #+#    #+#             */
/*   Updated: 2023/03/10 20:24:39 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../printf/ft_printf.h"
#include <stdlib.h>

// -------------------------------------------------------------------
// sort three or less numbers in stack a and b;

void	quicksort_three_stack_a_and_b(t_stacks *stack, int len)
{
	if (len == 3 && stack->size_a == 3)
		three_numbers_case_stack_a(stack);
	else if (len == 2)
	{
		if (stack->a[0] > stack->a[1])
			swap_a(stack, 0);
	}
	else if (len == 3)
	{
		while (len != 3 || !(stack->a[0] < stack->a[1]
				&& stack->a[1] < stack->a[2]))
		{
			if (len == 3 && stack->a[0] > stack->a[1] && stack->a[2])
				swap_a(stack, 0);
			else if (len == 3 && !(stack->a[2] > stack->a[0]
					&& stack->a[2] > stack->a[1]))
				len = ft_push(stack, len, 0);
			else if (stack->a[0] > stack->a[1])
				swap_a(stack, 0);
			else if (len++)
				push_a(stack, 0);
		}
	}
}

// -------------------------------------------------------------------
// sort three or less numbers in stack b;
int	sort_three_b(t_stacks *stack, int len)
{
	if (len == 1)
		push_a(stack, 0);
	else if (len == 2)
	{
		if (stack->b[0] < stack->b[1])
			swap_b(stack, 0);
		while (len--)
			push_a(stack, 0);
	}
	else if (len == 3)
	{
		while (len || !(stack->a[0] < stack->a[1] && stack->a[1] < stack->a[2]))
		{
			if (len == 1 && stack->a[0] > stack->a[1])
				swap_a(stack, 0);
			else if (len == 1 || (len >= 2 && stack->b[0] > stack->b[1])
				|| (len == 3 && stack->b[0] > stack->b[2]))
				len = ft_push(stack, len, 1);
			else
				swap_b(stack, 0);
		}
	}
	return (0);
}

// -----------------------------------------------------------------
//set up *pivot on median of stack a: 7 1 6 5 2 4 3
//sorts numbers in temporaire_stack using "simple swap" method 1 2 3 4 5 6 7
//return value of pointer pivot  - the median number: 1 2 3 '4' 5 6 7

int	axis_of_numbers(int *pivot, int *stack, int size)
{
	int		*temporaire_stack;
	int		i;

	temporaire_stack = (int *)malloc(size * sizeof(int));
	if (!temporaire_stack)
		return (0);
	i = 0;
	while (i < size)
	{
		temporaire_stack[i] = stack[i];
		i++;
	}
	temporary_sort(temporaire_stack, size);
	*pivot = temporaire_stack[size / 2];
	free(temporaire_stack);
	return (1);
}

// --------------------------------------------------------------------
//this is a quicksort-algorithm for stack a; 
//checks if stack a already sorted;
//run sorting algorithm "quicksort_three_stack_a_and_b" for len <=3 or
//run quicksort-algorithm for len >3;

int	quicksort_stack_a(t_stacks *stack, int len, int count_r)
{
	int	pivot;
	int	numbers;

	if (check_sorted(stack->a, len, 0) == 1)
		return (1);
	numbers = len;
	if (len <= 3)
	{
		quicksort_three_stack_a_and_b(stack, len);
		return (1);
	}
	if (!axis_of_numbers(&pivot, stack->a, len))
		return (0);
	while (len != numbers / 2 + numbers % 2)
	{
		if (stack->a[0] < pivot && (len--))
			push_b(stack, 0);
		else if (++count_r)
			rotate_a(stack, 0);
	}
	while (numbers / 2 + numbers % 2 != stack->size_a && count_r--)
		reverse_rotate_a(stack, 0);
	return (quicksort_stack_a(stack, numbers / 2 + numbers % 2, 0)
		&& quicksort_stack_b(stack, numbers / 2, 0));
	return (1);
}

// -------------------------------------------------------------------
// this is a quicksort-algorithm for stack b; 
// checks if stack a already sorted;
// run sorting algorithm "sort_three_b" for len <=3 or
// run quicksort-algorithm for len >3;
int	quicksort_stack_b(t_stacks *stack, int len, int count_r)
{
	int	pivot;
	int	numbers;

	if (check_sorted(stack->b, len, 1) == 1)
		while (len--)
			push_a(stack, 0);
	if (len <= 3)
	{
		sort_three_b(stack, len);
		return (1);
	}
	numbers = len;
	if (!axis_of_numbers(&pivot, stack->b, len))
		return (0);
	while (len != numbers / 2)
	{
		if (stack->b[0] >= pivot && len--)
			push_a(stack, 0);
		else if (++count_r)
			rotate_b(stack, 0);
	}
	while (numbers / 2 != stack->size_b && count_r--)
		reverse_rotate_b(stack, 0);
	return (quicksort_stack_a(stack, numbers / 2 + numbers % 2, 0)
		&& quicksort_stack_b(stack, numbers / 2, 0));
}
