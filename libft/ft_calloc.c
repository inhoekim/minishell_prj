/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasong <dasong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:22:30 by dasong            #+#    #+#             */
/*   Updated: 2023/03/20 21:27:19 by dasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	unsigned char	*res;
	size_t			i;

	res = (unsigned char *)malloc(elsize * nelem);
	if (!res)
		return (0);
	if (elsize)
	{
		i = 0;
		while (i < elsize * nelem)
		{
			res[i] = 0;
			i++;
		}
	}
	return (res);
}
