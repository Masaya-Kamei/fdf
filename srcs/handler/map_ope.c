/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_ope.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 12:44:03 by mkamei            #+#    #+#             */
/*   Updated: 2021/11/30 18:02:53 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_x(double *y, double *z, const double theta)
{
	const double	oldy = *y;
	const double	oldz = *z;

	*y = oldy * cos(theta) - oldz * sin(theta);
	*z = oldy * sin(theta) + oldz * cos(theta);
}

static void	rotate_y(double *x, double *z, const double phi)
{
	const double	oldx = *x;
	const double	oldz = *z;

	*x = oldx * cos(phi) + oldz * sin(phi);
	*z = -oldx * sin(phi) + oldz * cos(phi);
}

static void	rotate_z(double *x, double *y, const double psi)
{
	const double	oldx = *x;
	const double	oldy = *y;

	*x = oldx * cos(psi) - oldy * sin(psi);
	*y = oldx * sin(psi) + oldy * cos(psi);
}

void	rotate_3d_map(t_map *map, const t_axis_name name, const double angle)
{
	int					x;
	int					y;
	t_point_3d **const	matrix_3d = map->matrix_3d;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (name == X)
				rotate_x(&matrix_3d[y][x].y, &matrix_3d[y][x].z, angle);
			else if (name == Y)
				rotate_y(&matrix_3d[y][x].x, &matrix_3d[y][x].z, angle);
			else if (name == Z)
				rotate_z(&matrix_3d[y][x].x, &matrix_3d[y][x].y, angle);
		}
	}
}

void	zoom_3d_map(t_map *map, const double xy_zoom, const double z_zoom)
{
	int		x;
	int		y;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			map->matrix_3d[y][x].x *= xy_zoom;
			map->matrix_3d[y][x].y *= xy_zoom;
			map->matrix_3d[y][x].z *= z_zoom;
		}
	}
}
