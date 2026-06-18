/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:42:33 by alappas           #+#    #+#             */
/*   Updated: 2023/09/27 01:51:45 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

t_stack	*parse_elements(char **argv)

{
	t_stack	*stack_a;
	int		i;

	i = 1;
	while (argv[i])
	{
		if (i == 1)
			stack_a = ft_listnew(ft_toi(argv[i]));
		else
			ft_listadd_back(&stack_a, ft_listnew(ft_toi(argv[i])));
		i++;
	}
	return (stack_a);
}
