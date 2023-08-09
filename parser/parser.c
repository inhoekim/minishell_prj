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

static char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}

// init_tokenizer(char* line)  ==> t_tokenizer를 만든다.
// curr_token_start_ptr, curr_token_end_ptr 이 ls를 가리키고있다

// get_next_token() ==> t_tokenizer를 갱신한다.
// 갱신되면 t_tokenizer는 다른 토큰(문자열)을 가리키게 된다

//get_next_token() -> 원래 예전에 만들어놨던 t_tokenizer를 갱신.
t_tokenizer	get_next_token(t_tokenizer *tokenizer)
{
	reset_tokenizer(tokenizer);
	if (*tokenizer->end == '(')
	{
		tokenizer->start++;
		while (*tokenizer->end != '\0' && *tokenizer->end != ')')
			tokenizer->end++;
		if (*tokenizer->end == ')')
		{
			tokenizer->end--;
			return (make_token(tokenizer, SUBSHELL));
		}
		else
		{
			//syntax error 종료
			printf("!!!!!!!!!syntax error!!!!!!!!!!!\n");
		}
	}
	if (*tokenizer->end == ')')
	{
		//syntax error 종료
		printf("!!!!!!!!!syntax error!!!!!!!!!!!\n");
	}
	return (scan_char_token(tokenizer));
}

t_tokenizer	scan_char_token(t_tokenizer *tokenizer)
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

t_tokenizer	scan_word_token(t_tokenizer *tokenizer)
{
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

t_tokenizer	make_token(t_tokenizer *tokenizer, t_symbol type)
{
	tokenizer->type = type;
	return (*tokenizer);
}
