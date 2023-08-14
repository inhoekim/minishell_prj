#ifndef TOKNIZER_H
# define TOKNIZER_H

#include "minishell.h"


t_bool		match_token(t_symbol type, t_tokenizer *tokenizer);
t_token		*get_curr_token(t_tokenizer *tokenizer);
t_token		*get_next_token(t_tokenizer *tokenizer);
t_token		*make_token(t_tokenizer *tokenizer, t_symbol type);
void	    set_tokenizer(t_tokenizer *tokenizer, char *line);
void		reset_start_ptr(t_tokenizer *tokenizer);
void		skip_whitespace(t_tokenizer *tokenizer);
void	    syntax_error(char * str);
t_bool		match(t_tokenizer *tokenizer, char matchword);
t_token	    *scan_char_token(t_tokenizer *tokenizer);
t_token	    *scan_word_token(t_tokenizer *tokenizer);
t_bool		string_close(t_tokenizer *tokenizer, char c);
t_bool		check_first_set(t_nonterminal idx, t_symbol curr_token);

#endif
