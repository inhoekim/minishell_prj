/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhkim <inhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:25:54 by naylee            #+#    #+#             */
/*   Updated: 2023/08/16 12:19:52 by inhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/rule.h"
#include "../include/tokenizer.h"
#define STDERR_FD 2

t_node	*parser(char *line)
{
	t_node		*root;
	t_tokenizer	tokenizer;

	set_tokenizer(&tokenizer, line);
	if (get_curr_token(&tokenizer)->type == E0F)
	{
		//free_token(&tokenizer);
		return (NULL);
	}
	root = msh_grammar(&tokenizer);
	if (get_curr_token(&tokenizer)->type != E0F)
	{
		syntax_error(&tokenizer);
		free_tree(root);
		root = NULL;
	}
	free_token(&tokenizer);
	return (root);
}

void	syntax_error(t_tokenizer *tokenizer)
{
	t_token	*token;

	token = tokenizer->curr_token;
	ft_putstr_fd("minishell : ", STDERR_FD);
	ft_putstr_fd("syntax error near unexpected token ", STDERR_FD);
	ft_putchar_fd('\'', STDERR_FD);
	ft_putstr_fd(token->str, STDERR_FD);
	ft_putchar_fd('\'', STDERR_FD);
	ft_putchar_fd("\n", STDERR_FD);
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
	t_node	*test;
	test = parser("ls | ls >a | \"l\"s");
	int a = 3;
	a++;
	return (0);
}
