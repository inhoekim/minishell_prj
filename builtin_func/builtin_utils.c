/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:27:09 by seykim            #+#    #+#             */
/*   Updated: 2023/09/18 13:27:09 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

char	*ft_strnjoin(char const *s1, char const *s2)
{
	int		total;
	char	*res;
	int		i;

	if (!s1 || !s2)
		return (0);
	total = ft_strlen(s1) + ft_strlen(s2) + 2;
	res = (char *)malloc(sizeof(char) * total);
	if (!res)
		exit(ENOMEM);
	res[total - 1] = '\0';
	i = 0;
	while (*s1)
	{
		res[i] = *s1;
		s1++;
		i++;
	}
	res[i] = '=';
	while (*s2)
	{
		res[++i] = *s2;
		s2++;
	}
	return (res);
}

void	delete_node(t_list **head, t_list *node_to_delete)
{
	t_list	*current;
	t_list	*prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if (current == node_to_delete)
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			ft_lstdelone(current, free);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

char	*ft_getenv(char *pos)
{
	size_t	pos_len;
	t_list	*cur_env;
	char	*temp;

	pos_len = ft_strlen(pos);
	cur_env = getenv_list(pos, pos_len, get_envp());
	if (cur_env)
	{
		temp = ft_strdup((char *)cur_env->content + pos_len + 1);
		return (temp);
	}
	return (NULL);
}

t_list	*getenv_list(char *pos, size_t pos_len, t_list **env)
{
	t_list	*temp;
	char	*var;

	temp = *env;
	while (temp != NULL)
	{
		var = temp->content;
		if (ft_strncmp(var, pos, pos_len) == 0)
		{
			if (var[pos_len] == '=')
				return (temp);
		}
		temp = temp->next;
	}
	return (NULL);
}

void	set_envp(char *pos, char *pwd)
{
	t_list	*temp;
	size_t	pos_len;
	char	*newpwd;

	if (!pwd)
		return ;
	pos_len = ft_strlen(pos);
	temp = getenv_list(pos, pos_len, get_envp());
	if (!temp)
	{
		newpwd = ft_strnjoin(pos, pwd);
		ft_lstadd_back(get_envp(), ft_lstnew(ft_strdup(newpwd)));
		free(newpwd);
	}
	else
	{
		newpwd = ft_strnjoin(pos, pwd);
		free(temp->content);
		temp->content = ft_strdup(newpwd);
		free(newpwd);
	}
}
