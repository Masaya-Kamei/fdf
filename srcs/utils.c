/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:40:09 by mkamei            #+#    #+#             */
/*   Updated: 2021/09/12 12:08:58 by mkamei           ###   ########.fr       */
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

void	exit_with_errout(char *err_msg1, char *err_msg2, char *err_msg3)
{
	if (err_msg1 != NULL)
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
	exit(1);
}

void	write_matrix(t_data *d)
{
	int		x;
	int		y;

	y = 0;
	while (y < d->height)
	{
		x = 0;
		while (x < d->width)
		{
			if (x != 0)
				write(1, "   ", 3);
			ft_putnbr_fd(d->z_matrix[y][x], 1);
			write(1, ",", 2);
			ft_putnbr_fd(d->color_matrix[y][x], 1);
			x++;
		}
		write(1, "\n", 1);
		y++;
	}
}
