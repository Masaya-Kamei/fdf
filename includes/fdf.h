/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:03:55 by mkamei            #+#    #+#             */
/*   Updated: 2021/09/16 18:10:10 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
#include <stdio.h>

# define GNL_BUFFER_SIZE 100
# define PI 3.14159
# define ESC_KEY 53

typedef enum e_bool
{
	FALSE	= 0,
	TRUE	= 1
}			t_bool;

typedef struct s_map_value
{
	int		z;
	int		color;
}			t_map_value;

typedef struct s_point
{
	float	x;
	float	y;
	int		color;
}			t_point;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_vector
{
	float		x;
	float		y;
}				t_vector;

typedef struct s_data
{
	t_map_value	**map;
	int			width;
	int			height;
	t_vector	ex;
	t_vector	ey;
	int			xy_pixels_per_len;
	int			z_pixels_per_len;
	int			x_shift_pixels;
	int			y_shift_pixels;
	void		*mlx;
	void		*window;
	t_img		img;
}			t_data;

// main
void	read_fdf_file(t_data *d, char *fdf_file);
void	draw_map_to_img(t_data *d);

// utils
int		get_next_line(int fd, char **line);
void	free_double_ptr(void **ptr);
void	exit_with_errout(char *err_msg1, char *err_msg2, char *err_msg3);
void	write_map(t_data *d);

#endif
