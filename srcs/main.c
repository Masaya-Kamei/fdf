/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:03:27 by mkamei            #+#    #+#             */
/*   Updated: 2021/10/22 10:31:08 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_camera_data(t_data *d, int argc, char **argv)
{
	double	h;

	if (argc == 4)
	{
		d->camera.pixel_per_len = ft_atoi(argv[2]);
		d->camera.z_per_xy = ft_atoi(argv[3]) / d->camera.pixel_per_len;
	}
	else
	{
		d->camera.z_per_xy = 1.125;
		h = hypot(d->map.width / 2, d->map.height / 2)
			+ d->map.max_abs_z * d->camera.z_per_xy;
		d->camera.pixel_per_len
			= (fmin(d->win.width, d->win.height) / 2) / (h + 2);
	}
	d->camera.pixel_per_press = d->camera.pixel_per_len / 10;
	d->camera.angle_per_press = PI / 24.0;
}

static void	init_matrix_2d_data(t_map *map)
{
	int		y;

	map->matrix_2d = malloc(sizeof(t_point_2d *) * (map->height + 1));
	if (map->matrix_2d == NULL)
		exit_with_errout(NULL, NULL, NULL);
	y = -1;
	while (++y < map->height)
	{
		map->matrix_2d[y] = malloc(sizeof(t_point_2d) * map->width);
		if (map->matrix_2d[y] == NULL)
			exit_with_errout(NULL, NULL, NULL);
	}
	map->matrix_2d[y] = NULL;
}

static void	init_sort_data(t_map *map)
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
}

static void	init_fdf_data(t_data *d, int argc, char **argv)
{
	d->basis.ex.x = 1;
	d->basis.ex.y = 0;
	d->basis.ey.x = 0;
	d->basis.ey.y = 0;
	d->basis.ez.x = 0;
	d->basis.ez.y = -1;
	d->win.width = 800;
	d->win.height = 800;
	d->mlx = mlx_init();
	d->win.win = mlx_new_window(d->mlx, d->win.width, d->win.height, "FDF");
	d->img.img = mlx_new_image(d->mlx, d->win.width, d->win.height);
	d->img.addr = mlx_get_data_addr(d->img.img,
			&d->img.bits_per_pixel, &d->img.line_length, &d->img.endian);
	init_camera_data(d, argc, argv);
	init_matrix_2d_data(&d->map);
	init_sort_data(&d->map);
	rotate_3d_map(d->map, Z, -PI / 4);
	rotate_3d_map(d->map, X, asin(tan(-PI / 6)));
}

int	main(int argc, char **argv)
{
	t_data	*d;

	if (argc != 2 && argc != 4)
		exit_with_errout("Usage :", argv[0], "<filename> [ case_size z_size ]");
	d = (t_data *)malloc(sizeof(t_data));
	if (d == NULL)
		exit_with_errout(NULL, NULL, NULL);
	read_3d_map_data(&d->map, argv[1]);
	init_fdf_data(d, argc, argv);
	draw_map(d);
	mlx_hook(d->win.win, KEYPRESS, 1L << 0, key_handler, d);
	mlx_hook(d->win.win, BUTTONPRESS, 1L << 2, mouse_press_handler, d);
	mlx_hook(d->win.win, DESTROYNOTIFY, 1L << 17, finish_fdf, d);
	mlx_loop(d->mlx);
	return (0);
}
