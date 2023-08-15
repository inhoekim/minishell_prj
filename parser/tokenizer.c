/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhkim <inhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:26:07 by naylee            #+#    #+#             */
/*   Updated: 2023/08/15 17:19:18 by inhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


t_bool	match_token(t_symbol type, t_tokenizer *tokenizer, t_bool token_move)
{
	if (type == get_curr_token(tokenizer)->type)
	{
		if (token_move == TRUE)
			get_next_token(tokenizer);
		return (TRUE);
	}
	return (FALSE);
}

t_token	*get_curr_token(t_tokenizer *tokenizer)
{
	return (tokenizer->curr_token);
}

t_token	*get_next_token(t_tokenizer *tokenizer)
{
	reset_start_ptr(tokenizer);
	if (*tokenizer->end == '\0')
		return (make_token(tokenizer, E0F));
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
	if (type == E0F)
		tokenizer->curr_token->len = 0;
	else
		tokenizer->curr_token->len = tokenizer->end - tokenizer->start + 1;
	tokenizer->curr_token->str = ft_substr(tokenizer->start, 0, tokenizer->curr_token->len);
	return (tokenizer->curr_token);
}

t_token	*make_merge_word_token(t_tokenizer *tokenizer, int flag)
{
	char	*ptr;
	char	*str;
	int		len;
	int		i;

	len = tokenizer->end - tokenizer->start - (flag * 2) + 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	ptr = tokenizer->start;
	i = 0;
	while (ptr <= tokenizer->end)
	{
		if (*ptr != '\'' && *ptr != '"')
		{
			str[i] = *ptr;
			i++;
		}
		ptr++;
	}
	tokenizer->curr_token->type = WORD;
	tokenizer->curr_token->len = len;
	tokenizer->curr_token->str = str;
	return (tokenizer->curr_token);
}
