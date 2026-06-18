/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:04:45 by jastomme          #+#    #+#             */
/*   Updated: 2024/12/05 14:22:45 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H	//ifnotdefined HEADER_FILE (ie Once Only Header File)
# define GET_NEXT_LINE_H	// note the <space> before define
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 48
# endif
# include <stdlib.h>	//malloc, free & size_t
# include <unistd.h>	// write
# include <stdio.h>		// NULL
# include <fcntl.h>		// RD_ONLY(main)

char	*get_next_line(int fd);
char	*stash_filling(int fd, char *stash, char *buffer);
char	*extract_new_stash(char *stash);
char	*extract_line(char *stash, char *line);

#endif