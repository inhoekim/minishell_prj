/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasong <dasong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:17:00 by dasong            #+#    #+#             */
/*   Updated: 2023/03/20 21:25:00 by dasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static int	ft_strlen(char *str);

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_len;
	size_t	i;

	d_len = ft_strlen((char *)dst);
	i = 0;
	while (src[i] && i + d_len + 1 < dstsize)
	{
		dst[d_len + i] = src[i];
		i++;
	}
	dst[d_len + i] = '\0';
	if (d_len > dstsize)
		return (ft_strlen((char *)src) + dstsize);
	else
		return (ft_strlen((char *)src) + d_len);
}

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
