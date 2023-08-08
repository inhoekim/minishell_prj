/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasong <dasong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:41:32 by dasong            #+#    #+#             */
/*   Updated: 2023/03/20 21:24:58 by dasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		total;
	char	*res;
	int		i;

	if (!s1 || !s2)
		return (0);
	total = ft_strlen(s1) + ft_strlen(s2) + 1;
	res = (char *)malloc(sizeof(char) * total);
	if (!res)
		return (0);
	res[total - 1] = '\0';
	i = 0;
	while (*s1)
	{
		res[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		res[i] = *s2;
		s2++;
		i++;
	}
	return (res);
}
