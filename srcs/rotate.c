/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:44:03 by mkamei            #+#    #+#             */
/*   Updated: 2021/09/22 17:41:04 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_x(float *y, float *z, float theta)
{
	float	oldy;
	float	oldz;

	oldy = *y;
	oldz = *z;
	*y = oldy * cos(theta) - oldz * sin(theta);
	*z = oldy * sin(theta) + oldz * cos(theta);
}

static void	rotate_y(float *x, float *z, float phi)
{
	float	oldx;
	float	oldz;

	oldx = *x;
	oldz = *z;
	*x = oldx * cos(phi) + oldz * sin(phi);
	*z = -oldx * sin(phi) + oldz * cos(phi);
}

static void	rotate_z(float *x, float *y, float psi)
{
	float	oldx;
	float	oldy;

	oldx = *x;
	oldy = *y;
	*x = oldx * cos(psi) - oldy * sin(psi);
	*y = oldx * sin(psi) + oldy * cos(psi);
}

void	rotate_map(t_map map, t_axis_name name, float angle)
{
	int		x;
	int		y;

	y = -1;
	while (++y < map.height)
	{
		x = -1;
		while (++x < map.width)
		{
			if (name == X)
				rotate_x(&map.matrix[y][x].y, &map.matrix[y][x].z, angle);
			else if (name == Y)
				rotate_y(&map.matrix[y][x].x, &map.matrix[y][x].z, angle);
			else if (name == Z)
				rotate_z(&map.matrix[y][x].x, &map.matrix[y][x].y, angle);
		}
	}
}
