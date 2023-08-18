/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdg <sdg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:25:45 by naylee            #+#    #+#             */
/*   Updated: 2023/08/17 18:25:11 by sdg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tokenizer.h"

void	set_tokenizer(t_tokenizer *tokenizer, char *line)
{
	tokenizer->start = line;
	tokenizer->end = line;
	tokenizer->curr_token = (t_token *)malloc(sizeof(t_token));
	// tokenizer->curr_token->len = 0;
	// tokenizer->curr_token->str = "";
	tokenizer->curr_token->type = E0F;
	tokenizer->curr_token = get_next_token(tokenizer);
}

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
