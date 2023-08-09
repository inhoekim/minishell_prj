#ifndef TOKNIZER_H
# define TOKNIZER_H

#include <stdio.h>

typedef enum e_bool
{
	FALSE,
	TRUE,
}   t_bool;

typedef enum e_symbol
{
    WORD, //0
    LESS, //1
    GREAT, //2
    DGREAT, //3
    DLESS, //4
    AND_IF, //5
    OR_IF, //6
    PIPE, //7
	SUBSHELL, //8
	E0F, //9
}   t_symbol;

typedef struct s_tokenizer
{
    t_symbol	type;
	char		*start;
	char		*end;
} t_tokenizer;

t_tokenizer	get_next_token(t_tokenizer *tokenizer);
t_tokenizer	scan_char_token(t_tokenizer *tokenizer);
t_tokenizer	make_token(t_tokenizer *tokenizer, t_symbol type);
t_tokenizer	scan_word_token(t_tokenizer *tokenizer);

void		reset_tokenizer(t_tokenizer *tokenizer);
void		skip_whitespace(t_tokenizer *token);
t_bool		match(t_tokenizer *tokenizer, char matchword);
t_bool		string_close(t_tokenizer *tokenizer, char c);

#endif
