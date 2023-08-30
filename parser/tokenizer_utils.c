/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:25:45 by naylee            #+#    #+#             */
/*   Updated: 2023/08/30 16:36:06 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void	set_tokenizer(t_tokenizer *tokenizer, char *line)
{
	tokenizer->start = line;
	tokenizer->end = line;
	tokenizer->curr_token = (t_token *)malloc(sizeof(t_token));
	tokenizer->curr_token->type = E0F;
	tokenizer->curr_token->str = "";
	tokenizer->curr_token = get_next_token(tokenizer);
	tokenizer->heredoc_file_idx = 0;
	tokenizer->token_size = 0;
	tokenizer->heredoc_file_name = alloc_heredoc_name();
}

char	**alloc_heredoc_name(void)
{
	char	**file_name;
	char	*prefix;
	char	*suffix;
	int		i;

	file_name = (char **)ft_calloc(HEREDOC_MAX + 1, sizeof(char *));
	if (!file_name)
		exit(ENOMEM);
	i = 0;
	while (i < HEREDOC_MAX)
	{
		prefix = ft_strdup("heredoc_");
		suffix = ft_itoa(i);
		file_name[i++] = ft_strjoin(prefix, suffix);
		free(prefix);
		free(suffix);
	}
	return (file_name);
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

t_bool	is_match(t_tokenizer *tokenizer, char matchword)
{
	tokenizer->end++;
	if (tokenizer->end && *tokenizer->end == matchword)
		return (TRUE);
	tokenizer->end--;
	return (FALSE);
}
