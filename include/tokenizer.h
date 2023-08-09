#ifndef TOKNIZER_H
# define TOKNIZER_H

# include "minishell.h"

t_tokenizer	get_next_token(char *line);
t_tokenizer	scan_char_token(char *start, t_tokenizer *token);
t_tokenizer	scan_word_token(char *start, t_tokenizer *token);
t_tokenizer	make_token(char *start, t_tokenizer *token, t_symbol type);

char	*skip_whitespace(char *c);
t_bool	match(t_tokenizer *token, char matchword);

#endif
