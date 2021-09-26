/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 12:14:37 by mkamei            #+#    #+#             */
/*   Updated: 2021/09/26 13:47:47 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point_2d	change_basis(t_basis basis, t_point_3d p_3d)
{
	t_point_2d	p_2d;

	p_2d.x = p_3d.x * basis.ex.x + p_3d.y * basis.ey.x + p_3d.z * basis.ez.x;
	p_2d.y = p_3d.x * basis.ex.y + p_3d.y * basis.ey.y + p_3d.z * basis.ez.y;
	return (p_2d);
}

static t_point_2d	get_2d_point(t_data *d, t_point_3d p_3d)
{
	t_point_2d	p_2d;

	p_3d.x *= d->camera.pixel_per_len;
	p_3d.y *= d->camera.pixel_per_len;
	p_3d.z *= d->camera.pixel_per_len * d->camera.z_per_xy;
	p_2d = change_basis(d->basis, p_3d);
	p_2d.x += d->win.width / 2;
	p_2d.y += d->win.height / 2;
	p_2d.color = p_3d.color;
	return (p_2d);
}

static void	my_mlx_pixel_put(t_img img, int x, int y, int color)
{
	char	*dst;

	dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	draw_line(t_data *d, t_point_2d p, t_point_2d q)
{
	double	x_step;
	double	y_step;
	int		color_step[3];
	int		count;

	x_step = q.x - p.x;
	y_step = q.y - p.y;
	color_step[0] = (q.color >> 16 & 0x0000ff ) - (p.color >> 16 & 0x0000ff);
	color_step[1] = (q.color >> 8 & 0x0000ff) - (p.color >> 8 & 0x0000ff);
	color_step[2] = (q.color & 0x0000ff) - (p.color & 0x0000ff);
	count = ceil(fmax(fabs(x_step), fabs(y_step)));
	if (count == 0)
		return ;
	x_step /= count;
	y_step /= count;
	color_step[0] = ((color_step[0] / count) << 16)
		+ ((color_step[1] / count) << 8) + (color_step[2] / count);
	while (--count >= 0)
	{
		if (p.x >= 0 && p.x < d->win.width && p.y >= 0 && p.y < d->win.height)
			my_mlx_pixel_put(d->img, p.x, p.y, p.color);
		p.x += x_step;
		p.y += y_step;
		p.color += color_step[0];
	}
}

void	draw_map(t_data *d)
{
	t_point_3d	*sorted_p_3ds;
	t_point_2d	p_2d;
	int			i;
	int			x;
	int			y;

	ft_memset(d->img.addr, 0x000000,
		d->win.width * d->win.height * (d->img.bits_per_pixel / 8));
	sorted_p_3ds = create_sorted_p_3ds(d->map);
	i = -1;
	while (++i < (d->map.width - 1) * (d->map.height - 1))
	{
		x = sorted_p_3ds[i].map_x;
		y = sorted_p_3ds[i].map_y;
		p_2d = get_2d_point(d, d->map.matrix[y][x]);
		draw_line(d, p_2d, get_2d_point(d, d->map.matrix[y + 1][x]));
		draw_line(d, p_2d, get_2d_point(d, d->map.matrix[y][x + 1]));
		draw_line(d, p_2d, get_2d_point(d, d->map.matrix[y + 1][x + 1]));
	}
	free(sorted_p_3ds);
	mlx_put_image_to_window(d->mlx, d->win.win, d->img.img, 0, 0);
}
