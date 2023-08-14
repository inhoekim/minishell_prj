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
#include "../include/rule.h"

t_node	*parser(char *line)
 {
	t_node 		*root;
	t_tokenizer	tokenizer;

	set_tokenizer(&tokenizer, line);
	if (get_curr_token(&tokenizer)->type == E0F)
		return (NULL);
	root = msh_grammar(&tokenizer);
	if (get_curr_token(&tokenizer)->type != E0F)
	{
		syntax_error("error");
		//free_tree(root);
	}
	free(tokenizer.curr_token);
	return (root);
 }

void	syntax_error(char * str)
{
	return ;
}

void	free_tree(t_node *root)
{
	return ;
}

int	main(void)
{
	parser("echo 1234 > a.txt");
}