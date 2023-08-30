/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasong <dasong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 23:41:35 by dasong            #+#    #+#             */
/*   Updated: 2023/03/18 01:08:06 by dasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			allocate_res(char *res, long long l_n, int len);
static long long	ft_abs(long long a);

char	*ft_itoa(int n)
{
	int			len;
	char		*res;
	long long	l_n;
	long long	tmp_n;

	l_n = n;
	len = 0;
	tmp_n = ft_abs(l_n);
	while (tmp_n)
	{
		len++;
		tmp_n /= 10;
	}
	if (l_n <= 0)
		len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	if (l_n == 0)
		res[0] = '0';
	else if (l_n < 0)
		res[0] = '-';
	allocate_res(res, l_n, len);
	return (res);
}

static long long	ft_abs(long long a)
{
	if (a < 0)
		a *= -1;
	return (a);
}

static void	allocate_res(char *res, long long l_n, int len)
{
	long long	tmp_n;
	int			i;

	tmp_n = ft_abs(l_n);
	i = 0;
	while (tmp_n)
	{
		res[len - 1 - i++] = tmp_n % 10 + '0';
		tmp_n /= 10;
	}
	res[len] = '\0';
}
