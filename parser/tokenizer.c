/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naylee <naylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:26:07 by naylee            #+#    #+#             */
/*   Updated: 2023/08/11 11:26:07 by naylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/tokenizer.h"

t_bool  match_token(t_symbol token, t_tokenizer *tokenizer)
{ 
   //현재 토큰이 매개변수와 같으면 match 성공
   if(token == get_curr_token(tokenizer))
   {
		//다음토큰을 찾아놓음
   		get_next_token(tokenizer);
   		return (TRUE);
   }
   //현재 토큰이 매개변수와 다를때
   return (FALSE);

}

t_symbol get_curr_token(t_tokenizer *tokenizer) {
    return (tokenizer->type);
}


// init_tokenizer(char* line)  ==> t_tokenizer를 만든다.
// curr_token_start_ptr, curr_token_end_ptr 이 ls를 가리키고있다

// get_next_token() ==> t_tokenizer를 갱신한다.
// 갱신되면 t_tokenizer는 다른 토큰(문자열)을 가리키게 된다

//get_next_token() -> 원래 예전에 만들어놨던 t_tokenizer를 갱신.
t_symbol	get_next_token(t_tokenizer *tokenizer)
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

t_symbol	make_token(t_tokenizer *tokenizer, t_symbol type)
{
	tokenizer->type = type;
	return (type);
}

//환경변수 replace
//void	replace_env(t_tokenizer *tokenizer)
//{
//	char	*env;

//	env = ft_substr(tokenizer->start, tokenizer->end - tokenizer->start);

//}
