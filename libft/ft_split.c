/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasong <dasong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 23:04:14 by dasong            #+#    #+#             */
/*   Updated: 2023/03/18 05:47:05 by dasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	allocate_str(char **res, char const *s, char c, int i);
static int	memore_release(char **res, int k);

char	**ft_split(char const *s, char c)
{
	int		word_cnt;
	int		i;
	char	**res;

	word_cnt = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
				i++;
			word_cnt++;
		}
		else
			i++;
	}
	res = (char **)malloc(sizeof(char *) * (word_cnt + 1));
	if (!res)
		return (0);
	res[word_cnt] = 0;
	if (!(allocate_str(res, s, c, 0)))
		return (0);
	return (res);
}

static int	allocate_str(char **res, char const *s, char c, int i)
{
	int	j;
	int	k;
	int	m;

	k = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j = 0;
			while (s[i + j] != c && s[i + j])
				j++;
			res[k] = malloc(sizeof(char) * (j + 1));
			if (!res[k])
				if (memore_release(res, k))
					return (0);
			m = 0;
			while (m < j)
				res[k][m++] = s[i++];
			res[k++][m] = '\0';
		}
		else
			i++;
	}
	return (1);
}

static int	memore_release(char **res, int k)
{
	int	m;

	m = 0;
	while (m < k)
		free(res[m++]);
	free(res);
	return (1);
}
