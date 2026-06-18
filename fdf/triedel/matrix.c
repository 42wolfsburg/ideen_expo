/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:54:34 by triedel           #+#    #+#             */
/*   Updated: 2024/01/17 19:35:11 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "display.h"

t_vec4	vecmul(t_mat4 mat, t_vec4 v)
{
	t_vec4	res;

	res.x = mat[0][0] * v.x + \
			mat[0][1] * v.y + \
			mat[0][2] * v.z + \
			mat[0][3] * v.w;
	res.y = mat[1][0] * v.x + \
			mat[1][1] * v.y + \
			mat[1][2] * v.z + \
			mat[1][3] * v.w;
	res.z = mat[2][0] * v.x + \
			mat[2][1] * v.y + \
			mat[2][2] * v.z + \
			mat[2][3] * v.w;
	res.w = mat[3][0] * v.x + \
			mat[3][1] * v.y + \
			mat[3][2] * v.z + \
			mat[3][3] * v.w;
	return (res);
}

void	mat4_copy(t_mat4 to, t_mat4 from)
{
	int	m;
	int	n;

	m = 0;
	while (m < 4)
	{
		n = 0;
		while (n < 4)
		{
			to[m][n] = from[m][n];
			n++;
		}
		m++;
	}
}

void	matmul(t_mat4 mat1, t_mat4 mat2)
{
	int		m;
	int		n;
	int		i;
	t_mat4	tmp;

	m = 0;
	while (m < 4)
	{
		n = 0;
		while (n < 4)
		{
			tmp[m][n] = 0;
			i = 0;
			while (i < 4)
			{
				tmp[m][n] += mat1[m][i] * mat2[i][n];
				i++;
			}
			n++;
		}
		m++;
	}
	mat4_copy(mat1, tmp);
}

void	mat_identity(t_mat4 m)
{
	int	x;
	int	y;

	x = -1;
	while (++x < 4)
	{
		y = -1;
		while (++y < 4)
		{
			if (x == y)
				m[y][x] = 1;
			else
				m[y][x] = 0;
		}
	}
}

// extrinsic rotation
void	mat_rotation(t_mat4 m, float a, float b, float c)
{
	m[0][0] = cos(b) * cos(c);
	m[0][1] = sin(a) * sin(b) * cos(c) - cos(a) * sin(c);
	m[0][2] = cos(a) * sin(b) * cos(c) + sin(a) * sin(c);
	m[0][3] = 0;
	m[1][0] = cos(b) * sin(c);
	m[1][1] = sin(a) * sin(b) * sin(c) + cos(a) * cos(c);
	m[1][2] = cos(a) * sin(b) * sin(c) - sin(a) * cos(c);
	m[1][3] = 0;
	m[2][0] = -sin(b);
	m[2][1] = sin(a) * cos(b);
	m[2][2] = cos(a) * cos(b);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

// intrinsic rotation
// void	mat_rotation_int(t_mat4 m, float a, float b, float c)
// {
// 	m[0][0] = cos(a) * cos(b);
// 	m[0][1] = cos(a) * sin(b) * sin(c) - sin(a) * cos(c);
// 	m[0][2] = cos(a) * sin(b) * cos(c) + sin(a) * sin(c);
// 	m[0][3] = 0;
// 	m[1][0] = sin(a) * cos(b);
// 	m[1][1] = sin(a) * sin(b) * sin(c) + cos(a) * cos(c);
// 	m[1][2] = sin(a) * sin(b) * cos(c) - cos(a) * sin(c);
// 	m[1][3] = 0;
// 	m[2][0] = -sin(b);
// 	m[2][1] = cos(b) * sin(c);
// 	m[2][2] = cos(b) * cos(c);
// 	m[2][3] = 0;
// 	m[3][0] = 0;
// 	m[3][1] = 0;
// 	m[3][2] = 0;
// 	m[3][3] = 1;
// }

// void	mat4_print(t_mat4 mat)
// {
// 	printf("matrix:\n");
// 	for (int m=0; m<4; m++)
// 	{
// 		for (int n=0; n<4; n++)
// 			printf("% 5f ", mat[m][n]);
// 		printf("\n");
// 	}
// 	printf("\n");
// }