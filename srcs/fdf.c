/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:03:27 by mkamei            #+#    #+#             */
/*   Updated: 2021/09/12 12:12:29 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_data	*d;

	if (argc != 2 && argc != 4)
		exit_with_errout("Usage :", argv[0], "<filename> [ case_size z_size ]");
	d = (t_data *)malloc(sizeof(t_data));
	if (d == NULL)
		exit(1);
	read_file(d, argv[1]);
	write_matrix(d);
	free(d);
	return (0);
}
