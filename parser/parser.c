/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdg <sdg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:25:54 by naylee            #+#    #+#             */
/*   Updated: 2023/08/15 22:59:55 by sdg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/rule.h"
#include "../include/tokenizer.h"
#include "../include/parser.h"

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

void	free_tree(t_node *root)
{
	(void)root;
	return ;
}

// int	main(int argc, char **argv)
// {
// 	t_node *test;
// 	test = parser("ls | ls >a | \"l\"s");
// 	int a = 3;
// 	a++;
// 	return (0);
// }
