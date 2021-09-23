/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:03:55 by mkamei            #+#    #+#             */
/*   Updated: 2021/09/23 19:47:36 by mkamei           ###   ########.fr       */
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
# define MOUSE_DOWN 4
# define MOUSE_UP 5

// X11 events
# define KEYPRESS 2
# define BUTTONPRESS 4

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
	double		x;
	double		y;
	int			color;
}				t_point_2d;

typedef struct s_point_3d
{
	double		x;
	double		y;
	double		z;
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
	double		pixel_per_len;
	double		pixel_per_press;
	double		angle_per_press;
	double		z_per_xy;
}				t_camera;

typedef struct s_vector
{
	double		x;
	double		y;
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
void	rotate_map(t_map map, t_axis_name name, double angle);

// handler
int		key_handler(int keycode, t_data *d);
int		mouse_press_handler(int keycode, int x, int y, t_data *d);

// utils
int		get_next_line(int fd, char **line);
void	free_double_ptr(void **ptr);
void	finish_fdf(t_data *d);
void	exit_with_errout(char *err_msg1, char *err_msg2, char *err_msg3);
void	write_map(t_map map);

#endif
