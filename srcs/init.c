/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 18:30:38 by mkamei            #+#    #+#             */
/*   Updated: 2021/10/28 15:51:20 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_window_data(t_data *d)
{
	d->win.width = 800;
	d->win.height = 800;
	d->mlx = mlx_init();
	d->win.win = mlx_new_window(d->mlx, d->win.width, d->win.height, "FDF");
	d->img.img = mlx_new_image(d->mlx, d->win.width, d->win.height);
	d->img.addr = mlx_get_data_addr(d->img.img,
			&d->img.bits_per_pixel, &d->img.line_length, &d->img.endian);
}

static void	init_camera_data(t_data *d)
{
	double	h;

	if (d->camera.pixel_per_len == 0)
	{
		h = hypot(d->map.width / 2, d->map.height / 2) + d->map.max_abs_z;
		d->camera.pixel_per_len
			= (fmin(d->win.width, d->win.height) / 2) / h;
	}
	d->camera.pixel_per_press = d->camera.pixel_per_len / 10;
	d->camera.angle_per_press = PI / 24.0;
}

static void	init_map_data(t_map *map)
{
	const int	size = map->width * map->height;
	int			x;
	int			y;
	int			i;

	map->sorted_p_3d_ptrs = (t_point_3d **)malloc(sizeof(t_point_3d *) * size);
	if (map->sorted_p_3d_ptrs == NULL)
		exit_with_errout(NULL, NULL, NULL);
	i = 0;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
			map->sorted_p_3d_ptrs[i++] = &map->matrix_3d[y][x];
	}
	map->msort_tmp = (t_point_3d **)malloc(sizeof(t_point_3d *) * size);
	if (map->msort_tmp == NULL)
		exit_with_errout(NULL, NULL, NULL);
	map->matrix_2d = (t_point_2d **)create_matrix(
			map->width, map->height, sizeof(t_point_2d));
	if (map->matrix_2d == NULL)
		exit_with_errout(NULL, NULL, NULL);
}

static void	init_projection(t_data *d)
{
	d->basis.ex.x = 1;
	d->basis.ex.y = 0;
	d->basis.ey.x = 0;
	d->basis.ey.y = 0;
	d->basis.ez.x = 0;
	d->basis.ez.y = -1;
	rotate_3d_map(d->map, Z, -PI / 4);
	rotate_3d_map(d->map, X, asin(tan(-PI / 6)));
}

void	init_fdf_data(t_data *d)
{
	init_window_data(d);
	init_camera_data(d);
	init_map_data(&d->map);
	init_projection(d);
}
