/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:03:27 by mkamei            #+#    #+#             */
/*   Updated: 2021/09/23 19:48:07 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_z_abs_max(t_map map)
{
	int		max;
	int		x;
	int		y;
	int		z;

	max = 0;
	y = -1;
	while (++y < map.height)
	{
		x = -1;
		while (++x < map.width)
		{
			z = fabs(map.matrix[y][x].z);
			if (max < z)
				max = ceil(z);
		}
	}
	return (max);
}

static void	init_fdf_data(t_data *d)
{
	double	max_height;

	d->basis.ex.x = 1;
	d->basis.ex.y = 0;
	d->basis.ey.x = 0;
	d->basis.ey.y = 0;
	d->basis.ez.x = 0;
	d->basis.ez.y = -1;
	d->win.width = 800;
	d->win.height = 800;
	d->camera.z_per_xy = 1.125;
	max_height = hypot(d->map.width / 2, d->map.height / 2)
		+ get_z_abs_max(d->map) * d->camera.z_per_xy;
	d->camera.pixel_per_len
		= (fmin(d->win.width, d->win.height) / 2) / (max_height + 2);
	d->camera.pixel_per_press = d->camera.pixel_per_len / 10;
	d->camera.angle_per_press = PI / 24.0;
	d->mlx = mlx_init();
	d->win.win = mlx_new_window(d->mlx, d->win.width, d->win.height, "FDF");
	d->img.img = mlx_new_image(d->mlx, d->win.width, d->win.height);
	d->img.addr = mlx_get_data_addr(d->img.img,
			&d->img.bits_per_pixel, &d->img.line_length, &d->img.endian);
	rotate_map(d->map, Z, PI / 6);
	rotate_map(d->map, X, -PI / 6);
}

int	main(int argc, char **argv)
{
	t_data	*d;

	if (argc != 2 && argc != 4)
		exit_with_errout("Usage :", argv[0], "<filename> [ case_size z_size ]");
	d = (t_data *)malloc(sizeof(t_data));
	if (d == NULL)
		exit_with_errout(NULL, NULL, NULL);
	read_map_data(&d->map, argv[1]);
	init_fdf_data(d);
	draw_map(d);
	mlx_hook(d->win.win, KEYPRESS, 1L << 0, key_handler, d);
	mlx_hook(d->win.win, BUTTONPRESS, 1L << 2, mouse_press_handler, d);
	mlx_loop(d->mlx);
	return (0);
}
