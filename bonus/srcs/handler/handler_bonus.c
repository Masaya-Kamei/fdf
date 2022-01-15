/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 19:43:10 by mkamei            #+#    #+#             */
/*   Updated: 2022/01/15 15:27:41 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	key_handler(const int keycode, t_data *d)
{
	if (keycode == ESC_KEY)
		finish_fdf(d);
	else if (keycode == LEFT_KEY || keycode == RIGHT_KEY
		|| keycode == UP_KEY || keycode == DOWN_KEY)
	{
		if (keycode == LEFT_KEY)
			rotate_3d_map(&d->map, Z, d->camera.angle_per_press);
		else if (keycode == RIGHT_KEY)
			rotate_3d_map(&d->map, Z, -d->camera.angle_per_press);
		else if (keycode == DOWN_KEY)
			rotate_3d_map(&d->map, X, -d->camera.angle_per_press);
		else
			rotate_3d_map(&d->map, X, d->camera.angle_per_press);
		draw_map(d);
	}
	return (0);
}

int	zoom_handler(const int keycode, const int x, const int y, t_data *d)
{
	double	zoom_per_press;

	(void)x;
	(void)y;
	if (keycode == MOUSE_DOWN || keycode == MOUSE_UP)
	{
		if (keycode == MOUSE_UP)
			zoom_per_press = 1 / d->camera.zoom_per_press;
		else
			zoom_per_press = d->camera.zoom_per_press;
		zoom_3d_map(&d->map, zoom_per_press, zoom_per_press);
		draw_map(d);
	}
	return (0);
}

int	finish_fdf_handler(t_data *d)
{
	finish_fdf(d);
	return (0);
}

int	put_img_handler(t_data *d)
{
	mlx_put_image_to_window(d->mlx, d->win.win, d->img.img, 0, 0);
	return (0);
}
