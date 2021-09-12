/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:38:31 by mkamei            #+#    #+#             */
/*   Updated: 2021/09/12 12:40:47 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	parse_str(char *str, int *z, int *color)
{
	int		i;
	char	*comma_ptr;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	*z = 0;
	while (str[i] >= '0' && str[i] <= '9')
		*z = *z * 10 + str[i++] - '0';
	if (str[0] == '-')
		*z *= -1;
	comma_ptr = ft_strchr(str, ',');
	if (comma_ptr == NULL)
		*color = 0x00ffff;
	else
		*color = 0x00ffff;
}

static int	**create_matrix(int width, int height)
{
	int		**matrix;
	int		i;

	matrix = (int **)malloc(sizeof(int *) * height);
	if (matrix == NULL)
		return (NULL);
	i = 0;
	while (i < height)
	{
		matrix[i] = (int *)malloc(sizeof(int) * width);
		if (matrix[i] == NULL)
		{
			free_double_ptr((void **)matrix);
			return (NULL);
		}
		i++;
	}
	return (matrix);
}

static void	init_fdf_data(t_data *d, t_list *lines_list)
{
	char	**strs;

	strs = ft_split(lines_list->content, ' ');
	if (strs == NULL)
		exit_with_errout(NULL, NULL, NULL);
	d->width = 0;
	while (strs[d->width] != NULL)
		d->width++;
	free_double_ptr((void **)strs);
	if (d->width == 0)
		exit_with_errout("No data found.", NULL, NULL);
	d->height = ft_lstsize(lines_list);
	d->height -= ((char *)ft_lstlast(lines_list)->content)[0] == '\0';
	d->z_matrix = create_matrix(d->width, d->height);
	if (d->z_matrix == NULL)
		exit_with_errout(NULL, NULL, NULL);
	d->color_matrix = create_matrix(d->width, d->height);
	if (d->color_matrix == NULL)
		exit_with_errout(NULL, NULL, NULL);
}

	// int		i;

	// matrix = (t_point **)malloc(sizeof(t_point *) * d->height);
	// if (matrix == NULL)
	// 	exit_with_errout(NULL, NULL, NULL);
	// i = -1;
	// while (++i < height)
	// {
	// 	matrix[i] = (int *)malloc(sizeof(int) * width);
	// 	if (matrix[i] == NULL)
	// 		exit_with_errout(NULL, NULL, NULL);
	// }

static void	save_fdf_data(t_data *d, t_list *lines_list)
{
	int		x;
	int		y;
	t_list	*list;
	char	**strs;

	init_fdf_data(d, lines_list);
	y = -1;
	list = lines_list;
	while (++y < d->height)
	{
		strs = ft_split(list->content, ' ');
		if (strs == NULL)
			exit_with_errout(NULL, NULL, NULL);
		x = -1;
		while (++x < d->width)
		{
			if (strs[x] == NULL)
				exit_with_errout("Found wrong line length. Exiting.", 0, 0);
			parse_str(strs[x], &d->z_matrix[y][x], &d->color_matrix[y][x]);
		}
		free_double_ptr((void **)strs);
		list = list->next;
	}
	ft_lstclear(&lines_list, NULL);
}

void	read_file(t_data *d, char *fdf_file)
{
	int		fd;
	char	*line;
	int		gnl_status;
	t_list	*new_list;
	t_list	*lines_list;

	fd = open(fdf_file, O_RDONLY);
	if (fd == -1)
		exit_with_errout("No file", fdf_file, NULL);
	lines_list = NULL;
	gnl_status = 1;
	while (gnl_status != 0)
	{
		gnl_status = get_next_line(fd, &line);
		if (gnl_status == -1)
			exit_with_errout(NULL, NULL, NULL);
		new_list = ft_lstnew(line);
		if (new_list == NULL)
			exit_with_errout(NULL, NULL, NULL);
		ft_lstadd_back(&lines_list, new_list);
	}
	if (close(fd) == -1)
		exit_with_errout(NULL, NULL, NULL);
	return (save_fdf_data(d, lines_list));
}
