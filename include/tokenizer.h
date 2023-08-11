#ifndef TOKNIZER_H
# define TOKNIZER_H

#include "minishell.h"

t_tokenizer	get_next_token(t_tokenizer *tokenizer);
t_tokenizer	scan_char_token(t_tokenizer *tokenizer);
t_tokenizer	make_token(t_tokenizer *tokenizer, t_symbol type);
t_tokenizer	scan_word_token(t_tokenizer *tokenizer);

void		reset_tokenizer(t_tokenizer *tokenizer);
void		skip_whitespace(t_tokenizer *token);
t_bool		match(t_tokenizer *tokenizer, char matchword);
t_bool		string_close(t_tokenizer *tokenizer, char c);
t_bool		check_first_set(t_nonterminal idx, t_symbol curr_token);
#endif
