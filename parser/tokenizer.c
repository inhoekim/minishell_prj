/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:29:30 by seykim            #+#    #+#             */
/*   Updated: 2023/09/18 13:29:31 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_token	*make_token(t_tokenizer *tokenizer, t_symbol type)
{
	tokenizer->curr_token->type = type;
	tokenizer->curr_token->len = tokenizer->end - tokenizer->start + 1;
	tokenizer->curr_token->str = tokenizer->start;
	tokenizer->end++;
	tokenizer->start = tokenizer->end;
	return (tokenizer->curr_token);
}

t_bool	match_token(t_symbol type, t_tokenizer *tokenizer, t_bool token_move)
{
	if (type == get_curr_token(tokenizer)->type)
	{
		if (token_move == TRUE)
			get_next_token(tokenizer);
		return (TRUE);
	}
	return (FALSE);
}

t_token	*get_curr_token(t_tokenizer *tokenizer)
{
	return (tokenizer->curr_token);
}

t_token	*get_next_token(t_tokenizer *tokenizer)
{
	tokenizer->token_size++;
	if (tokenizer->token_size == TOKEN_SIZE)
	{
		ft_putstr_fd("minishell : ", STDERR_FILENO);
		ft_putstr_fd("too many command\n", STDERR_FILENO);
		exit(1);
	}
	skip_whitespace(tokenizer);
	if (!tokenizer->end || !*tokenizer->end)
		return (make_token(tokenizer, E0F));
	if (*tokenizer->start == '(')
	{
		if (string_close(tokenizer, ')') == FALSE)
		{
			syntax_error(tokenizer);
		}
		return (make_token(tokenizer, SUBSHELL_LEFT));
	}
	if (*tokenizer->start == ')')
		return (make_token(tokenizer, SUBSHELL_RIGHT));
	return (scan_char_token(tokenizer));
}
