/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:25:47 by jastomme          #+#    #+#             */
/*   Updated: 2024/10/03 12:30:10 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (big == NULL && little == NULL)
		return (NULL);
	i = 0;
	if (little[i] == '\0')
		return ((char *) big);
	while (i < len && big[i] != '\0' )
	{
		j = 0;
		while (little[j] == big[i + j] && (i + j) < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

/*int main(void)
{
char big[] = "Hello, World!";
char little[] = "World";
char *result = ft_strnstr(big, little, strlen(big));
if (result)
    ft_printf("Found '%s' at index %ld\n", little, result - big);
else
    ft_printf("Not found\n");

}

#include <string.h>

char* my_strnstr(const char* haystack, const char* needle, size_t n) {
    size_t needle_len = strlen(needle);
    if (needle_len == 0) return (char*)haystack;
    
    size_t i = 0;
    while (i <= n - needle_len) {
        if (strncmp(haystack + i, needle, needle_len) == 0) {
            return (char*)(haystack + i);
        }
        i++;
    }
    
    return NULL;
}
if little empty return big
outer while iterates through big until len or 0
inner loop compares little to big starting at i && != >len
if end of little (j+1 == '\0')*/