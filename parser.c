#include "minishell.h"

t_node	*parse(t_tokenizer *token)
{
	t_node	*root;

	if (EOF)
	{
		//종료
		return (NULL);
	}
	root = msh_grammer(token); //생성규칙 따라 트리 생성
	if (token != EOF)
	{
		//syntax error
		//free root
		//종료
		return (NULL);
	}
	return (root);
}

#include "minishell.h";

t_tokenizer	get_next_token(char *line)
{
	t_tokenizer token;
	
	token.type = E0F;
	token.current_token = line;
	token.token_size = 0;

    skip_whitespace();
	char c = 포인터 하나;
    if (c == EOF)
	{
		//종료
	}
	if (c == '(')
	{
		make_token
	}
	if (c == ')')
	{

	}
}

t_tokenizer	scan_char_token(t_tokenizer token, char c)
{
	if (c == '<')
	{
		if (match 함수 -> 다음 글자가 '<'일 때)
			return (make_token(c, c + 1, DLESS))
		return(make_token((c, c, LESS));
	}
	if (c == '>')
	{
		if (match 함수 -> 다음 글자가 '>'일 때)
			return (make_token(c, c + 1, DGREAT))
		return(make_token(c, c, GREAT));
	}
	if (c == '&')
	{

	}
	if (c == '|')
	{

	}
	return (scan_word_token())
}

t_tokenizer	scan_word_token(t_tokenizer token, char c)
{
	if (c == '\'' || c == '"' || c == '/')
	{
		if (안닫혔으면)
			//error
		
	}
}

t_tokenizer	make_token(char *left_ptr, char *right_ptr, t_symbol type)
{
	t_tokenizer	token;

	token.type = type;
	token.current_token = left_ptr;
	token.token_size = right_ptr - left_ptr;
	return (token);
}