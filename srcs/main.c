/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:03:27 by mkamei            #+#    #+#             */
/*   Updated: 2021/12/07 16:49:27 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	map->matrix_2d = (t_point_2d **)
		create_matrix(map->width, map->height, sizeof(t_point_2d));
	if (map->matrix_2d == NULL)
		exit_with_errout(NULL, NULL, NULL);
}

static void	get_pixel_per_len(
	t_data *d, char **argv, double *xy_pixel_per_len, double *z_pixel_per_len)
{
	int		n2;
	int		n3;
	double	h;

	if (argv[2])
	{
		n2 = ft_atoi(argv[2]);
		n3 = ft_atoi(argv[3]);
		if (n2 > 0 && n3 > 0)
		{
			*xy_pixel_per_len = n2;
			*z_pixel_per_len = n3;
			return ;
		}
	}
	h = hypot(d->map.width / 2, d->map.height / 2) + d->map.max_abs_z;
	*xy_pixel_per_len = (fmin(d->win.width, d->win.height) / 2) / h;
	*z_pixel_per_len = *xy_pixel_per_len * 1.125;
}

static void	init_fdf_data(t_data *d, char **argv)
{
	double	xy_pixel_per_len;
	double	z_pixel_per_len;

	init_map_data(&d->map);
	d->win.width = 800;
	d->win.height = 800;
	d->mlx = mlx_init();
	d->win.win = mlx_new_window(d->mlx, d->win.width, d->win.height, "FDF");
	d->img.img = mlx_new_image(d->mlx, d->win.width, d->win.height);
	d->img.addr = mlx_get_data_addr(d->img.img,
			&d->img.bits_per_pixel, &d->img.line_length, &d->img.endian);
	d->camera.basis.ex.x = 1;
	d->camera.basis.ex.y = 0;
	d->camera.basis.ey.x = 0;
	d->camera.basis.ey.y = 0;
	d->camera.basis.ez.x = 0;
	d->camera.basis.ez.y = -1;
	d->camera.zoom_per_press = 1.1;
	d->camera.angle_per_press = PI / 24.0;
	get_pixel_per_len(d, argv, &xy_pixel_per_len, &z_pixel_per_len);
	zoom_3d_map(&d->map, xy_pixel_per_len, z_pixel_per_len);
	rotate_3d_map(&d->map, Z, -PI / 4);
	rotate_3d_map(&d->map, X, asin(tan(-PI / 6)));
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
	init_fdf_data(d, argv);
	draw_map(d);
	mlx_hook(d->win.win, KEYPRESS, 1L << 0, key_handler, d);
	mlx_hook(d->win.win, BUTTONPRESS, 1L << 2, zoom_handler, d);
	mlx_hook(d->win.win, DESTROYNOTIFY, 1L << 17, finish_fdf_handler, d);
	mlx_hook(d->win.win, FOCUSIN, 1L << 21, put_img_handler, d);
	mlx_loop(d->mlx);
	return (0);
}
