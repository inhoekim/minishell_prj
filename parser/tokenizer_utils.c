/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdg <sdg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:25:45 by naylee            #+#    #+#             */
/*   Updated: 2023/08/17 01:44:17 by sdg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tokenizer.h"

void	set_tokenizer(t_tokenizer *tokenizer, char *line)
{
	tokenizer->start = line;
	tokenizer->end = line;
	tokenizer->curr_token = (t_token *)malloc(sizeof(t_token));
	// @ eof token이 ""인 이유?
	tokenizer->curr_token->len = 0;
	tokenizer->curr_token->str = "";
	tokenizer->curr_token->type = E0F;
	tokenizer->curr_token = get_next_token(tokenizer);
}

void	reset_start_ptr(t_tokenizer *tokenizer)
{
	// 이전 토큰 타입이 E0F가 아니라면(즉 첫번째로 보는 토큰이 아니라면)
	// @ gnt호출 시 호출되는 reset_start_ptr이다.
	// @ 토큰이 eof가 아닐 때, end를 1증가시키는 이유가 미리 end를 한칸 밀어서 문자를 확인하기 위함인가?
	if (tokenizer->curr_token->type != E0F)
	{	
		tokenizer->end++;
		free(tokenizer->curr_token->str);
	}
	skip_whitespace(tokenizer);
	// @거짓인 경우가 있나?
	if (tokenizer->end)
		tokenizer->start = tokenizer->end;
}

void	skip_whitespace(t_tokenizer *tokenizer)
{
	// @tokenizer가 line 끝에 도달했는지 확인하는 용도? 이게 더 간단해보임
	// if (*tokenizer->end)
	if (!tokenizer->end || !ft_strlen(tokenizer->end))
	{
        tokenizer->curr_token->type = E0F;
		return ;
	}
	while ((*tokenizer->end) && ((*tokenizer->end) == 32 || \
		((*tokenizer->end) >= 9 && (*tokenizer->end) <= 13)))
		tokenizer->end++;
}
t_bool	match(t_tokenizer *tokenizer, char matchword)
{
	tokenizer->end++;
	// @ tokenizer->end가 거짓인 경우가 있나?
	if (tokenizer->end && *tokenizer->end == matchword)
		return (TRUE);
	tokenizer->end--;
	// @ match되었으면 end(현재 tokenizer가 바라보는 포인터)가 넘어가야 함.
	return (FALSE);
}
void	free_token(t_tokenizer *tokenizer)
{
	// if (tokenizer->curr_token->str)
	// 	free(tokenizer->curr_token->str);
	free(tokenizer->curr_token);
}
