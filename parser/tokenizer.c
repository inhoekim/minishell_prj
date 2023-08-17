/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdg <sdg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:26:07 by naylee            #+#    #+#             */
/*   Updated: 2023/08/17 12:44:00 by sdg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/tokenizer.h"

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
	// reset_start_ptr(tokenizer);
	skip_whitespace(tokenizer);
	if (!tokenizer->end || !*tokenizer->end)
		return (make_token(tokenizer, E0F));
	if (*tokenizer->start == '(')
	{
		if (string_close(tokenizer, ')') == FALSE)
		{
			//syntax_error("");
		}
		return (make_token(tokenizer, SUBSHELL_LEFT));
	}
	if (*tokenizer->start == ')')
		return (make_token(tokenizer, SUBSHELL_RIGHT));
	return (scan_char_token(tokenizer));
}

t_token	*make_token(t_tokenizer *tokenizer, t_symbol type)
{
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

t_token	*make_merge_word_token(t_tokenizer *tokenizer, int flag)
{
	char	*ptr;
	char	*str;
	int		len;
	int		i;

	len = tokenizer->end - tokenizer->start - (flag * 2) + 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	ptr = tokenizer->start;
	i = 0;
	while (ptr <= tokenizer->end)
	{
		if (*ptr != '\'' && *ptr != '"')
		{
			str[i] = *ptr;
			i++;
		}
		ptr++;
	}
	tokenizer->curr_token->type = WORD;
	tokenizer->curr_token->len = len;
	tokenizer->curr_token->str = str;
	return (tokenizer->curr_token);
}
