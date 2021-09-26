/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 13:02:30 by mkamei            #+#    #+#             */
/*   Updated: 2021/09/26 13:48:11 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rec_merge_sort_by_3d_y(
	t_point_3d *p_3ds, t_point_3d *tmp, int start, int end)
{
	const int	middle = (start + end) / 2;
	int			i;
	int			left;
	int			right;

	if (start >= end)
		return ;
	rec_merge_sort_by_3d_y(p_3ds, tmp, start, middle);
	rec_merge_sort_by_3d_y(p_3ds, tmp, middle + 1, end);
	i = 0;
	left = start;
	right = middle + 1;
	while (left <= middle || right <= end)
	{
		if (left > middle)
			tmp[i++] = p_3ds[right++];
		else if (right > end)
			tmp[i++] = p_3ds[left++];
		else if (p_3ds[left].y < p_3ds[right].y)
			tmp[i++] = p_3ds[left++];
		else
			tmp[i++] = p_3ds[right++];
	}
	ft_memcpy(&p_3ds[start], tmp, sizeof(t_point_3d) * (end - start + 1));
}

static void	merge_sort_by_3d_y(t_point_3d *p_3ds, int size)
{
	t_point_3d	*tmp;

	tmp = (t_point_3d *)malloc(sizeof(t_point_3d) * size);
	if (tmp == NULL)
		exit_with_errout(NULL, NULL, NULL);
	rec_merge_sort_by_3d_y(p_3ds, tmp, 0, size - 1);
	free(tmp);
}

t_point_3d	*create_sorted_p_3ds(t_map map)
{
	const int	size = (map.width - 1) * (map.height - 1);
	t_point_3d	*p_3ds;
	int			i;

	p_3ds = (t_point_3d *)malloc(sizeof(t_point_3d) * size);
	if (p_3ds == NULL)
		exit_with_errout(NULL, NULL, NULL);
	i = -1;
	while (++i < map.height - 1)
	{
		ft_memcpy(p_3ds + i * (map.width - 1),
			&map.matrix[i][0], sizeof(t_point_3d) * (map.width - 1));
	}
	merge_sort_by_3d_y(p_3ds, size);
	return (p_3ds);
}
