/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:25:04 by seykim            #+#    #+#             */
/*   Updated: 2023/08/30 17:25:05 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	long	res;

	res = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		sign = 1 + -2 * (nptr[i++] == '-');
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (res > LONG_MAX / 10 || (res == LONG_MAX / 10 && nptr[i] - '0' > 7))
		{
			if (sign == 1)
				return ((int)LONG_MAX);
			else
				return ((int)LONG_MIN);
		}
		res = res * 10 + nptr[i++] - '0';
	}
	return ((int)sign * res);
}
