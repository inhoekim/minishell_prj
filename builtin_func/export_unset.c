/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:42:49 by seykim            #+#    #+#             */
/*   Updated: 2023/08/22 13:33:06 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include "../include/execute.h"
#include "../include/exec_node_util.h"

t_bool	ft_export(char **argv)
{
	int		idx;
	t_list	**env;

	idx = 0;
	env = get_envp();
	if (!argv[1])
	{
		while ((*env)->next != NULL)
		{
			printf("declare -x %s\n", (char *)(*env)->content);
			env = &(*env)->next;
		}
	}
	else
	{
		env = get_envp();
		check_env(argv, env);
		while (argv[++idx])
			ft_lstadd_back(env, ft_lstnew(ft_strdup(argv[idx])));
	}
	return (0);
}

void	check_env(char **argv, t_list **env)
{
	t_list	*check;
	int		idx;
	char	*temp;

	env = get_envp();
	idx = 0;
	check = *env;
	while (argv[++idx])
	{
		check = *env;
		temp = make_temp(argv[idx]);
		while (check)
		{
			if (!ft_memcmp(temp, check->content, ft_strlen(temp)))
			{
				delete_node(env, check);
				break ;
			}
			check = check->next;
		}
	}
	free(temp);
}

char	*make_temp(char *s1)
{
	int		idx;
	char	*temp;

	idx = 0;
	temp = 0;
	if (!s1)
		return (0);
	while (s1[idx])
	{
		if (s1[idx] == '=')
		{
			temp = ft_substr(s1, 0, idx);
			break ;
		}
		idx++;
	}
	return (temp);
}

t_bool	ft_unset(char **argv)
{
	int		idx;
	t_list	**env;
	t_list	*check;

	idx = 0;
	if (argv[1])
	{
		env = get_envp();
		while (argv[++idx])
		{
			check = *env;
			while (check)
			{
				if (!ft_memcmp(argv[idx], check->content, ft_strlen(argv[idx])))
				{
					delete_node(env, check);
					break ;
				}
				check = check->next;
			}
		}
	}
	return (0);
}
