/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasong <dasong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:23:09 by dasong            #+#    #+#             */
/*   Updated: 2023/03/30 03:34:49 by dasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	int		len;
	int		i;
	char	*res;

	len = 0;
	while (s[len])
		len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	i = 0;
	while (i < len + 1)
	{
		res[i] = s[i];
		i++;
	}
	return (res);
}
