/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 13:02:30 by mkamei            #+#    #+#             */
/*   Updated: 2021/10/21 11:57:02 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	merge_sort_by_3d_y(
	t_point_3d **p_3d_ptrs, t_point_3d **tmp, const int start, const int end)
{
	const int	middle = (start + end) / 2;
	int			i;
	int			left;
	int			right;

	if (start >= end)
		return ;
	merge_sort_by_3d_y(p_3d_ptrs, tmp, start, middle);
	merge_sort_by_3d_y(p_3d_ptrs, tmp, middle + 1, end);
	i = 0;
	left = start;
	right = middle + 1;
	while (left <= middle || right <= end)
	{
		if (left > middle)
			tmp[i++] = p_3d_ptrs[right++];
		else if (right > end)
			tmp[i++] = p_3d_ptrs[left++];
		else if (p_3d_ptrs[left]->y < p_3d_ptrs[right]->y)
			tmp[i++] = p_3d_ptrs[left++];
		else
			tmp[i++] = p_3d_ptrs[right++];
	}
	ft_memcpy(&p_3d_ptrs[start], tmp, sizeof(t_point_3d *) * (end - start + 1));
}
