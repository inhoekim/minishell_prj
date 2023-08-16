/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_scan.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdg <sdg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:09:36 by naylee            #+#    #+#             */
/*   Updated: 2023/08/16 21:17:01 by sdg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tokenizer.h"
#define SYMBOLCHAR "<>&|() \t\n"

t_token	*scan_char_token(t_tokenizer *tokenizer)
{
	if (*tokenizer->start == '<')
	{
		if (match(tokenizer, '<'))
			return (make_token(tokenizer, DLESS));
		return (make_token(tokenizer, LESS));
	}
	if (*tokenizer->start == '>')
	{
		if (match(tokenizer, '>'))
			return (make_token(tokenizer, DGREAT));
		return (make_token(tokenizer, GREAT));
	}
	if (*tokenizer->start == '&')
	{
		if (match(tokenizer, '&'))
			return (make_token(tokenizer, AND_IF));
	}
	if (*tokenizer->start == '|')
	{
		if (match(tokenizer, '|'))
			return (make_token(tokenizer, OR_IF));
		return (make_token(tokenizer, PIPE));
	}
	return (scan_word_token(tokenizer));
}

t_token	*scan_word_token(t_tokenizer *tokenizer)
{
	while (!ft_strchr(SYMBOLCHAR, *tokenizer->end))
	{
		if (*tokenizer->end == '\0')
			return (make_token(tokenizer, E0F));
		if (*tokenizer->end == '\'' || *tokenizer->end == '"')
		{
			if (string_close(tokenizer, *tokenizer->end) == FALSE)
			{
				//syntax_error
			}
			else
			{
				while (*tokenizer->end != '\'' && *tokenizer->end != '"')
					tokenizer->end++;
			}
		}
		tokenizer->end++;
	}
	// @ start와 end가 다른 이유를 고려하는 이유가 ''나 ""의 매칭이 달라질경우, end가 quotation을 가리키도록 하기 위함인가?
	if (tokenizer->start != tokenizer->end && ft_strchr(SYMBOLCHAR, *tokenizer->end))
		tokenizer->end--;
	return (make_token(tokenizer, WORD));
}

t_bool	string_close(t_tokenizer *tokenizer, char c)
{
	char	*end_ptr;

	end_ptr = tokenizer->end + 1;
	while (*end_ptr != '\0' && *end_ptr != c)
		end_ptr++;
	// @c는 ( or ) 이므로 *end_ptr == '\0'로도 충분.
	// if  (*end_ptr == '\0')
	if (*end_ptr == '\0' || *end_ptr != c)
		return (FALSE);
	if (c != ')')
		tokenizer->end = end_ptr;
	return (TRUE);
}
