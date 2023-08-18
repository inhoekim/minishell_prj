/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdg <sdg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:26:07 by naylee            #+#    #+#             */
/*   Updated: 2023/08/17 18:26:20 by sdg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/tokenizer.h"
#include "../include/parser.h"

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

t_token	*make_token(t_tokenizer *tokenizer, t_symbol type)
{
	if (tokenizer->curr_token->type != SYNTAX_ERR)
		tokenizer->curr_token->type = type;
	// @ grammar부분에서 free할 때 문제없으면 
	// @ if (type == E0F)블록 삭제
	if (type == E0F)
	{
		// tokenizer->curr_token->len = 0;
		// tokenizer->curr_token->str = "";
	}
	else
	{
		tokenizer->curr_token->len = tokenizer->end - tokenizer->start + 1;
		// @ grammar부분에서 free할 때 문제없으면 
		// @ tokenizer->curr_token->str = tokenizer->start; 로 바꿔도 됨.
		tokenizer->curr_token->str = ft_substr(tokenizer->start, 0, tokenizer->curr_token->len);
	}
	tokenizer->end++;
	tokenizer->start = tokenizer->end;
	return (tokenizer->curr_token);
}
