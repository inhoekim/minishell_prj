/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naylee <naylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:25:54 by naylee            #+#    #+#             */
/*   Updated: 2023/08/11 11:25:54 by naylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/tokenizer.h"
#include "../include/minishell.h"

t_node	*parser(char *line)
 {
	t_node		*root;
	t_tokenizer	tokenizer;

	set_tokenizer(&tokenizer, line);
	if (get_curr_token(&tokenizer)->type == E0F)
		return (NULL);
	root = msh_grammar(&tokenizer);
	if (get_curr_token(&tokenizer)->type != EOF)
	{
		syntex_error();
		free_tree(root);
	}
	return (root);
 }

