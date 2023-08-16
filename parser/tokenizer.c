/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdg <sdg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:26:07 by naylee            #+#    #+#             */
/*   Updated: 2023/08/16 22:10:35 by sdg              ###   ########.fr       */
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
	reset_start_ptr(tokenizer);
	// line end check용도? 이게 더 간단해보임.
	// if(!*tokenizer->end)
	if (!tokenizer->end || !ft_strlen(tokenizer->end))
		return (make_token(tokenizer, E0F));
	if (*tokenizer->start == '(')
	{
		if (string_close(tokenizer, ')') == FALSE)
		{
			//syntax_error("");
		}
		// @ '(' 토큰 만드는 이유?
		return (make_token(tokenizer, SUBSHELL_LEFT));
	}
	if (*tokenizer->end == ')')
		// @ ')' 토큰 만드는 이유?
		return (make_token(tokenizer, SUBSHELL_RIGHT));
	return (scan_char_token(tokenizer));
}

t_token	*make_token(t_tokenizer *tokenizer, t_symbol type)
{
	tokenizer->curr_token->type = type;
	if (type == E0F)
	{
		tokenizer->curr_token->len = 0;
		tokenizer->curr_token->str = "";
	}
	else
	{
		// @ + 1이면 폐구간 길이인가? "<<"의 start: 0, end: 2라면 +1하면 안됨.
		tokenizer->curr_token->len = tokenizer->end - tokenizer->start + 1;
		// @ parsing중에 스택변수 line은 free되지않음. 그러니까 str에는 주소만 있으면 될 것같음.
		tokenizer->curr_token->str = ft_substr(tokenizer->start, 0, tokenizer->curr_token->len);
	}
	// @ tokenizer->start갱신해줘야 함.
	// tokenizer->start = tokenizer->end;
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
