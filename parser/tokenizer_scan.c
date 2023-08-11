#include "../include/tokenizer.h"
#define SYMBOLCHAR "<>&|() \t\n"

t_symbol	scan_char_token(t_tokenizer *tokenizer)
{
	if (*tokenizer->start == '<')	{
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

t_symbol	scan_word_token(t_tokenizer *tokenizer)
{
	if (*tokenizer->end == '\n')
		return (make_token(tokenizer, E0F));
	while (!ft_strchr(SYMBOLCHAR, *tokenizer->end))
	{
		if (*tokenizer->end == '\'' || *tokenizer->end == '"')
		{
			if (string_close(tokenizer, *tokenizer->end) == FALSE)
			{
				//syntax error 종료
				printf("!!!!!!!!!syntax error!!!!!!!!!!!\n");
			}
			else
				break;
		}
		tokenizer->end++;
	}
	return (make_token(tokenizer, WORD));
}

t_bool	string_close(t_tokenizer *tokenizer, char c)
{
	tokenizer->end++;
	while (*tokenizer->end != '\0' && *tokenizer->end != c)
		tokenizer->end++;
	if (*tokenizer->end == '\0' || *tokenizer->end != c)
		return (FALSE);
	return (TRUE);
}