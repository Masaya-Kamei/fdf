/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:44:03 by mkamei            #+#    #+#             */
/*   Updated: 2021/09/23 11:58:51 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_x(double *y, double *z, double theta)
{
	double	oldy;
	double	oldz;

	oldy = *y;
	oldz = *z;
	*y = oldy * cos(theta) - oldz * sin(theta);
	*z = oldy * sin(theta) + oldz * cos(theta);
}

static void	rotate_y(double *x, double *z, double phi)
{
	double	oldx;
	double	oldz;

	oldx = *x;
	oldz = *z;
	*x = oldx * cos(phi) + oldz * sin(phi);
	*z = -oldx * sin(phi) + oldz * cos(phi);
}

static void	rotate_z(double *x, double *y, double psi)
{
	double	oldx;
	double	oldy;

	oldx = *x;
	oldy = *y;
	*x = oldx * cos(psi) - oldy * sin(psi);
	*y = oldx * sin(psi) + oldy * cos(psi);
}

void	rotate_map(t_map map, t_axis_name name, double angle)
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
