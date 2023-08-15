/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naylee <naylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:25:45 by naylee            #+#    #+#             */
/*   Updated: 2023/08/11 11:25:45 by naylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/tokenizer.h"

void	set_tokenizer(t_tokenizer *tokenizer, char *line)
{
	tokenizer->start = line;
	tokenizer->end = line;
	tokenizer->curr_token = (t_token *)malloc(sizeof(t_token));
	tokenizer->curr_token->len = 0;
	tokenizer->curr_token->str = "";
	tokenizer->curr_token->type = E0F;
	tokenizer->curr_token = get_next_token(tokenizer);
}

void	reset_start_ptr(t_tokenizer *tokenizer)
{
	//이전 토큰 타입이 E0F가 아니라면(즉 첫번째로 보는 토큰이 아니라면)
	if (tokenizer->curr_token->type != E0F)
	{	
		tokenizer->end++;
		free(tokenizer->curr_token->str);
	}
	skip_whitespace(tokenizer);
	tokenizer->start = tokenizer->end;
}

void	skip_whitespace(t_tokenizer *tokenizer)
{
	while ((*tokenizer->end) && ((*tokenizer->end) == 32 || \
		((*tokenizer->end) >= 9 && (*tokenizer->end) <= 13)))
		tokenizer->end++;
	if (*(tokenizer->end) == '\0')
        tokenizer->curr_token->type = E0F;
}

t_bool	match(t_tokenizer *tokenizer, char matchword)
{
	tokenizer->end++;
	if (tokenizer->end && *tokenizer->end == matchword)
		return (TRUE);
	tokenizer->end--;
	return (FALSE);
}
