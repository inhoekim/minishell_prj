/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rule2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhkim <inhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 07:46:14 by inhkim            #+#    #+#             */
/*   Updated: 2023/08/14 07:46:15 by inhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/grammar.h"

//command ::= simple_cmd
//command ::= ssh io_redirect_star
t_node	*command(t_tokenizer *tokenizer)
{
	t_node	*parent;
	t_node	*child;
	t_token	tk;

	tk = *(tokenizer->curr_token);
	if (check_first_set(SIMPLE_CMD, tk.type))
	{
		parent = simple_cmd(tokenizer);
		return (parent);
	}
	else if (match_token(SUBSHELL_LEFT, tokenizer, FALSE))
	{
		child = ssh(tokenizer);
		if (child)
		{
			parent = io_redirect_star(tokenizer);
			if (parent)
				return (merge_tree(parent, child));
		}
		return (child);
	}
	syntax_error(tokenizer);
	return (NULL);
}

//ssh ::= LBRACE msh_grammar RBRACE
t_node	*ssh(t_tokenizer *tokenizer)
{
	t_node	*parent;

	if (match_token(SUBSHELL_LEFT, tokenizer, TRUE))
	{
		parent = msh_grammar(tokenizer);
		if (match_token(SUBSHELL_RIGHT, tokenizer, TRUE))
			return (make_tree(SUBSHELL, parent, NULL));
	}
	syntax_error(tokenizer);
	return (NULL);
}

//simple_cmd ::= WORD io_redirect_or_word_star
//simple_cmd ::= io_redirect_dagger io_redirect_dg_after_simple_cmd
t_node	*simple_cmd(t_tokenizer *tokenizer)
{
	t_node	*parent;
	t_node	*child;
	t_token	tk;

	tk = *(tokenizer->curr_token);
	if (match_token(WORD, tokenizer, FALSE))
	{
		child = make_leaf(tokenizer);
		parent = io_redirect_or_word_star(tokenizer);
		if (child)
			return (merge_tree(parent, child));
		return (parent);
	}
	else if (check_first_set(IO_REDIRECT_DAGGER, tk.type))
	{
		parent = io_redirect_dagger(tokenizer);
		child = io_redirect_dg_after_simple_cmd(tokenizer);
		return (merge_tree(parent, child));
	}
	syntax_error(tokenizer);
	return (NULL);
}

//io_redirect_or_word_star ::= io_redirect io_redirect_or_word_star
//io_redirect_or_word_star ::= WORD io_redirect_or_word_star
//io_redirect_or_word_star ::= empty
t_node	*io_redirect_or_word_star(t_tokenizer *tokenizer)
{
	t_node	*parent;
	t_node	*child;
	t_token	tk;

	tk = *(tokenizer->curr_token);
	if (check_first_set(IO_REDIRECT, tk.type))
	{
		parent = io_redirect(tokenizer);
		child = io_redirect_or_word_star(tokenizer);
		return (merge_tree(parent, child));
	}
	else if (match_token(WORD, tokenizer, FALSE))
	{
		child = make_leaf(tokenizer);
		parent = io_redirect_or_word_star(tokenizer);
		return (merge_tree(parent, child));
	}
	return (NULL);
}

//io_redirect_dagger ::= io_redirect io_redirect_star
t_node	*io_redirect_dagger(t_tokenizer *tokenizer)
{
	t_node	*parent;
	t_node	*child;
	t_token	tk;

	tk = *(tokenizer->curr_token);
	if (check_first_set(IO_REDIRECT, tk.type))
	{
		parent = io_redirect(tokenizer);
		child = io_redirect_star(tokenizer);
		return (merge_tree(parent, child));
	}
	syntax_error(tokenizer);
	return (NULL);
}
