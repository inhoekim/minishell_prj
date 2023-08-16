/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhkim <inhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:25:54 by naylee            #+#    #+#             */
/*   Updated: 2023/08/15 17:45:35 by inhkim           ###   ########.fr       */
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
	{
		free_token(&tokenizer);
		return (NULL);
	}
	root = msh_grammar(&tokenizer);
	if (get_curr_token(&tokenizer)->type != E0F)
	{
		free_token(&tokenizer);
		syntax_error("error");
		//free_tree(root);
	}
	free_token(&tokenizer);
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

// static void	test_exit()
// {
// 	system("leaks --list -- parser_test");
// }

int	main(int argc, char **argv)
{
	// atexit(test_exit);
	t_node *test;
	test = parser("s");
	int a = 3;
	a++;
	return (0);
}
