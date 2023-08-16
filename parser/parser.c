/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhkim <inhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:25:54 by naylee            #+#    #+#             */
/*   Updated: 2023/08/16 12:40:48 by inhkim           ###   ########.fr       */
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
	ft_putstr_fd("minishell : syntax error near unexpected token ", STDERR_FILENO);
	ft_putchar_fd('\'', STDERR_FILENO);
	if (token->type == E0F)
		ft_putstr_fd("newline", STDERR_FD);
	else
		ft_putstr_fd(token->str, STDERR_FD);
	ft_putchar_fd('\'', STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	set_exit_status(STDERR_FILENO);
}

void	free_tree(t_node *root)
{
	(void)root;
	return ;
}

// int	main(int argc, char **argv)
// {
// 	//atexit(test_exit);
// 	t_node *test;
// 	test = parser("cat | >");
// 	int a = 3;
// 	a++;
// 	return (0);
// }


