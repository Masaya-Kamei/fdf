/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 12:14:37 by mkamei            #+#    #+#             */
/*   Updated: 2021/09/22 17:55:49 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point_2d	change_basis(
	t_basis basis, float x_3d, float y_3d, float z_3d)
{
	t_point_2d	p_2d;

	p_2d.x = (x_3d * basis.ex.x) + (y_3d * basis.ey.x) + (z_3d * basis.ez.x);
	p_2d.y = (x_3d * basis.ex.y) + (y_3d * basis.ey.y) + (z_3d * basis.ez.y);
	return (p_2d);
}

static t_point_2d	get_2d_point(t_data *d, int x, int y)
{
	t_point_2d	p_2d;
	float		x_3d;
	float		y_3d;
	float		z_3d;
	const int	color = d->map.matrix[y][x].color;

	x_3d = d->map.matrix[y][x].x * d->camera.pixels_per_len;
	y_3d = d->map.matrix[y][x].y * d->camera.pixels_per_len;
	z_3d = d->map.matrix[y][x].z * d->camera.pixels_per_len * d->camera.z_rate;
	p_2d = change_basis(d->basis, x_3d, y_3d, z_3d);
	p_2d.x += d->win.width / 2;
	p_2d.y += d->win.height / 2;
	p_2d.color = color;
	return (p_2d);
}

static void	my_mlx_pixel_put(t_img img, int x, int y, int color)
{
	char	*dst;

	dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	draw_line_segment(
	t_img img, t_win win, t_point_2d p0, t_point_2d p1)
{
	float	x_step;
	float	y_step;
	int		color_step[3];
	float	count;

	x_step = p1.x - p0.x;
	y_step = p1.y - p0.y;
	color_step[0] = (p1.color >> 16 & 0x0000ff ) - (p0.color >> 16 & 0x0000ff);
	color_step[1] = (p1.color >> 8 & 0x0000ff) - (p0.color >> 8 & 0x0000ff);
	color_step[2] = (p1.color & 0x0000ff) - (p0.color & 0x0000ff);
	count = fmaxf(fabsf(x_step), fabsf(y_step));
	if (count < 1)
		count = 1;
	x_step /= count;
	y_step /= count;
	color_step[0] = ((color_step[0] / (int)count) << 16)
		+ ((color_step[1] / (int)count) << 8) + (color_step[2] / (int)count);
	while ((int)(p0.x - p1.x) || (int)(p0.y - p1.y))
	{
		if (p0.x >= 0 && p0.x < win.width && p0.y >= 0 && p0.y < win.height)
			my_mlx_pixel_put(img, p0.x, p0.y, p0.color);
		p0.x += x_step;
		p0.y += y_step;
		p0.color += color_step[0];
	}
}

void	draw_map(t_data *d)
{
	int			x;
	int			y;
	t_point_2d	p0;
	t_point_2d	p1;
	int			i;

	ft_memset(d->img.addr, 0x000000,
		d->win.width * d->win.height * (d->img.bits_per_pixel / 8));
	y = -1;
	while (++y < d->map.height - 1)
	{
		x = -1;
		while (++x < d->map.width - 1)
		{
			i = -1;
			while (++i < 3)
			{
				p0 = get_2d_point(d, x, y);
				p1 = get_2d_point(d,
						x + (i == 0 || i == 2), y + (i == 1 || i == 2));
				draw_line_segment(d->img, d->win, p0, p1);
			}
		}
	}
	mlx_put_image_to_window(d->mlx, d->win.win, d->img.img, 0, 0);
}
