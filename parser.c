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


// init_tokenizer(char* line)  ==> t_tokenizer를 만든다.
// curr_token_start_ptr, curr_token_end_ptr 이 ls를 가리키고있다

// get_next_token() ==> t_tokenizer를 갱신한다.
// 갱신되면 t_tokenizer는 다른 토큰(문자열)을 가리키게 된다


t_tokenizer	get_next_token(t_tokenizer &tokenizer)
{
	t_tokenizer	token;
	char		*start;

	get_next_token() -> 원래 예전에 만들어놨던 t_tokenizer를 갱신.

	ls << cat
	start = skip_whitespace(line);
	// if (*start == NULL)
	// {
	// 	//종료asd
	// }
	token.current_token = start + 1;
	token.token_size = 0;
	token.type = E0F;
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
	if (*start == '<')	{
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
// 			if (sring_close(token, start) == FALSE)
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
	token->token_size += token->current_token - start;
	token->current_token = start;
	return (*token);
}
