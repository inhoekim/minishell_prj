/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_word_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:12:01 by seykim            #+#    #+#             */
/*   Updated: 2023/08/30 19:12:02 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

t_list	*split_quotes(char *str)
{
	int		i;
	int		base;
	char	*not_quote_str;
	t_list	*head;

	i = 0;
	head = NULL;
	while (str[i])
	{
		if (str[i] == '"')
			ft_lstadd_back(&head, include_slice(str, &i, '"'));
		else if (str[i] == '\'')
			ft_lstadd_back(&head, include_slice(str, &i, '\''));
		else
		{
			base = i;
			while (str[i] && str[i] != '\'' && str[i] != '"')
				i++;
			not_quote_str = ft_substr(&str[base], 0, i - base);
			ft_lstadd_back(&head, ft_lstnew(not_quote_str));
			i--;
		}
		i++;
	}
	return (head);
}

t_list	*include_slice(char *str, int *i, char end)
{
	int	base;

	base = (*i)++;
	while (str[*i] != end)
		(*i)++;
	return (ft_lstnew(ft_substr(&str[base], 0, *i - base + 1)));
}

t_bool	check_glob(t_list *list)
{
	return (list_search(list, '*') || list_search(list, '?'));
}

t_bool	list_search(t_list *list, char ch)
{
	char	*content;
	t_bool	pattern;

	pattern = FALSE;
	while (list)
	{
		content = list->content;
		if (ft_strchr(content, ch))
		{
			if (!ft_strchr(content, '"') && !ft_strchr(content, '\''))
				pattern = TRUE;
		}
		list = list->next;
	}
	return (pattern);
}

void	unquote(t_list *list)
{
	char	*content;

	while (list)
	{
		content = list->content;
		if (content[0] == '"')
		{
			content = ft_strtrim(content, "\"");
			free(list->content);
			list->content = content;
		}
		else if (content[0] == '\'')
		{
			content = ft_strtrim(content, "'");
			free(list->content);
			list->content = content;
		}
		list = list->next;
	}
}
