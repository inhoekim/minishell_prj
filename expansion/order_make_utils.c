/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_make_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:12:14 by seykim            #+#    #+#             */
/*   Updated: 2023/08/30 19:12:14 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"

static char		*make_arr(int start, int end, char *str);
static int		if_c(char c, char charset);
static int		chunk_size(char *str, char c);

char	**path_split(char *s, char c)
{
	char	**newstr;
	int		idx;
	int		num;
	int		start;

	idx = 0;
	newstr = (char **)malloc(sizeof(char *) * (chunk_size((char *)s, c) + 1));
	if (!newstr)
		exit(ENOMEM);
	num = 0;
	while (s[num] && idx < (chunk_size((char *)s, c)))
	{
		while (s[num] && if_c(s[num], c))
			num++;
		if (s[num] != 0)
			start = num;
		while (s[num] && (!(if_c(s[num], c))))
			num++;
		newstr[idx] = make_arr(start, num, (char *)s);
		idx++;
	}
	newstr[idx] = 0;
	return (newstr);
}

static int	chunk_size(char *str, char c)
{
	int	num;
	int	count;

	num = 0;
	count = 0;
	while (str[num])
	{
		while (str[num] && (if_c(str[num], c)))
			num++;
		if (str[num] != 0)
			count++;
		while (str[num] && (!if_c(str[num], c)))
			num++;
	}
	return (count);
}

static char	*make_arr(int start, int end, char *str)
{
	int		size;
	int		idx;
	char	*arr;

	size = end - start;
	idx = 0;
	arr = (char *)malloc(sizeof(char) * (size + 2));
	if (!arr)
		exit(ENOMEM);
	while (start < end)
	{
		arr[idx] = str[start];
		start++;
		idx++;
	}
	arr[idx++] = '/';
	arr[idx] = 0;
	return (arr);
}

static int	if_c(char c, char charset)
{
	if (c == charset)
		return (1);
	return (0);
}
