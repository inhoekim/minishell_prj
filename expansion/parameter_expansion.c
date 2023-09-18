/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:28:18 by seykim            #+#    #+#             */
/*   Updated: 2023/09/18 13:28:19 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"

static char	*str_replace(char *str, char *old, char *new);
static int	word_cnt(char *str, char *word);
static char	*get_value(char *key);

char	*parameter_expansion(char *str)
{
	char	*key;
	char	*value;
	char	*n_str;
	t_list	*list;
	t_list	*head;

	str = ft_strdup(str);
	n_str = str;
	head = make_key_list(str, 0);
	list = head;
	while (list)
	{
		key = list->content;
		value = get_value(key);
		n_str = str_replace(str, key, value);
		free(str);
		free(value);
		str = n_str;
		list = list->next;
	}
	ft_lstclear(&head, free);
	return (n_str);
}

static char	*str_replace(char *str, char *old, char *new)
{
	int		i;
	int		new_len;
	int		old_len;
	char	*res;

	old_len = ft_strlen(old);
	new_len = ft_strlen(new);
	res = malloc(ft_strlen(str) + \
			word_cnt(str, old) * (new_len - old_len) + 1);
	if (!res)
		exit(ENOMEM);
	i = 0;
	while (*str)
	{
		if (ft_strnstr(str, old, ft_strlen(str)) == str)
		{
			ft_strlcpy(&res[i], new, new_len + 1);
			i += new_len;
			str += old_len;
		}
		else
			res[i++] = *str++;
	}
	res[i] = '\0';
	return (res);
}

static int	word_cnt(char *str, char *word)
{
	int	i;
	int	cnt;
	int	len;

	i = 0;
	cnt = 0;
	len = ft_strlen(word);
	while (str[i])
	{
		if (ft_strnstr(&str[i], word, ft_strlen(&str[i])) == &str[i])
		{
			cnt++;
			i += len;
		}
		else
			i++;
	}
	return (cnt);
}

static char	*get_value(char *key)
{
	char	*value;

	if (key[1] == '?')
	{
		value = ft_itoa(*get_last_exit_status());
		return (value);
	}
	value = ft_getenv(&key[1]);
	if (!value)
		value = ft_strdup("");
	return (value);
}

t_list	*make_key_list(char *str, int i)
{
	int		base;
	t_list	*head;

	base = 0;
	head = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			base = i++;
			if (str[i] == '?')
				ft_lstadd_back(&head, ft_lstnew(ft_strdup("$?")));
			else if (ft_isalpha(str[i]) || str[i] == '_')
			{
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
					i++;
				ft_lstadd_back(&head, \
				ft_lstnew(ft_substr(str, base, i - base)));
			}
		}
		else
			i++;
	}
	return (head);
}
