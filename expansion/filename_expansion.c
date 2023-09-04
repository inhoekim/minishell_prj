/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:12:12 by seykim            #+#    #+#             */
/*   Updated: 2023/08/30 19:12:13 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"

static t_list	*globbing(char *pattern);
static void		dir_search(char *pattern, t_list **matches, int *p_file_cnt);

t_list	*filename_expansion(t_list *list, t_bool glob_flag)
{
	t_list	*expanded_list;
	char	*pattern;

	pattern = concatenate(list);
	if (!pattern)
		exit(ENOMEM);
	if (glob_flag)
	{
		expanded_list = globbing(pattern);
		if (expanded_list)
		{
			free(pattern);
			return (expanded_list);
		}
	}
	return (ft_lstnew(pattern));
}

char	*concatenate(t_list *list)
{
	int		str_size;
	char	*content;
	char	*pattern;
	t_list	*head;

	head = list;
	str_size = 0;
	while (list)
	{
		str_size += ft_strlen(list->content);
		list = list->next;
	}
	pattern = ft_calloc(str_size + 1, sizeof(char));
	if (!pattern)
		return (NULL);
	list = head;
	while (list)
	{
		content = list->content;
		ft_strlcat(pattern, content, str_size + 1);
		list = list->next;
	}
	return (pattern);
}

static t_list	*globbing(char *pattern)
{
	t_list			*matches;
	int				file_cnt;

	file_cnt = 0;
	matches = NULL;
	dir_search(pattern, &matches, &file_cnt);
	if (*get_redirect_ambiguity() == TRUE && file_cnt > 1)
	{
		printf("minishell: %s: ambiguous redirect\n", pattern);
		set_redirect_ambiguity(FALSE);
		ft_lstclear(&matches, free);
		return (NULL);
	}
	else
		return (matches);
}

static void	dir_search(char *pattern, t_list **matches, int *p_file_cnt)
{
	char			dirbuf[PATH_MAX];
	DIR				*dp;
	struct dirent	*dir;

	getcwd(dirbuf, PATH_MAX);
	dp = opendir(dirbuf);
	dir = readdir(dp);
	while (dir != NULL)
	{
		dir = readdir(dp);
		if (dir && dir->d_name[0] == '.')
			dir->d_type = DT_UNKNOWN;
		if (dir && (dir->d_type == DT_REG || dir->d_type == DT_DIR) \
			&& wildcard(pattern, dir->d_name, 0, 0))
		{
			ft_lstadd_back(matches, ft_lstnew(ft_strdup(dir->d_name)));
			(*p_file_cnt)++;
		}
	}
	closedir(dp);
	return ;
}
