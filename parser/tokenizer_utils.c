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
	tokenizer->curr_token = get_next_token(tokenizer);
}

void	reset_start_ptr(t_tokenizer *tokenizer)
{
	if (tokenizer->curr_token->type == SUBSHELL)
		tokenizer->end++;
	if (tokenizer->start != tokenizer->end)
		tokenizer->end++;
	skip_whitespace(tokenizer);
	if (*tokenizer->end == '\0')
	{
		//종료
	}
	tokenizer->start = tokenizer->end;
}

void	skip_whitespace(t_tokenizer *tokenizer)
{
	while ((*tokenizer->end) == 32 || \
		((*tokenizer->end) >= 9 && (*tokenizer->end) <= 13))
		tokenizer->end++;
	tokenizer->start = tokenizer->end;
}

t_bool	match(t_tokenizer *tokenizer, char matchword)
{
	tokenizer->end++;
	if (tokenizer->end && *(tokenizer->end) == matchword)
		return (TRUE);
	return (FALSE);
}


#include <stdio.h>
int main(void)
{
	char *line = "<<  >>";
	t_tokenizer tokenizer;
	//t_tokenizer token2;

	tokenizer.start = line;
	tokenizer.end = line;
	tokenizer.curr_token->len = 0;
	tokenizer.curr_token->str = 0;
	tokenizer.curr_token->type = E0F;
	//tokenizer.curr_token = get_next_token(&tokenizer);
	//token1.curr_token->type = NULL;

	tokenizer.curr_token = get_next_token(&tokenizer);
	printf("str: %s\n", tokenizer.curr_token->str);
	printf("start ptr: %s\n", tokenizer.start);
	printf("ended ptr: %s\n\n", tokenizer.end);

	tokenizer.curr_token = get_next_token(&tokenizer);
	printf("str: %s\n", tokenizer.curr_token->str);
	printf("start ptr: %s\n", tokenizer.start);
	printf("ended ptr: %s\n", tokenizer.end);
}
