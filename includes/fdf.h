/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:03:55 by mkamei            #+#    #+#             */
/*   Updated: 2021/09/12 16:24:32 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
#include <stdio.h>

# define GNL_BUFFER_SIZE 100
# define ESC_KEY 53

typedef enum e_bool
{
	FALSE	= 0,
	TRUE	= 1
}			t_bool;

typedef struct s_data
{
	int		**z_matrix;
	int		**color_matrix;
	int		width;
	int		height;
	void	*mlx;
	void	*window;
}			t_data;

// main
void	read_file(t_data *d, char *fdf_file);

// utils
int		get_next_line(int fd, char **line);
void	free_double_ptr(void **ptr);
void	exit_with_errout(char *err_msg1, char *err_msg2, char *err_msg3);
void	write_matrix(t_data *d);

#endif
