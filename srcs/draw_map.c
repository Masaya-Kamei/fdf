/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 12:14:37 by mkamei            #+#    #+#             */
/*   Updated: 2021/09/16 18:23:57 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	transform_coordinates(t_vector ex, t_vector ey, t_point p[2])
{
	float	oldx;
	float	oldy;

	oldx = p[0].x;
	oldy = p[0].y;
	p[0].x = oldx * ex.x + oldy * ey.x;
	p[0].y = oldx * ex.y + oldy * ey.y;
	oldx = p[1].x;
	oldy = p[1].y;
	p[1].x = oldx * ex.x + oldy * ey.x;
	p[1].y = oldx * ex.y + oldy * ey.y;
}

static void	edix_xy_component(t_data *d, t_point p[2])
{
	float	z[2];

	z[0] = d->map[(int)p[0].y][(int)p[0].x].z;
	z[1] = d->map[(int)p[1].y][(int)p[1].x].z;
	transform_coordinates(d->ex, d->ey, p);
	p[0].x *= d->xy_pixels_per_len;
	p[1].x *= d->xy_pixels_per_len;
	p[0].y *= d->xy_pixels_per_len;
	p[1].y *= d->xy_pixels_per_len;
	p[0].y -= z[0] * d->z_pixels_per_len;
	p[1].y -= z[1] * d->z_pixels_per_len;
	p[0].x += d->x_shift_pixels;
	p[1].x += d->x_shift_pixels;
	p[0].y += d->y_shift_pixels;
	p[1].y += d->y_shift_pixels;
}

static void	my_mlx_pixel_put(t_img img, int x, int y, int color)
{
	char	*dst;

	dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	draw_line_segment(t_data *d, t_point p[2])
{
	float	x_step;
	float	y_step;
	int		color_step[3];
	float	count;

	x_step = p[1].x - p[0].x;
	y_step = p[1].y - p[0].y;
	color_step[0] = ((p[1].color & 0xff0000) - (p[0].color & 0xff0000)) >> 16;
	color_step[1] = ((p[1].color & 0x00ff00) - (p[0].color & 0x00ff00)) >> 8;
	color_step[2] = (p[1].color & 0x0000ff) - (p[0].color & 0x0000ff);
	count = fmaxf(fabsf(x_step), fabsf(y_step));
	x_step /= count;
	y_step /= count;
	color_step[0] = (color_step[0] / (int)count) << 16;
	color_step[1] = (color_step[1] / (int)count) << 8;
	color_step[2] = color_step[2] / (int)count;
	while ((int)(p[0].x - p[1].x) || (int)(p[0].y - p[1].y))
	{
		my_mlx_pixel_put(d->img, p[0].x, p[0].y, p[0].color);
		p[0].x += x_step;
		p[0].y += y_step;
		p[0].color += color_step[0] + color_step[1] + color_step[2];
	}
}

void	draw_map_to_img(t_data *d)
{
	int		x;
	int		y;
	int		i;
	t_point	p[2];

	y = -1;
	while (++y < d->height - 1)
	{
		x = -1;
		while (++x < d->width - 1)
		{
			i = -1;
			while (++i < 3)
			{
				p[0].x = x;
				p[1].x = x + (i == 0 || i == 2);
				p[0].y = y;
				p[1].y = y + (i == 1 || i == 2);
				p[0].color = d->map[(int)p[0].y][(int)p[0].x].color;
				p[1].color = d->map[(int)p[1].y][(int)p[1].x].color;
				edix_xy_component(d, p);
				draw_line_segment(d, p);
			}
		}
	}
}
