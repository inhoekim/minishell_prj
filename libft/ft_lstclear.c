/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasong <dasong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 04:07:59 by dasong            #+#    #+#             */
/*   Updated: 2023/03/18 04:50:22 by dasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cur;
	t_list	*tmp_node;

	cur = lst[0];
	while (cur)
	{
		tmp_node = cur;
		del(cur->content);
		cur = cur->next;
		free(tmp_node);
	}
	*lst = 0;
}
