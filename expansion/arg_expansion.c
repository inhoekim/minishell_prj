/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:27:49 by seykim            #+#    #+#             */
/*   Updated: 2023/09/18 13:27:50 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expansion.h"

void	arg_expansion(t_list *list)
{
	char	*content;

	while (list)
	{
		content = list->content;
		if (content[0] != '\'')
		{
			content = parameter_expansion(list->content);
			free(list->content);
			list->content = content;
		}
		list = list->next;
	}
}
