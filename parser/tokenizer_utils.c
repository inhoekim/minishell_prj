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

t_tokenizer	*set_tokenizer(char *line)
{
	t_tokenizer tokenizer;

	tokenizer->start = line;
	tokenizer->end = line;
	tokenizer->curr_token = get_next_token(&tokenizer);
    return (&tokenizer);
}

void	reset_start_ptr(t_tokenizer *tokenizer)
{
	if (tokenizer->type == SUBSHELL)
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
	char *line = "'hihihihi'>>";
	t_tokenizer token1;
	//t_tokenizer token2;

	token1.start = line;
	token1.end = line;
	token1.type = E0F;

	token1 = get_next_token(&token1);
	printf("str: %s\n", token1.curr_token->str);

	token1 = get_next_token(&token1);
	printf("str: %s\n", token1.curr_token->str);
}
