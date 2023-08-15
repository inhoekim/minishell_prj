/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdg <sdg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:26:07 by naylee            #+#    #+#             */
/*   Updated: 2023/08/14 12:47:11 by sdg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


t_bool	match_token(t_symbol type, t_tokenizer *tokenizer, t_bool token_move)
{ 
   if(type == get_curr_token(tokenizer)->type)
   {
		if (token_move == TRUE)
			get_next_token(tokenizer);
		return (TRUE);
   }
   return (FALSE);
}

t_token	*get_curr_token(t_tokenizer *tokenizer) {
    return (tokenizer->curr_token);
}

t_token	*get_next_token(t_tokenizer *tokenizer)
{
	t_token token;

	reset_start_ptr(tokenizer);
	if (*tokenizer->end == '(')
	{
		if (string_close(tokenizer, ')') == FALSE)
		{
			//syntax_error("");
		}
		return (make_token(tokenizer, SUBSHELL_LEFT));
	}
	if (*tokenizer->end == ')')
		return (make_token(tokenizer, SUBSHELL_RIGHT));
	return (scan_char_token(tokenizer));
}

t_token	*make_token(t_tokenizer *tokenizer, t_symbol type)
{
	tokenizer->curr_token->type = type;
	tokenizer->curr_token->len = tokenizer->end - tokenizer->start + 1;
	//if (*tokenizer->start == '\'' || *tokenizer->start == '"')
	//	tokenizer->curr_token->len++;
	//if (tokenizer->end == tokenizer->start)
	//	tokenizer->curr_token->len++;
	tokenizer->curr_token->str = ft_substr(tokenizer->start, 0, tokenizer->curr_token->len);
	return (tokenizer->curr_token);
}

// t_token 추가(한개, 계속 갱신)
// 문자열비교할때 curr_token으로 비교
// 

//환경변수 replace
//void	replace_env(t_tokenizer *tokenizer)
//{
//	char	*env;

//	env = ft_substr(tokenizer->start, tokenizer->end - tokenizer->start);

//}