/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:27:16 by seykim            #+#    #+#             */
/*   Updated: 2023/09/18 13:27:17 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

static t_bool	export_error(char *argv);
static void		export_excp(char **argv, int idx, t_list **env);

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
		export_excp(argv, idx, env);
	return (0);
}

static t_bool	export_error(char *argv)
{
	int	idx;

	idx = 1;
	if (argv[0] != '_' && !ft_isalpha(argv[0]))
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(argv, 2);
		ft_putendl_fd("': not a valid identifier", 1);
		return (FALSE);
	}
	while (argv[idx] && argv[idx] != '=')
	{
		if (!ft_isalnum(argv[idx]) && argv[idx] != '_')
		{
			ft_putstr_fd("export: '", 2);
			ft_putstr_fd(argv, 2);
			ft_putendl_fd("': not a valid identifier", 1);
			return (FALSE);
		}
		idx++;
	}
	return (TRUE);
}

static void	export_excp(char **argv, int idx, t_list **env)
{
	int		cnt;
	int		ret;
	char	*temp_str;

	cnt = 0;
	while (argv[++idx])
	{
		if (export_error(argv[idx]) == FALSE)
			continue ;
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
				ft_lstadd_back(env, ft_lstnew(ft_strdup(argv[idx])));
			cnt++;
		}
		if (ret == 0 && getenv_list(argv[idx], ft_strlen(argv[idx]), env) == 0)
			ft_lstadd_back(env, ft_lstnew(ft_strdup(argv[idx])));
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
