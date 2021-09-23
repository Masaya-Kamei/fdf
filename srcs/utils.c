/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:40:09 by mkamei            #+#    #+#             */
/*   Updated: 2021/09/23 19:47:10 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_double_ptr(void **ptr)
{
	int		i;

	if (ptr == NULL)
		return ;
	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	finish_fdf(t_data *d)
{
	free_double_ptr((void **)d->map.matrix);
	mlx_destroy_image(d->mlx, d->img.img);
	mlx_destroy_window(d->mlx, d->win.win);
	free(d);
	exit(0);
}

void	exit_with_errout(char *err_msg1, char *err_msg2, char *err_msg3)
{
	if (err_msg1 != NULL)
	{
		write(1, err_msg1, ft_strlen(err_msg1));
		if (err_msg2 != NULL)
		{
			write(1, " ", 1);
			write(1, err_msg2, ft_strlen(err_msg2));
		}
		if (err_msg3 != NULL)
		{
			write(1, " ", 1);
			write(1, err_msg3, ft_strlen(err_msg3));
		}
		write(1, "\n", 1);
	}
	else
		perror(NULL);
	exit(1);
}

void	write_map(t_map map)
{
	int		x;
	int		y;

	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			if (x != 0)
				write(1, "   ", 3);
			ft_putnbr_fd(map.matrix[y][x].z, 1);
			x++;
		}
		write(1, "\n", 1);
		y++;
	}
}
