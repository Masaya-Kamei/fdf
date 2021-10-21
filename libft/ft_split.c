/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 18:14:01 by mkamei            #+#    #+#             */
/*   Updated: 2021/10/04 18:06:42 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_splited_str_count(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (count);
}

static void	*split_release_handling(char **strs)
{
	int		i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;
	int		len;
	int		strs_index;

	strs = (char **)malloc((get_splited_str_count(s, c) + 1) * sizeof(char *));
	if (strs == NULL)
		return (NULL);
	i = -1;
	strs_index = -1;
	while (s[++i] != '\0')
	{
		if (s[i] != c)
		{
			len = 0;
			while (s[i + len] != c && s[i + len] != '\0')
				len++;
			strs[++strs_index] = ft_substr(s, i, len);
			if (strs[strs_index] == NULL)
				return (split_release_handling(strs));
			i += len - 1;
		}
	}
	strs[++strs_index] = NULL;
	return (strs);
}
