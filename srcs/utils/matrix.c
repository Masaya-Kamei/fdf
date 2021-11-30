/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 11:32:43 by mkamei            #+#    #+#             */
/*   Updated: 2021/11/30 11:35:10 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
