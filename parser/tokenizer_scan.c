/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_scan.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:09:36 by naylee            #+#    #+#             */
/*   Updated: 2023/08/22 16:09:27 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tokenizer.h"
#include "../include/parser.h"
#define DELIMETER "<>&|() \t\n"

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
	while (!ft_strchr(DELIMETER, *tokenizer->end))
	{
		if (*tokenizer->end == '\0')
			return (make_token(tokenizer, E0F));
		if (*tokenizer->end == '\'' || *tokenizer->end == '"')
		{
			if (string_close(tokenizer, *tokenizer->end) == FALSE)
			{
				syntax_error(tokenizer);
				return (make_token(tokenizer, SYNTAX_ERR));
			}
		}
		tokenizer->end++;
	}
	// ex. ls & ls일 때, word token '&'는 tokenizer->start == tokenizer->end이므로 false
	// 나머지는 DELIMETER에 속할 경우 end를 왼쪽으로 한칸 밀어야 함.
	if (tokenizer->start != tokenizer->end \
		&& ft_strchr(DELIMETER, *tokenizer->end))
		tokenizer->end--;
	return (make_token(tokenizer, WORD));
}

t_bool	string_close(t_tokenizer *tokenizer, char c)
{
	char	*end_ptr;

	end_ptr = tokenizer->end + 1;
	while (*end_ptr != '\0' && *end_ptr != c)
		end_ptr++;
	if (*end_ptr == '\0')
		return (FALSE);
	if (c != ')')
		tokenizer->end = end_ptr++;
	return (TRUE);
}
