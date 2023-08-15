#define NONE -1


#include <stdio.h>
#include "libft.h"
#include "execute.h"

typedef enum e_bool
{
	FALSE,
	TRUE,
}   t_bool;

typedef enum e_nonterminal{
	PIPELINE = 0,
	SIMPLE_CMD = PIPELINE,
	COMMAND = PIPELINE,
	IO_REDIRECT_OR_WORD_STAR = PIPELINE,
	PIPED_COMMAND = 1,
	IO_FILE = 2,
	IO_HERE = 3,
	IO_REDIRECT = 4,
	IO_REDIRECT_DAGGER = IO_REDIRECT,
	IO_REDIRECT_DG_AFTER_SIMPLE_CMD = 5,
	CONDITIONAL = 6,
}   t_nonterminal;

// &&, ||, |, (, ),  <, >, <<, >>, word
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
	SUBSHELL_LEFT,
	SUBSHELL_RIGHT,
	E0F,
}   t_symbol;

/* binary tree */
typedef struct s_node
{
    t_symbol		type;
	struct s_node	*left;
    struct s_node	*right;
    char			**word;
} t_node;

typedef struct s_token
{
	t_symbol	type;
	char		*str;
	int			len;
}t_token;

/* object that separate tokens */
typedef struct s_tokenizer
{
    t_token		*curr_token;
	char		*start;
	char		*end;
} t_tokenizer;

t_list	**get_envp(void);
