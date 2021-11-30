/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:03:27 by mkamei            #+#    #+#             */
/*   Updated: 2021/11/30 12:02:49 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	read_cmd_arg(t_data *d, const int argc, char **argv)
{
	int		n3;
	int		n4;

	if (argc == 4)
	{
		n3 = ft_atoi(argv[3]);
		n4 = ft_atoi(argv[4]);
		if (n3 > 0 && n4 > 0)
		{
			d->camera.pixel_per_len = n3;
			d->map.z_per_xy = n4 / n3;
			return ;
		}
	}
	d->camera.pixel_per_len = 0;
	d->map.z_per_xy = 1.125;
}

int	main(int argc, char **argv)
{
	t_data	*d;

	if (argc != 2 && argc != 4)
		exit_with_errout("Usage :", argv[0], "<filename> [ case_size z_size ]");
	d = (t_data *)malloc(sizeof(t_data));
	if (d == NULL)
		exit_with_errout(NULL, NULL, NULL);
	read_cmd_arg(d, argc, argv);
	read_3d_map_data(&d->map, argv[1]);
	init_fdf_data(d);
	draw_map(d);
	mlx_hook(d->win.win, KEYPRESS, 1L << 0, key_handler, d);
	mlx_hook(d->win.win, BUTTONPRESS, 1L << 2, zoom_handler, d);
	mlx_hook(d->win.win, DESTROYNOTIFY, 1L << 17, finish_fdf_handler, d);
	mlx_hook(d->win.win, FOCUSIN, 1L << 21, put_img_handler, &d);
	mlx_loop(d->mlx);
	return (0);
}
