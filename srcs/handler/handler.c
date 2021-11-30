/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 19:43:10 by mkamei            #+#    #+#             */
/*   Updated: 2021/11/30 12:09:31 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_handler(const int keycode, t_data *d)
{
	if (keycode == ESC_KEY)
		finish_fdf(d);
	else if (keycode == LEFT_KEY || keycode == RIGHT_KEY
		|| keycode == UP_KEY || keycode == DOWN_KEY)
	{
		if (keycode == LEFT_KEY)
			rotate_3d_map(d->map, Z, d->camera.angle_per_press);
		else if (keycode == RIGHT_KEY)
			rotate_3d_map(d->map, Z, -d->camera.angle_per_press);
		else if (keycode == DOWN_KEY)
			rotate_3d_map(d->map, X, -d->camera.angle_per_press);
		else
			rotate_3d_map(d->map, X, d->camera.angle_per_press);
		draw_map(d);
	}
	return (1);
}

int	zoom_handler(const int keycode, const int x, const int y, t_data *d)
{
	(void)x;
	(void)y;
	if (keycode == MOUSE_DOWN || keycode == MOUSE_UP)
	{
		if (keycode == MOUSE_UP)
		{
			d->camera.pixel_per_len -= d->camera.pixel_per_press;
			if (d->camera.pixel_per_len < 0)
				d->camera.pixel_per_len = 0;
		}
		else if (keycode == MOUSE_DOWN)
			d->camera.pixel_per_len += d->camera.pixel_per_press;
		draw_map(d);
	}
	return (1);
}

int	finish_fdf_handler(t_data *d)
{
	finish_fdf(d);
	return (1);
}

int	put_img_handler(t_data *d)
{
	mlx_put_image_to_window(d->mlx, d->win.win, d->img.img, 0, 0);
	return (1);
}
