/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:25:54 by naylee            #+#    #+#             */
/*   Updated: 2023/08/22 16:09:12 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/rule.h"
#include "../include/tokenizer.h"
#include "../include/parser.h"
#include "../include/filename_expansion.h"
#include "../include/here_doc.h"

t_node	*parser(char *line)
{
	t_node		*root;
	t_tokenizer	tokenizer;

	set_heredoc_exit_flag(0);
	set_tokenizer(&tokenizer, line);
	if (get_curr_token(&tokenizer)->type == E0F)
	{
		free_tokenizer(&tokenizer);
		return (NULL);
	}
	root = msh_grammar(&tokenizer);
	if (get_curr_token(&tokenizer)->type != E0F)
	{
		syntax_error(&tokenizer);
		free_tree(root);
		root = NULL;
	}
	else if (*get_heredoc_exit_flag() == 1)
	{
		free_tree(root);
		root = NULL;
	}
	free_tokenizer(&tokenizer);
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
	if (token->type != SYNTAX_ERR)
	{	
		ft_putstr_fd("minishell : ", STDERR_FILENO);
		ft_putstr_fd("syntax error: near unexpected ", STDERR_FILENO);
		if (token->type == E0F)
			ft_putstr_fd("end of file", STDERR_FILENO);
		else
		{
			ft_putstr_fd("token ", STDERR_FILENO);
			ft_putchar_fd('\'', STDERR_FILENO);
			ft_putstr_fd(token->str, STDERR_FILENO);
			ft_putchar_fd('\'', STDERR_FILENO);
		}
		ft_putchar_fd('\n', STDERR_FILENO);
		tokenizer->curr_token->type = SYNTAX_ERR;
	}
	return ;
}

void	free_tokenizer(t_tokenizer *tokenizer)
{
	int	i;

	free(tokenizer->curr_token);
	i = 0;
	while (i < tokenizer->heredoc_file_idx)
		free(tokenizer->heredoc_file_name[i++]);
	free(tokenizer->heredoc_file_name);
}