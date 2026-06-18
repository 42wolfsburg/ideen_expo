/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmorvai <bmorvai@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:33:29 by bmorvai           #+#    #+#             */
/*   Updated: 2026/03/12 18:08:05 by bmorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	add(int value, t_stack_node **a)
{
	t_stack_node	*new_node;
	t_stack_node	*current;

	new_node = malloc(sizeof(t_stack_node));
	new_node->value = value;
	new_node->next = NULL;
	new_node->index = -1;
	if (!*a)
	{
		*a = new_node;
		return ;
	}
	current = *a;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	print_stack(t_stack_node *stack)
{
	t_stack_node	*print_ptr;

	print_ptr = stack;
	while (print_ptr != NULL)
	{
		printf("%d\n", print_ptr->value);
		print_ptr = print_ptr->next;
	}
}

int	stack_size(t_stack_node **stack)
{
	int				size;
	t_stack_node	*temp;

	size = 0;
	temp = *stack;
	while (temp)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}

void	free_stack(t_stack_node **stack)
{
	t_stack_node	*current;
	t_stack_node	*next;

	current = *stack;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*stack = NULL;
}
