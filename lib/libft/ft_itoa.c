/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 15:30:11 by mkamei            #+#    #+#             */
/*   Updated: 2021/10/04 12:41:15 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digit_num(int n)
{
	int		digit_num;

	digit_num = 0;
	while (n != 0 && ++digit_num)
		n /= 10;
	return (digit_num);
}

char	*ft_itoa(int n)
{
	const int	digit_num = get_digit_num(n);
	const int	minus_flag = (n < 0);
	const int	sign = 1 - (minus_flag * 2);
	char		*str;
	int			i;

	if (n == 0)
		return (ft_strdup("0"));
	str = (char *)malloc((digit_num + minus_flag + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = digit_num + minus_flag;
	while (n != 0)
	{
		str[--i] = (n % 10) * sign + '0';
		n /= 10;
	}
	if (minus_flag)
		str[0] = '-';
	str[digit_num + minus_flag] = '\0';
	return (str);
}
