/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdg <sdg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:42:49 by seykim            #+#    #+#             */
/*   Updated: 2023/08/15 22:57:24 by sdg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include "../include/execute.h"

t_bool	ft_export(t_node *node)
{
	char	**temp;
	int		idx;
	t_list	**env;

	temp = node->left->word;
	idx = -1;
	env = get_envp();
	if (!temp[1])
		while ((*env)->next != NULL)
			printf("declare -x %s\n", (char *)(*env)->content);
	else
	{
		env = get_envp();
		while (temp[++idx])
			ft_lstadd_back(env, ft_lstnew(ft_strdup(temp[idx])));
	}
	return (FALSE);
}

t_bool	ft_unset(t_node *node)
{
	char	**temp;
	int		idx;
	t_list	**env;
	t_list	*check;

	temp = node->left->word;
	idx = -1;
	if (temp[1])
	{
		env = get_envp();
		while (temp[++idx])
		{
			check = *env;
			while (check->next != NULL)
			{
				if (!ft_memcmp(temp[idx], check->content, ft_strlen(temp[idx])))
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
