/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmichale <pmichale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:44:08 by pmichale          #+#    #+#             */
/*   Updated: 2024/01/30 18:34:28 by pmichale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_ls
{
	char			*retline;
	char			*line;
	int				done;
	int				offset;
}					t_ls;

char	*get_next_line(int fd);
char	*sub_retlineextend(char *retline);
char	*sub_newlinesep(char *line, t_ls *ls);
char	*sub_buildstatic(char *line1, t_ls *ls);
void	*sub_calloc(size_t count, size_t size);
void	sub_staticinline(char *stline, t_ls *ls, int *i, int *j);
char	*sub_handlestatic(int fd, char *stline, t_ls *ls);
void	sub_retlinebuild(t_ls *ls, int *i, int *j);
char	*sub_mainloop(int fd, char *stline, t_ls *ls, int i);
char	*sub_itssoover(t_ls *ls, char *stline, int *i, int *j);
#endif
