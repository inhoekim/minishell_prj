/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasong <dasong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:50:10 by dasong            #+#    #+#             */
/*   Updated: 2023/03/20 21:24:32 by dasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	int		flag;

	if (!dst && !src)
		return (0);
	if (dst > src)
		flag = 1;
	else
		flag = 0;
	i = 0;
	while (i < len)
	{
		if (flag == 1)
			((char *)dst)[len - 1 - i] = ((char *)src)[len - 1 - i];
		else
			((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}
