/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:42:49 by seykim            #+#    #+#             */
/*   Updated: 2023/08/09 17:43:23 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
# define PATH_MAX 1024

// 등록한 환경변수는 쉘이 종료됨에 따라 같이 환경변수에서 삭제되야함
t_bool	ft_export(t_node *node)
{
	char	**temp;
	int		idx;
	t_list	**env;

	temp = node->right->word;
	idx = -1;
	env = get_envp();
	if (!temp[1])
		while ((*env)->next != NULL)
			printf("declare -x %s\n", (*env)->content);
	else
	{
		env = get_envp();
		while (temp[++idx])
			ft_lstadd_back(env, ft_lstnew(ft_strdup(temp[idx])));
		ft_lstadd_back(env, ft_lstnew(NULL));
	}
	return (FALSE);
}

t_bool	ft_unset(t_node *node)
{
	char	**temp;
	int		idx;
	t_list	**env;
	t_list	*check;

	temp = node->right->word;
	idx = -1;
	if (temp[1])
	{
		env = get_envp();
		while (temp[++idx])
		{
			check = *env;
			while (check->next != NULL)
			{
				if (ft_memcmp(temp[idx], check->content, \
				ft_strlen(temp[idx])) == 0)
				{
					delete_node((*env), check);
					break ;
				}
				check = check->next;
			}
		}
	}
	return (FALSE);
}
