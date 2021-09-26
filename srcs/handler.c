/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 19:43:10 by mkamei            #+#    #+#             */
/*   Updated: 2021/09/24 21:06:50 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_handler(int keycode, t_data *d)
{
	if (keycode == ESC_KEY)
		finish_fdf(d);
	else if (keycode == LEFT_KEY || keycode == RIGHT_KEY
		|| keycode == UP_KEY || keycode == DOWN_KEY)
	{
		if (keycode == LEFT_KEY)
			rotate_map(d->map, Z, d->camera.angle_per_press);
		else if (keycode == RIGHT_KEY)
			rotate_map(d->map, Z, -d->camera.angle_per_press);
		else if (keycode == DOWN_KEY)
			rotate_map(d->map, X, -d->camera.angle_per_press);
		else
			rotate_map(d->map, X, d->camera.angle_per_press);
		draw_map(d);
	}
	return (1);
}

int	mouse_press_handler(int keycode, int x, int y, t_data *d)
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
