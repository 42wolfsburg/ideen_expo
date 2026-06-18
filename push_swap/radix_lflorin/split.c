/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 19:43:50 by lea               #+#    #+#             */
/*   Updated: 2026/05/28 14:11:15 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	process_token(char *token, t_stack **stack_a)
{
	long	value;
	t_stack	*new;
	t_stack	*last;

	if (!is_valid_input(token))
		return (error());
	value = ft_atol(token);
	if (value < -2147483648 || value > 2147483647)
		return (error());
	if (dublicate_check(*stack_a, value))
		return (error());
	new = ft_newlist((int)value);
	if (!new)
		return (1);
	if (!*stack_a)
		*stack_a = new;
	else
	{
		last = ft_last(*stack_a);
		last->next = new;
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen((char *)s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	i;

	dup = malloc(sizeof(char) * (ft_strlen((char *)s1) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
