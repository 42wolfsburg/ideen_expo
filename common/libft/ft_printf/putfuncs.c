/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putfuncs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:46:28 by triedel           #+#    #+#             */
/*   Updated: 2023/12/08 20:46:55 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "putfuncs.h"

void	putstr(char c, void *s)
{
	*((*(char **) s)++) = c;
}

void	putstdout(char c, void *_)
{
	(void) _;
	write(STDOUT_FILENO, &c, 1);
}

void	putdummy(char c, void *_)
{
	(void) _;
	(void) c;
}
