/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:42:49 by seykim            #+#    #+#             */
/*   Updated: 2023/09/04 19:03:04 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

t_bool	ft_export(char **argv)
{
	int		idx;
	t_list	**env;
	t_list	*temp;

	idx = 0;
	env = get_envp();
	temp = *env;
	if (!argv[1])
	{
		while (temp != NULL)
		{
			printf("declare -x %s\n", (char *)temp->content);
			temp = temp->next;
		}
	}
	else
	{
		export_excp(argv, idx, env);
	}
	return (0);
}

void	export_excp(char **argv, int idx, t_list **env)
{
	int		cnt;
	int		ret;
	char	*temp_str;

	cnt = 0;
	while (argv[++idx])
	{
		ret = check_argv(argv[idx]);
		if (ret == 2)
		{
			temp_str = ft_strjoin(argv[idx], "\"\"");
			free(argv[idx]);
			argv[idx] = temp_str;
		}
		if (!(ret == 0 && cnt > 0))
		{
			if (check_env(argv[idx], env) == 0)
			{
				ft_lstadd_back(env, ft_lstnew(ft_strdup(argv[idx])));
				cnt++;
			}
		}
	}
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
