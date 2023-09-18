/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:27:19 by seykim            #+#    #+#             */
/*   Updated: 2023/09/18 13:27:20 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

int	check_argv(char *argv)
{
	int		idx;

	idx = 0;
	while (argv[idx])
	{
		if (argv[idx] == '=')
		{
			if (argv[idx + 1] != 0)
			{
				if (!ft_strncmp(&argv[idx + 1], "\"\"", 3))
					return (3);
				return (1);
			}
			else
				return (2);
		}
		idx++;
	}
	return (0);
}

int	check_env(char *argv, t_list **env)
{
	t_list	*check;
	char	*temp;

	check = *env;
	if (argv)
	{
		check = *env;
		temp = make_temp(argv);
		if (!temp)
			return (1);
		while (check)
		{
			if (!ft_memcmp(temp, check->content, ft_strlen(temp)))
			{
				delete_node(env, check);
				break ;
			}
			check = check->next;
		}
		free(temp);
	}
	return (0);
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
