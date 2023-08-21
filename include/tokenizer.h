/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdg <sdg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:12:07 by naylee            #+#    #+#             */
/*   Updated: 2023/08/18 17:22:07 by sdg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# include "minishell.h"

t_bool		match_token(t_symbol type, \
t_tokenizer *tokenizer, t_bool token_move);
t_token		*get_curr_token(t_tokenizer *tokenizer);
t_token		*get_next_token(t_tokenizer *tokenizer);
t_token		*make_token(t_tokenizer *tokenizer, t_symbol type);
void		set_tokenizer(t_tokenizer *tokenizer, char *line);
void		reset_start_ptr(t_tokenizer *tokenizer);
void		skip_whitespace(t_tokenizer *tokenizer);
t_bool		match(t_tokenizer *tokenizer, char matchword);
t_token		*scan_char_token(t_tokenizer *tokenizer);
t_token		*scan_word_token(t_tokenizer *tokenizer);
t_bool		string_close(t_tokenizer *tokenizer, char c);
t_bool		check_first_set(t_nonterminal idx, t_symbol curr_token);
void		free_tokenizer(t_tokenizer *tokenizer);

#endif
