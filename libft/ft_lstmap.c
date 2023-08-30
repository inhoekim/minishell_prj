/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasong <dasong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 04:08:38 by dasong            #+#    #+#             */
/*   Updated: 2023/03/18 05:56:14 by dasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new_node;
	t_list	*pre_node;

	head = 0;
	pre_node = 0;
	while (lst)
	{
		new_node = (t_list *)malloc(sizeof(t_list) * 1);
		if (!new_node)
		{
			if (head != 0)
				ft_lstclear(&head, del);
			return (0);
		}
		new_node->content = f(lst->content);
		new_node->next = 0;
		if (pre_node != 0)
			pre_node->next = new_node;
		else
			head = new_node;
		pre_node = new_node;
		lst = lst->next;
	}
	return (head);
}
