/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdg <sdg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:25:54 by naylee            #+#    #+#             */
/*   Updated: 2023/08/17 12:45:01 by sdg              ###   ########.fr       */
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
	{
		free(tokenizer.curr_token);
		// free_token(&tokenizer);
		return (NULL);
	}
	root = msh_grammar(&tokenizer);
	if (get_curr_token(&tokenizer)->type != E0F)
	{
		syntax_error(&tokenizer);
		free_tree(root);
		root = NULL;
	}
	free(tokenizer.curr_token);
	// free_token(&tokenizer);
	return (root);
}

void	free_tree(t_node *root)
{
	(void)root;
	return ;
}

void	syntax_error(t_tokenizer *tokenizer)
{
	t_token	*token;

	token = tokenizer->curr_token;
	ft_putstr_fd("minishell : ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
	ft_putchar_fd('\'', STDERR_FILENO);
	// @ 문법에러인경우, token내부의 str을 출력하는 이유는?
	// @ str에 에러메세지를 담는 token을 사용하지않으므로 필요없어 보임.
	ft_putstr_fd(token->str, STDERR_FILENO);
	ft_putchar_fd('\'', STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return ;
}

// int	main(void)
// {
// 	t_node	*test;
// 	int		a;

// 	test = parser("ls > a.txt");
// 	a = 3;
// 	a++;
// 	return (0);
// }