/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:22:03 by dasong            #+#    #+#             */
/*   Updated: 2023/08/16 18:45:06 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*make_empty_str(void);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	size_t			i;
	unsigned int	s_len;

	if (*s == 0)
		return (make_empty_str());
	s_len = (unsigned int)ft_strlen(s);
	if (s_len <= start)
		len = 0;
	i = 0;
	while (i < len && s[start + i])
		i++;
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return (0);
	i = 0;
	while (i < len && s[start + i])
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static char	*make_empty_str(void)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * (1));
	if (!res)
		return (0);
	res[0] = '\0';
	return (res);
}
