// # define NULL 0
#define NONE -1


#include <stdio.h>
#include <libft.h>

typedef enum e_bool
{
	FALSE,
	TRUE,
}   t_bool;

typedef enum e_nonterminal{
	PIPELINE = 0,
	SIMPLE_CMD = PIPELINE,
	COMMAND = PIPELINE,
	PIPED_COMMAND = 1,
	IO_FILE = 2,
	IO_HERE = 3,
	IO_REDIRECT = 4,
	IO_REDIRECT_DAGGER = IO_REDIRECT,
	IO_REDIRECT_STAR = IO_REDIRECT,
	IO_REDIRECT_DG_AFTER_SIMPLE_CMD = 5,
	CONDITIONAL = 6,
}   t_nonterminal;

// &&, ||, |, (),  <, >, <<, >>, word 
typedef enum e_symbol
{
    WORD,
    LESS,
    GREAT,
    DGREAT,
    DLESS,
    AND_IF,
    OR_IF,
    PIPE,
	SUBSHELL,
	E0F,
}   t_symbol;

/* COMMAND or FILE_NAME */

/* binary tree */
typedef struct s_node
{
    t_symbol	type;
    t_node		*left;
    t_node		*right;
    char		**word;
} t_node;

/* object that separate tokens */
typedef struct s_tokenizer
{
    t_symbol	type;
	char		*current_token;
	int			token_size;
} t_tokenizer;

// t_symbol의 개수는 10개지만, table의 일차원 배열의 길이는 9개임. (word제외)
t_bool	check_first_set(t_nonterminal idx, t_symbol curr_token)
{
	static int table[7][9] = {
	[PIPELINE] = {WORD, LESS, GREAT, DGREAT, DLESS, NONE, NONE, NONE, NONE}, // pipeline, command, simple_cmd
	[IO_REDIRECT] = {NONE, LESS, GREAT, DGREAT, DLESS, NONE, NONE, NONE, NONE}, // io_redirect, io_redirect_star, io_redirect_dagger, 
	[CONDITIONAL] = {NONE, NONE, NONE, NONE, NONE, AND_IF, OR_IF, NONE, NONE},
	[PIPED_COMMAND] = {NONE, NONE, NONE, NONE, NONE, NONE, NONE, PIPE, NONE}, // piped_command
	[IO_REDIRECT_DG_AFTER_SIMPLE_CMD] = {WORD, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE}, // io_redirect_dg_after_simple_cmd
	[IO_FILE] = {NONE, LESS, GREAT, DGREAT, NONE, NONE, NONE, NONE, NONE}, // io_file
	[IO_HERE] = {NONE, NONE, NONE, NONE, DLESS, NONE, NONE, NONE, NONE}, // io_here
	};
	// -1이면 firstset 실패, 0 이상이면 성공
	if (table[idx][curr_token] != NONE)
		return (TRUE);
	else
		return (FALSE);
}
