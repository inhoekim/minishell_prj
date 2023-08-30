/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdg <sdg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:23:18 by dasong            #+#    #+#             */
/*   Updated: 2023/08/18 14:44:55 by sdg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static int	is_match(const char *str1, const char *str2, size_t len);

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	i;

	if (*little == 0)
		return ((char *)big);
	i = 0;
	while (i < len && big[i])
	{
		if (is_match(big + i, little, len - i))
			return ((char *)big + i);
		i++;
	}
	return (0);
}

static int	is_match(const char *str1, const char *str2, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	if (str2[i] == 0)
		return (1);
	else
		return (0);
}
