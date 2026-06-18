/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:14:43 by alappas           #+#    #+#             */
/*   Updated: 2023/09/27 03:11:33 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

long int	ft_toi(const char *str)

{
	int		i;
	int		minus;
	long	result;

	i = 0;
	result = 0;
	minus = 1;
	if (str[i] == '-')
	{
		minus = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] >= 48 && str[i] <= 57)
		{
			result *= 10;
			result += str[i] - 48;
			++i;
		}
		else
			return (0);
	}
	return (result * minus);
}

t_stack	*ft_listnew(int data)
{
	t_stack	*stack_a;

	stack_a = (t_stack *)malloc(sizeof(t_stack));
	if (!stack_a)
		return (NULL);
	stack_a->data = data;
	stack_a->next = NULL;
	return (stack_a);
}

void	ft_listadd_back(t_stack **lst, t_stack *next)
{
	if (!lst)
		return ;
	if (lst)
	{
		if (*lst)
		{
			ft_lilast(*lst)->next = next;
			return ;
		}
	}
	*lst = next;
}

t_stack	*ft_lilast(t_stack *lst)

{
	t_stack	*node;

	node = lst;
	if (node != NULL)
	{
		while (node->next != NULL)
			node = node->next;
	}
	return (node);
}

int	ft_strcmp(const char *s1, const char *s2)

{
	unsigned int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
