/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:03:27 by mkamei            #+#    #+#             */
/*   Updated: 2021/09/17 12:04:31 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_hook(int keycode, t_data *d)
{
	if (keycode == ESC_KEY)
	{
		free_double_ptr((void **)d->map);
		mlx_destroy_window(d->mlx, d->window);
		free(d);
		exit(0);
	}
	return (1);
}

static int	get_z_max(
	t_map_value **map, int width, int height, t_bool minus_flag)
{
	int		max;
	int		x;
	int		y;
	int		z;

	max = 0;
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
		{
			if (minus_flag == 0)
				z = map[y][x].z;
			else
				z = -map[y][x].z;
			if (max < z)
				max = z;
		}
	}
	return (max);
}

static void	init_fdf_data(t_data *d)
{
	int		win_width;
	int		win_height;
	int		z_max;
	int		z_minus_max;

	d->ex.x = cos(5.0 * PI / 6.0);
	d->ex.y = sin(5.0 * PI / 6.0);
	d->ey.x = cos(PI / 6.0);
	d->ey.y = sin(PI / 6.0);
	d->xy_pixels_per_len = 15;
	d->z_pixels_per_len = 20;
	z_max = get_z_max(d->map, d->width, d->height, 0);
	z_minus_max = get_z_max(d->map, d->width, d->height, 1);
	d->x_shift_pixels = fabsf(d->ex.x) * (d->width + 1) * d->xy_pixels_per_len;
	d->y_shift_pixels = (z_max + 1) * d->z_pixels_per_len;
	win_width = (fabsf(d->ex.x) * d->width + fabsf(d->ey.x) * d->height + 2)
		* d->xy_pixels_per_len;
	win_height = (fabsf(d->ex.y) * d->width + fabsf(d->ey.y) * d->height)
		* d->xy_pixels_per_len
		+ (z_max + z_minus_max + 2) * d->z_pixels_per_len;
	d->mlx = mlx_init();
	d->window = mlx_new_window(d->mlx, win_width, win_height, "FDF");
	d->img.img = mlx_new_image(d->mlx, win_width, win_height);
	d->img.addr = mlx_get_data_addr(d->img.img,
			&d->img.bits_per_pixel, &d->img.line_length, &d->img.endian);
}

int	main(int argc, char **argv)
{
	t_data	*d;

	if (argc != 2 && argc != 4)
		exit_with_errout("Usage :", argv[0], "<filename> [ case_size z_size ]");
	d = (t_data *)malloc(sizeof(t_data));
	if (d == NULL)
		exit_with_errout(NULL, NULL, NULL);
	read_fdf_file(d, argv[1]);
	init_fdf_data(d);
	draw_map_to_img(d);
	mlx_put_image_to_window(d->mlx, d->window, d->img.img, 0, 0);
	mlx_key_hook(d->window, key_hook, d);
	mlx_loop(d->mlx);
	return (0);
}
