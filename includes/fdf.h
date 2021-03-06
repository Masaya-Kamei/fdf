/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:03:55 by mkamei            #+#    #+#             */
/*   Updated: 2022/01/16 10:20:22 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>

# define GNL_BUFFER_SIZE 100
# define PI 3.14159

// key
# if __linux__
#  define ESC_KEY 65307
#  define LEFT_KEY 65361
#  define UP_KEY 65362
#  define RIGHT_KEY 65363
#  define DOWN_KEY 65364
# else
#  define ESC_KEY 53
#  define LEFT_KEY 123
#  define RIGHT_KEY 124
#  define DOWN_KEY 125
#  define UP_KEY 126
# endif
# define MOUSE_DOWN 4
# define MOUSE_UP 5

// X11 events
# define KEYPRESS 2
# define BUTTONPRESS 4
# define DESTROYNOTIFY 17
# define FOCUSIN 9

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
	int			matrix_x;
	int			matrix_y;
	int			color;
}				t_point_3d;

typedef struct s_map
{
	t_point_3d	**matrix_3d;
	t_point_2d	**matrix_2d;
	int			width;
	int			height;
	int			max_abs_z;
	t_point_3d	**sorted_p_3d_ptrs;
	t_point_3d	**msort_tmp;
}				t_map;

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

typedef struct s_camera
{
	double		zoom_per_press;
	double		angle_per_press;
	t_basis		basis;
}				t_camera;

typedef struct s_win
{
	void		*win;
	int			width;
	int			height;
}				t_win;

typedef struct s_img
{
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
	void		*mlx;
	t_win		win;
	t_img		img;
}				t_data;

// main
void	read_3d_map_data(t_map *map, const char *file_path);
void	draw_map(t_data *d);

// handler
int		key_handler(const int keycode, t_data *d);
int		zoom_handler(const int keycode, const int x, const int y, t_data *d);
int		finish_fdf_handler(t_data *d);
int		put_img_handler(t_data *d);
void	rotate_3d_map(t_map *map, const t_axis_name name, const double angle);
void	zoom_3d_map(t_map *map, const double xy_zoom, const double z_zoom);

// utils
void	merge_sort_by_3d_y(t_point_3d **p_3d_ptrs,
			t_point_3d **tmp, const int start, const int end);
int		get_next_line(int fd, char **line);
void	free_double_ptr(void **ptr);
void	finish_fdf(t_data *d);
void	exit_with_errout(
			const char *err_msg1, const char *err_msg2, const char *err_msg3);
void	**create_matrix(const int width, const int height, const int size);
void	write_matrix_3d_z(const t_map map);

#endif
