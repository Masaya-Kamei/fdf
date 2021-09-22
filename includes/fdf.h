/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:03:55 by mkamei            #+#    #+#             */
/*   Updated: 2021/09/22 17:34:23 by mkamei           ###   ########.fr       */
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

// key
# define ESC_KEY 53
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define DOWN_KEY 125
# define UP_KEY 126

typedef enum e_bool
{
	FALSE	= 0,
	TRUE	= 1
}			t_bool;

typedef enum e_axis_name
{
	X		= 0,
	Y		= 1,
	Z		= 2
}			t_axis_name;

typedef struct s_point_2d
{
	float		x;
	float		y;
	int			color;
}				t_point_2d;

typedef struct s_point_3d
{
	float		x;
	float		y;
	float		z;
	int			color;
}				t_point_3d;

typedef struct s_map
{
	t_point_3d	**matrix;
	int			width;
	int			height;
}				t_map;

typedef struct s_camera
{
	int			pixels_per_len;
	float		z_rate;
}				t_camera;

typedef struct s_vector
{
	float		x;
	float		y;
}				t_vector;

typedef struct s_basis
{
	t_vector	ex;
	t_vector	ey;
	t_vector	ez;
}				t_basis;

typedef struct s_win
{
	void		*win;
	int			width;
	int			height;
}				t_win;

typedef struct s_img {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_data
{
	t_map		map;
	t_camera	camera;
	t_basis		basis;
	void		*mlx;
	t_win		win;
	t_img		img;
}				t_data;

// main
void	read_map_data(t_map *map, char *fdf_file);
void	draw_map(t_data *d);
void	rotate_map(t_map map, t_axis_name name, float angle);

// utils
int		get_next_line(int fd, char **line);
void	free_double_ptr(void **ptr);
void	exit_with_errout(char *err_msg1, char *err_msg2, char *err_msg3);
void	write_map(t_map map);

#endif
