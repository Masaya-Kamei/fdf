/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:40:09 by mkamei            #+#    #+#             */
/*   Updated: 2021/10/28 16:05:38 by mkamei           ###   ########.fr       */
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

int	finish_fdf(t_data *d)
{
	free_double_ptr((void **)d->map.matrix_3d);
	free_double_ptr((void **)d->map.matrix_2d);
	free(d->map.sorted_p_3d_ptrs);
	free(d->map.msort_tmp);
	mlx_destroy_image(d->mlx, d->img.img);
	mlx_destroy_window(d->mlx, d->win.win);
	free(d);
	exit(0);
}

void	exit_with_errout(
	const char *err_msg1, const char *err_msg2, const char *err_msg3)
{
	if (err_msg1)
	{
		write(1, err_msg1, ft_strlen(err_msg1));
		if (err_msg2)
		{
			write(1, " ", 1);
			write(1, err_msg2, ft_strlen(err_msg2));
		}
		if (err_msg3)
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

void	**create_matrix(const int width, const int height, const int size)
{
	void	**matrix;
	int		y;

	matrix = malloc(__SIZEOF_POINTER__ * (height + 1));
	if (matrix == NULL)
		return (NULL);
	y = -1;
	while (++y < height)
	{
		matrix[y] = malloc(size * width);
		if (matrix[y] == NULL)
		{
			free_double_ptr(matrix);
			return (NULL);
		}
	}
	matrix[y] = NULL;
	return (matrix);
}

void	write_matrix_3d_z(const t_map map)
{
	int		x;
	int		y;

	y = -1;
	while (y < map.height)
	{
		x = -1;
		while (x < map.width)
		{
			if (x != 0)
				write(1, "   ", 3);
			ft_putnbr_fd(map.matrix_3d[y][x].z, 1);
		}
		write(1, "\n", 1);
	}
}
