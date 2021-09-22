/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:38:31 by mkamei            #+#    #+#             */
/*   Updated: 2021/09/22 17:40:45 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ato_nbr(char *str, int base)
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

static void	parse_str(char *map_value_str, t_map *map, int x, int y)
{
	char	*comma_ptr;

	map->matrix[y][x].x = x - map->width / 2.0;
	map->matrix[y][x].y = y - map->height / 2.0;
	map->matrix[y][x].z = ato_nbr(map_value_str, 10);
	comma_ptr = ft_strchr(map_value_str, ',');
	if (comma_ptr == NULL)
		map->matrix[y][x].color = 0xffffff;
	else
		map->matrix[y][x].color = ato_nbr(comma_ptr + 1, 16);
}

static void	init_map_data(t_map *map, char **first_map_strs, t_list *lines_list)
{
	int		y;

	map->width = 0;
	while (first_map_strs[map->width] != NULL)
		map->width++;
	if (map->width == 0)
		exit_with_errout("No data found.", NULL, NULL);
	map->height = ft_lstsize(lines_list);
	map->height -= ((char *)(ft_lstlast(lines_list)->content))[0] == '\0';
	map->matrix = malloc(sizeof(t_point_3d *) * (map->height + 1));
	if (map->matrix == NULL)
		exit_with_errout(NULL, NULL, NULL);
	y = -1;
	while (++y < map->height)
	{
		map->matrix[y] = malloc(sizeof(t_point_3d) * map->width);
		if (map->matrix[y] == NULL)
			exit_with_errout(NULL, NULL, NULL);
	}
	map->matrix[y] = NULL;
}

static void	save_map_data(t_map *map, t_list *lines_list)
{
	int		x;
	int		y;
	t_list	*list;
	char	**map_strs;

	y = -1;
	list = lines_list;
	while (++y == 0 || y < map->height)
	{
		map_strs = ft_split(list->content, ' ');
		if (map_strs == NULL)
			exit_with_errout(NULL, NULL, NULL);
		if (y == 0)
			init_map_data(map, map_strs, lines_list);
		x = -1;
		while (++x < map->width)
		{
			if (map_strs[x] == NULL)
				exit_with_errout("Found wrong line length. Exiting.", 0, 0);
			parse_str(map_strs[x], map, x, y);
		}
		free_double_ptr((void **)map_strs);
		list = list->next;
	}
	ft_lstclear(&lines_list, NULL);
}

void	read_map_data(t_map *map, char *fdf_file)
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
	return (save_map_data(map, lines_list));
}
