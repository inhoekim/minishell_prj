/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:42:49 by seykim            #+#    #+#             */
/*   Updated: 2023/08/16 14:56:05 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include "../include/execute.h"

t_bool	ft_export(char **argv)
{
	int		idx;
	t_list	**env;

	idx = -1;
	env = get_envp();
	if (!argv[1])
		while ((*env)->next != NULL)
			printf("declare -x %s\n", (char *)(*env)->content);
	else
	{
		env = get_envp();
		while (argv[++idx])
			ft_lstadd_back(env, ft_lstnew(ft_strdup(argv[idx])));
	}
	return (FALSE);
}

t_bool	ft_unset(char **argv)
{
	int		idx;
	t_list	**env;
	t_list	*check;

	idx = -1;
	if (argv[1])
	{
		env = get_envp();
		while (argv[++idx])
		{
			check = *env;
			while (check->next != NULL)
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
	return (FALSE);
}
