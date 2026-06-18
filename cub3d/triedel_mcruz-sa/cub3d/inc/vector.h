/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:59:36 by triedel           #+#    #+#             */
/*   Updated: 2024/08/12 17:00:56 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// \file
#ifndef VECTOR_H
# define VECTOR_H

# include <stdbool.h>

/// 2D vector
typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

/// 3D vector
typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

/// 2D vector
typedef t_vec2			t_vec;
/// 2D point (equivalent to vector)
typedef t_vec2			t_pt;

typedef t_vec2			t_pt2;
typedef t_vec3			t_pt3;

typedef unsigned int	t_color;

/// 2D line, starting at location `loc` with direction vector `dir`
typedef struct s_line
{
	t_pt	loc;
	t_vec	dir;
}	t_line;

/// 2D integer point
typedef struct s_ipt
{
	int		x;
	int		y;
}	t_ipt;

/// colored point, combines t_color and t_ipt
typedef struct s_cpt
{
	t_color	col;
	t_ipt	pt;
}	t_cpt;

typedef struct s_rect
{
	// top left
	t_ipt	tl;
	// bottom right
	t_ipt	br;
}	t_rect;

/// direction constant for north
# define DNORTH	0
/// direction constant for south
# define DSOUTH	1
/// direction constant for west
# define DWEST	2
/// direction constant for east
# define DEAST	3

// ===== 2D vector =====
/// create vector - convenience function
t_vec	vec(float x, float y);
/// create vector from first 2 entries of a 3D vector
t_vec	vec_from_vec3(t_vec3 *v);
/// sum together vectors `a` and `b`
t_vec	vec_add(t_vec a, t_vec b);
/// subtract vector `b` from vector`a`
t_vec	vec_sub(t_vec a, t_vec b);
/// scale vector `a` by scalar `f`
t_vec	vec_scale(t_vec a, float f);
/// rotate vector `v` by `r` radians
t_vec	vec_rotate(t_vec v, float r);
/// magnitude of vector
float	vec_len(t_vec v);
/// normalize vector, such that its magnitude is 1
t_vec	vec_normalize(t_vec v);
/// calculate direction relative to north
int		vec_direction(t_vec *v);
/// whether either coordinate is non-zero
bool	vec_nonzero(t_vec *v);
/// dot product
float	vec_mul(t_vec v, t_vec w);

// ===== 3D vector =====
/// create 3D vector - convenience function
t_vec3	vec3(float x, float y, float z);
/// create 3D vector, using x and y from 2D vector `v`
t_vec3	vec3_from_vec(t_vec	*v);

// ===== ipt / integer point =====
/// create integer point - convenience function
t_ipt	ipt(int x, int y);
// ===== cpt / colored integer point =====
t_cpt	cpt(t_color c, int x, int y);

// ===== rect =====
t_rect	rect(int x1, int y1, int x2, int y2);

#endif
