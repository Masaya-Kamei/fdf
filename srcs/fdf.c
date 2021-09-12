/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:03:27 by mkamei            #+#    #+#             */
/*   Updated: 2021/09/12 16:41:52 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_hook(int keycode, t_data *d)
{
	if (keycode == ESC_KEY)
	{
		free_double_ptr(d->z_matrix);
		free_double_ptr(d->color_matrix);
		mlx_destroy_window(d->mlx, d->window);
		free(d);
		exit(0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*d;

	if (argc != 2 && argc != 4)
		exit_with_errout("Usage :", argv[0], "<filename> [ case_size z_size ]");
	d = (t_data *)malloc(sizeof(t_data));
	if (d == NULL)
		exit_with_errout(NULL, NULL, NULL);
	read_file(d, argv[1]);
	// write_matrix(d);
	d->mlx = mlx_init();
	d->window = mlx_new_window(d->mlx, 1000, 1000, "FDF");
	mlx_key_hook(d->window, key_hook, &d);
	mlx_loop(d->mlx);
	return (0);
}
