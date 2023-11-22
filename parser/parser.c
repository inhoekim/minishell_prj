/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:29:22 by seykim            #+#    #+#             */
/*   Updated: 2023/09/18 13:29:23 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_node	*parser(char *line)
{
	t_node		*root;
	t_tokenizer	tokenizer;

	set_tokenizer(&tokenizer, line);
	if (get_curr_token(&tokenizer)->type == E0F)
	{
		free_tokenizer(&tokenizer);
		return (NULL);
	}
	root = msh_grammar(&tokenizer);
	if (get_heredoc_data()->heredoc_fault_flag == TRUE)
	{
		free_tree(root);
		root = NULL;
	}
	else if (get_curr_token(&tokenizer)->type != E0F)
	{
		syntax_error(&tokenizer);
		free_tree(root);
		root = NULL;
	}
	free_tokenizer(&tokenizer);
	return (root);
}

void	syntax_error(t_tokenizer *tokenizer)
{
	t_token	*token;

	set_last_exit_status(1);
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
	while (i < 16)
		free(tokenizer->heredoc_file_name[i++]);
	free(tokenizer->heredoc_file_name);
}

// first_set() Details
/* It checks which terminal character 
the first letter of the nonterminal function results in */
/*	set[10] =
	{WORD, LESS, GREAT, DGREAT, DLESS, AND_IF, OR_IF, PIPE, SUBSHELL_LEFT, E0F}
*/
t_bool	check_first_set(t_nonterminal idx, t_symbol curr_token)
{
	static int	table[8][10] = {
	[PIPELINE] = {WORD, LESS, GREAT, DGREAT, DLESS, \
	NONE, NONE, NONE, SUBSHELL_LEFT, NONE},
	[SIMPLE_CMD] = {WORD, LESS, GREAT, DGREAT, DLESS, \
	NONE, NONE, NONE, NONE, NONE},
	[IO_REDIRECT] = {NONE, LESS, GREAT, DGREAT, DLESS, \
	NONE, NONE, NONE, NONE, NONE},
	[CONDITIONAL] = {NONE, NONE, NONE, NONE, NONE, \
	AND_IF, OR_IF, NONE, NONE, NONE},
	[PIPED_COMMAND] = {NONE, NONE, NONE, NONE, NONE, \
	NONE, NONE, PIPE, NONE, NONE},
	[IO_REDIRECT_DG_AFTER_SIMPLE_CMD] = {WORD, NONE, NONE, \
	NONE, NONE, NONE, NONE, NONE, NONE, NONE},
	[IO_FILE] = {NONE, LESS, GREAT, DGREAT, NONE, NONE, NONE, NONE, NONE, NONE},
	[IO_HERE] = {NONE, NONE, NONE, NONE, DLESS, NONE, NONE, NONE, NONE, NONE},
	};

	if (table[idx][curr_token] != NONE)
		return (TRUE);
	else
		return (FALSE);
}
