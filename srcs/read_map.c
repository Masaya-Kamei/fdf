/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:38:31 by mkamei            #+#    #+#             */
/*   Updated: 2021/10/28 15:53:06 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	atoi_in_base(const char *str, const int base)
{
	int		i;
	int		nbr;

	i = 0;
	nbr = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (base == 16 && (str[i] == '0' && str[i + 1] == 'x'))
		i += 2;
	else if (base == 16)
		return (nbr);
	while (1)
	{
		if (str[i] >= '0' && str[i] <= '9')
			nbr = nbr * base + str[i++] - '0';
		else if (base == 16 && str[i] >= 'a' && str[i] <= 'f')
			nbr = nbr * base + str[i++] - 'a' + 10;
		else if (base == 16 && str[i] >= 'A' && str[i] <= 'F')
			nbr = nbr * base + str[i++] - 'A' + 10;
		else
			break ;
	}
	if (str[0] == '-')
		nbr *= -1;
	return (nbr);
}

static void	parse_p_3d_str(t_map *map, char *p_3d_str, const int x, const int y)
{
	char	*comma_ptr;

	map->matrix_3d[y][x].matrix_x = x;
	map->matrix_3d[y][x].matrix_y = y;
	map->matrix_3d[y][x].x = x - map->width / 2.0;
	map->matrix_3d[y][x].y = y - map->height / 2.0;
	map->matrix_3d[y][x].z = atoi_in_base(p_3d_str, 10) * map->z_per_xy;
	if (map->max_abs_z < fabs(map->matrix_3d[y][x].z))
		map->max_abs_z = fabs(map->matrix_3d[y][x].z);
	comma_ptr = ft_strchr(p_3d_str, ',');
	if (comma_ptr == NULL)
		map->matrix_3d[y][x].color = 0xffffff;
	else
		map->matrix_3d[y][x].color = atoi_in_base(comma_ptr + 1, 16);
}

static void	init_3d_map_data(t_map *map, t_list *lines_list)
{
	char	**first_p_3d_strs;

	first_p_3d_strs = ft_split(lines_list->content, ' ');
	if (first_p_3d_strs == NULL)
		exit_with_errout(NULL, NULL, NULL);
	map->width = 0;
	while (first_p_3d_strs[map->width])
		map->width++;
	if (map->width == 0)
		exit_with_errout("No data found.", NULL, NULL);
	free_double_ptr((void **)first_p_3d_strs);
	map->height = ft_lstsize(lines_list);
	if (((char *)(ft_lstlast(lines_list)->content))[0] == '\0')
		map->height--;
	map->max_abs_z = 0;
	map->matrix_3d = (t_point_3d **)create_matrix(
			map->width, map->height, sizeof(t_point_3d));
	if (map->matrix_3d == NULL)
		exit_with_errout(NULL, NULL, NULL);
}

static void	save_3d_map_data(t_map *map, t_list *lines_list)
{
	int		x;
	int		y;
	t_list	*list;
	char	**p_3d_strs;

	init_3d_map_data(map, lines_list);
	y = -1;
	list = lines_list;
	while (++y < map->height)
	{
		p_3d_strs = ft_split(list->content, ' ');
		if (p_3d_strs == NULL)
			exit_with_errout(NULL, NULL, NULL);
		map->matrix_3d[y] = (t_point_3d *)map->matrix_3d[y];
		x = -1;
		while (++x < map->width)
		{
			if (p_3d_strs[x] == NULL)
				exit_with_errout("Found wrong line length. Exiting.", 0, 0);
			parse_p_3d_str(map, p_3d_strs[x], x, y);
		}
		free_double_ptr((void **)p_3d_strs);
		list = list->next;
	}
	ft_lstclear(&lines_list, free);
}

void	read_3d_map_data(t_map *map, const char *file_path)
{
	int		fd;
	char	*line;
	int		gnl_status;
	t_list	dummy_head;
	t_list	*lines_list;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		exit_with_errout("No file", file_path, NULL);
	lines_list = &dummy_head;
	while (1)
	{
		gnl_status = get_next_line(fd, &line);
		if (gnl_status == -1)
			exit_with_errout(NULL, NULL, NULL);
		lines_list->next = ft_lstnew(line);
		if (lines_list->next == NULL)
			exit_with_errout(NULL, NULL, NULL);
		lines_list = lines_list->next;
		if (gnl_status == 0)
			break ;
	}
	if (close(fd) == -1)
		exit_with_errout(NULL, NULL, NULL);
	return (save_3d_map_data(map, dummy_head.next));
}
