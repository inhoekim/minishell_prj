/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhkim <inhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:25:54 by naylee            #+#    #+#             */
/*   Updated: 2023/08/15 17:18:22 by inhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/rule.h"
#include "../include/tokenizer.h"

t_node	*parser(char *line)
 {
	t_node		*root;
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
	free(tokenizer.curr_token->str);
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
	t_node *test;
	test = parser("echo \"1234 1234\"'ok' 1234 > b.txt");
	int a = 3;
	a++;
	return (0);
}
