/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:38:31 by mkamei            #+#    #+#             */
/*   Updated: 2021/09/16 18:28:00 by mkamei           ###   ########.fr       */
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

static void	parse_str(char *map_value_str, t_map_value *map_value)
{
	char	*comma_ptr;

	(*map_value).z = ato_nbr(map_value_str, 10);
	comma_ptr = ft_strchr(map_value_str, ',');
	if (comma_ptr == NULL)
		(*map_value).color = 0xffffff;
	else
		(*map_value).color = ato_nbr(comma_ptr + 1, 16);
}

static void	init_map_data(t_data *d, char **first_map_strs, t_list *lines_list)
{
	int		y;

	d->width = 0;
	while (first_map_strs[d->width] != NULL)
		d->width++;
	if (d->width == 0)
		exit_with_errout("No data found.", NULL, NULL);
	d->height = ft_lstsize(lines_list);
	d->height -= ((char *)ft_lstlast(lines_list)->content)[0] == '\0';
	d->map = (t_map_value **)malloc(sizeof(t_map_value *) * (d->height + 1));
	if (d->map == NULL)
		exit_with_errout(NULL, NULL, NULL);
	y = -1;
	while (++y < d->height)
	{
		d->map[y] = (t_map_value *)malloc(sizeof(t_map_value) * d->width);
		if (d->map[y] == NULL)
			exit_with_errout(NULL, NULL, NULL);
	}
	d->map[y] = NULL;
}

static void	save_map_data(t_data *d, t_list *lines_list)
{
	int		x;
	int		y;
	t_list	*list;
	char	**map_strs;

	y = -1;
	list = lines_list;
	while (++y == 0 || y < d->height)
	{
		map_strs = ft_split(list->content, ' ');
		if (map_strs == NULL)
			exit_with_errout(NULL, NULL, NULL);
		if (y == 0)
			init_map_data(d, map_strs, lines_list);
		x = -1;
		while (++x < d->width)
		{
			if (map_strs[x] == NULL)
				exit_with_errout("Found wrong line length. Exiting.", 0, 0);
			parse_str(map_strs[x], &d->map[y][d->width - x - 1]);
		}
		free_double_ptr((void **)map_strs);
		list = list->next;
	}
	ft_lstclear(&lines_list, NULL);
}

void	read_fdf_file(t_data *d, char *fdf_file)
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
	return (save_map_data(d, lines_list));
}
