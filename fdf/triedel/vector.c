/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:53:08 by triedel           #+#    #+#             */
/*   Updated: 2024/01/18 10:33:03 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

t_vec	vec(float x, float y, float z)
{
	return ((t_vec){.x = x, .y = y, .z = z});
}

t_vec4	vec_from_vec4(t_vec v)
{
	return ((t_vec4){.x = v.x, .y = v.y, .z = v.z, .w = 1});
}

t_vec	vec_normalize(t_vec4 v)
{
	return ((t_vec){
		.x = v.x / v.w,
		.y = v.y / v.w,
		.z = v.z / v.w
	});
}

t_vec	vec_from_cvec(t_cvec v)
{
	return (vec(v.x, v.y, v.z));
}

t_edge	edge(int a, int b)
{
	return ((t_edge){.a = a, .b = b});
}

// void	vec_print(t_vec v)
// {
// 	printf("v:  % 3.1f % 3.1f % 3.1f\n", v.x, v.y, v.z);
// }

// void	cvec_print(t_cvec v)
// {
// 	printf("cv: % 3.1f % 3.1f % 3.1f\n", v.x, v.y, v.z);
// }

// void	vec4_print(t_vec4 v)
// {
// 	printf("v4: % 3.1f % 3.1f % 3.1f % 3.1f\n", v.x, v.y, v.z, v.w);
// }

// int	main()
// {
// 	t_vec4 v = vec_from_vec4((t_vec){1, 2, 3});
// 	printf("%f %f %f %f\n", v.x, v.y, v.z, v.w);
// }
