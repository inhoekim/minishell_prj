#include "tokenizer.h"

#define SYMBOLCHAR "<>&|() \t\n"

// t_node	*parse(t_tokenizer *token)
// {
// 	t_node	*root;

// 	if (EOF)
// 	{
// 		//종료
// 		return (NULL);
// 	}
// 	root = msh_grammer(token); //생성규칙 따라 트리 생성
// 	if (token != EOF)
// 	{
// 		//syntax error
// 		//free root
// 		//종료
// 		return (NULL);
// 	}
// 	return (root);
// }

t_tokenizer	get_next_token(char *line)
{
	t_tokenizer	token;
	char		*start;

	start = skip_whitespace(line);
	token.current_token = start + 1;
	token.token_size = 0;
	token.type = E0F;

	if (*start == EOF)
	{
		//종료
	}
	if (*start == '(')
	{
		while (*token.current_token != ')' || token.current_token)
			token.current_token++;
		if (match(&token, ')'))
			return (make_token(start, &token, SUBSHELL));
	}
	return (scan_char_token(start, &token));
}

t_tokenizer	scan_char_token(char *start, t_tokenizer *token)
{
	if (*start == '<')
	{
		if (match(token, '<'))
			return (make_token(start, token, DLESS));
		return (make_token(start, token, LESS));
	}
	if (*start == '>')
	{
		if (match(token, '>'))
			return (make_token(start, token, DGREAT));
		return (make_token(start, token, GREAT));
	}
	if (*start == '&')
	{
		if (match(token, '&'))
			return (make_token(start, token, AND_IF));
	}
	if (*start == '|')
	{
		if (match(token, '|'))
			return (make_token(start, token, OR_IF));
		return (make_token(start, token, PIPE));
	}
	return (make_token(start, token, EOF));
}

// t_tokenizer	scan_word_token(char *start, t_tokenizer *token)
// {
// 	while (!ft_strchr(SYMBOLCHAR, token->current_token))
// 	{
// 		if (start == '\'' || start == '"' || start == '/')
// 		{
// 			if (string_close(token, start) == FALSE)
// 			{
// 				//뭔가 동작함
// 			}
			
// 		}
// 		token->current_token++;
// 	}
// 	return (make_token(start, token, WORD));
// }

t_tokenizer	make_token(char *start, t_tokenizer *token, t_symbol type)
{
	token->type = type;
	token->token_size = token->current_token - start;
	token->current_token = start;
	return (*token);
}
