/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasong <dasong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 22:15:48 by dasong            #+#    #+#             */
/*   Updated: 2023/03/18 03:33:46 by dasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in(char ch, const char *set);
static char	*make_empty_str(void);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		i;
	int		j;
	int		k;

	if (*s1 == 0)
		return (make_empty_str());
	i = 0;
	while (is_in(s1[i], set))
		i++;
	if (s1[i] == '\0')
		return (make_empty_str());
	j = ft_strlen(s1) - 1;
	while (is_in(s1[j], set))
		j--;
	k = j - i + 1;
	res = (char *)malloc(sizeof(char) * (k + 1));
	if (!res)
		return (0);
	k = i;
	i = 0;
	while (k <= j)
		res[i++] = s1[k++];
	res[i] = '\0';
	return (res);
}

static int	is_in(char ch, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (ch == set[i])
			return (1);
		i++;
	}
	return (0);
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
