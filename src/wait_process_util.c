/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_process_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:13:18 by seykim            #+#    #+#             */
/*   Updated: 2023/08/30 19:13:19 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	*get_last_pid(void)
{
	static int	last_pid;

	return (&last_pid);
}

void	set_last_pid(int pid)
{
	*get_last_pid() = pid;
}

int	*get_last_exit_status(void)
{
	static int	last_exit_status;

	return (&last_exit_status);
}

void	set_last_exit_status(int exit_status)
{
	*get_last_exit_status() = exit_status;
}

t_list	*_delete_process(t_list **head, t_list *d_node)
{
	t_list	*prev;
	t_list	*current;

	prev = *head;
	current = (*head)->next;
	while (current != d_node)
	{
		prev = current;
		current = current->next;
	}
	if (current == *head && prev == *head)
	{
		ft_lstdelone(d_node, free);
		return (NULL);
	}
	else if (current == *head)
	{
		*head = current->next;
		prev->next = *head;
	}
	else
		prev->next = current->next;
	ft_lstdelone(current, free);
	return (prev);
}
