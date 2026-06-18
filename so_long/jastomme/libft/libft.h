/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:56:36 by jastomme          #+#    #+#             */
/*   Updated: 2024/12/05 14:20:16 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H		//ifnotdefined HEADER_FILE (ie Once Only Header File)
# define LIBFT_H	// note the <space> before define

# include <unistd.h>	// note the <space> before include
# include <stdlib.h>
# include <stddef.h>
# include <stdarg.h>	//va_list included with ft_printf add
# include "get_next_line.h"

int		ft_atoi(const char *str);
void	ft_bzero(void *str, size_t len);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
char	*ft_itoa(int n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t len);
void	*ft_memmove(void *dest, const void *src, size_t len);
void	*ft_memset(void *str, int c, size_t len);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	**ft_split(const char *s, char c);
size_t	count_words(const char *s, char c);
size_t	word_len(const char *s, char c);
void	free_array(size_t i, char **array);
char	**fill_arr(const char *s, char c, char **array, size_t count_words);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
//ft_printf added:
int		ft_printf(const char *format, ...);
int		ft_print_c(char c);
int		ft_print_d_upper(long n, int base);
int		ft_print_d(long n, int base);
int		ft_print_p(void *ptr);
int		ft_print_ptr(unsigned long n, int base);
int		ft_print_s(char *str);
//get_next_line added:
char	*get_next_line(int fd);
char	*stash_filling(int fd, char *stash, char *buffer);
char	*extract_new_stash(char *stash);
char	*extract_line(char *stash, char *line);

#endif