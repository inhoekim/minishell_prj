/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rule1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 07:46:07 by inhkim            #+#    #+#             */
/*   Updated: 2023/08/16 19:10:15 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/tokenizer.h"
#include "../include/rule.h"
#include "../include/parser.h"

//msh_grammar ::= pipeline conditional
t_node	*msh_grammar(t_tokenizer *tokenizer)
{
	t_node	*parent;
	t_node	*child;
	t_token	tk;

	tk = *(tokenizer->curr_token);
	if (check_first_set(PIPELINE, tk.type) || \
	match_token(SUBSHELL_LEFT, tokenizer, FALSE))
	{
		child = pipeline(tokenizer);
		if (child)
		{
			parent = conditional(tokenizer);
			if (parent)
				return (merge_tree(parent, child));
		}
		return (child);
	}
	syntax_error(tokenizer);
	return (NULL);
}

//conditional ::= AND pipeline conditional
//conditional ::= OR pipeline conditional
//conditional ::= empty
t_node	*conditional(t_tokenizer *tokenizer)
{
	t_node	*pipe;
	t_node	*parent;
	t_node	*child;

	if (match_token(AND_IF, tokenizer, TRUE))
	{
		pipe = pipeline(tokenizer);
		parent = conditional(tokenizer);
		child = make_tree(AND_IF, NULL, pipe);
		return (merge_tree(parent, child));
	}
	else if (match_token(OR_IF, tokenizer, TRUE))
	{
		pipe = pipeline(tokenizer);
		parent = conditional(tokenizer);
		child = make_tree(OR_IF, NULL, pipe);
		return (merge_tree(parent, child));
	}
	return (NULL);
}

//pipeline ::= command piped_command
t_node	*pipeline(t_tokenizer *tokenizer)
{
	t_node	*parent;
	t_node	*child;
	t_token	tk;

	tk = *(tokenizer->curr_token);
	if (check_first_set(COMMAND, tk.type) || \
	match_token(SUBSHELL_LEFT, tokenizer, FALSE))
	{
		child = command(tokenizer);
		if (child)
		{
			parent = piped_command(tokenizer);
			if (parent)
				return (merge_tree(parent, child));
		}
		return (child);
	}
	syntax_error(tokenizer);
	return (NULL);
}

//piped_command ::= PIPE pipeline
//piped_command ::= empty
t_node	*piped_command(t_tokenizer *tokenizer)
{
	t_node	*child;

	if (match_token(PIPE, tokenizer, TRUE))
	{
		child = pipeline(tokenizer);
		return (make_tree(PIPE, NULL, child));
	}
	return (NULL);
}
