/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdg <sdg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:25:45 by naylee            #+#    #+#             */
/*   Updated: 2023/08/17 12:43:29 by sdg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tokenizer.h"

void	set_tokenizer(t_tokenizer *tokenizer, char *line)
{
	tokenizer->start = line;
	tokenizer->end = line;
	tokenizer->curr_token = (t_token *)malloc(sizeof(t_token));
	// * eof token이 ""인 이유?
	// tokenizer->curr_token->len = 0;
	// tokenizer->curr_token->str = "";
	tokenizer->curr_token->type = E0F;
	tokenizer->curr_token = get_next_token(tokenizer);
}

// void	reset_start_ptr(t_tokenizer *tokenizer)
// {
// 	// 첫번째로 보는 토큰은 EOF.
// 	// 이전 토큰 타입이 E0F가 아니라면(즉 첫번째로 보는 토큰이 아니라면)
// 	// if (tokenizer->curr_token->type != E0F)
// 	// {	
// 	// 	tokenizer->end++;
// 	// 	// @ grammar부분에서 free할 때 문제없으면 아래 라인은 없어도 됨.
// 	// 	free(tokenizer->curr_token->str);
// 	// }
// 	// token이 아닌 부분을 넘김
// 	skip_whitespace(tokenizer);
// 	tokenizer->start = tokenizer->end;
// }

void	skip_whitespace(t_tokenizer *tokenizer)
{
	if (!tokenizer->end || !*tokenizer->end)
	{
        tokenizer->curr_token->type = E0F;
		return ;
	}
	while ((*tokenizer->end) && ((*tokenizer->end) == ' ' || \
		((*tokenizer->end) >= '\t' && (*tokenizer->end) <= '\r')))
		tokenizer->end++;
	tokenizer->start = tokenizer->end;
}
t_bool	match(t_tokenizer *tokenizer, char matchword)
{
	tokenizer->end++;
	if (tokenizer->end && *tokenizer->end == matchword)
		return (TRUE);
	tokenizer->end--;
	return (FALSE);
}
// void	free_token(t_tokenizer *tokenizer)
// {
// 	if (tokenizer->curr_token->str)
// 		free(tokenizer->curr_token->str);
// 	// free(tokenizer->curr_token->str);
// 	free(tokenizer->curr_token);
// }
