/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 20:01:17 by yyakuben          #+#    #+#             */
/*   Updated: 2024/04/29 01:36:43 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include "inc/libft/libft.h"
# include "inc/ft_printf/ft_printf.h"

typedef struct s_lists
{
	int				index;
	int				content;
	int				distance;
	struct s_lists	*next;
}					t_lists;

void	big_sort(t_lists **lst_a, t_lists **lst_b, int ac);
void	go_home(t_lists **lst_b);
int		best_moment(int ac);

int		distance(t_lists **lst, int (*f)(t_lists **lst));
void	move_distance(t_lists **lst_a);
void	find_index(t_lists **lst);

long	ft_atoi_num(const char *str);
int		is_sorted(t_lists **lst);
int		ft_lst_size(t_lists **lst);
int		find_min(t_lists **lst);
int		find_max(t_lists **lst);

void	ft_lstadd_back(t_lists **lst, t_lists *new);
t_lists	*ft_lstnew(int content);
t_lists	*ft_lstlast(t_lists *lst);
void	lst_add_front(t_lists **lst, t_lists *new);
void	ft_listclear(t_lists **lst);

int		lst_swap(t_lists **lst);
int		lst_rotate(t_lists **lst);
int		lst_reverse_rotate(t_lists **lst);
int		push(t_lists **lst_a, t_lists **lst_b);

void	rra(t_lists **lst);
void	rrb(t_lists **lst);
void	rrr(t_lists **lst_a, t_lists **lst_b);

void	ra(t_lists **lst);
void	rb(t_lists **lst);
void	rr(t_lists **lst_a, t_lists **lst_b);

void	sa(t_lists **lst);
void	sb(t_lists **lst);
void	ss(t_lists **lst_a, t_lists **lst_b);
void	pa(t_lists **lst_a, t_lists **lst_b);
void	pb(t_lists **lst_a, t_lists **lst_b);

void	print_error(void);
int		check_duplicate(t_lists *stack_a, int num);
int		check_max_min(long num);
int		ft_str_is_num(char *str);
t_lists	*init_stack_a(int ac, char **av);

void	sort2(t_lists **lst);
void	sort3(t_lists **lst);
void	sort4(t_lists **lst_a, t_lists **lst_b);
void	sort5(t_lists **lst_a, t_lists **lst_b);

#endif