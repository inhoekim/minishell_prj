#ifndef PARSER_H
# define PARSER_H

# define HEREDOC_MAX 16
# define TOKEN_SIZE 1024
# define DELIMETER "<>&|() \t\n"

typedef enum e_bool
{
	FALSE,
	TRUE,
}	t_bool;

typedef t_bool	(*t_builtin)(char **args);

typedef enum e_nonterminal{
	PIPELINE = 0,
	COMMAND = PIPELINE,
	SIMPLE_CMD = 1,
	IO_REDIRECT_OR_WORD_STAR = SIMPLE_CMD,
	PIPED_COMMAND = 2,
	IO_FILE = 3,
	IO_HERE = 4,
	IO_REDIRECT = 5,
	IO_REDIRECT_DAGGER = IO_REDIRECT,
	IO_REDIRECT_DG_AFTER_SIMPLE_CMD = 6,
	CONDITIONAL = 7,
}t_nonterminal;

// word, <, >, >>, <<, &&, ||, |, (, eof, ssh, ), err
// SUBSHELL_LEFT, SUBSHELL_RIGHT, E0F, SYNTAX_ERR 심볼은 오직 토크나이저에서만 사용하는 심벌
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
	SUBSHELL_LEFT,
	E0F,
	SUBSHELL,
	SUBSHELL_RIGHT,
	SYNTAX_ERR
} t_symbol;

/* binary tree */
typedef struct s_node
{
	t_symbol		type;
	struct s_node	*left;
	struct s_node	*right;
	char			**word;
}t_node;

typedef struct s_token
{
	t_symbol	type;
	char		*str;
	int			len;
}t_token;

/* object that separate tokens */
typedef struct s_tokenizer
{
	t_token	*curr_token;
	char	*start;
	char	*end;
	int		heredoc_file_idx;
	char	**heredoc_file_name;
	int		token_size;
}t_tokenizer;


t_node	*parser(char *line);
void	syntax_error(t_tokenizer *tokenizer);
void	free_tokenizer(t_tokenizer *tokenizer);
t_bool	check_first_set(t_nonterminal idx, t_symbol curr_token);
t_token	*make_token(t_tokenizer *tokenizer, t_symbol type);
t_bool	match_token(t_symbol type, t_tokenizer *tokenizer, t_bool token_move);
t_token	*get_curr_token(t_tokenizer *tokenizer);
t_token	*get_next_token(t_tokenizer *tokenizer);
void	set_tokenizer(t_tokenizer *tokenizer, char *line);
void	skip_whitespace(t_tokenizer *tokenizer);
t_bool	is_match(t_tokenizer *tokenizer, char matchword);
char	**alloc_heredoc_name(void);
t_token	*scan_char_token(t_tokenizer *tokenizer);
t_token	*scan_word_token(t_tokenizer *tokenizer);
t_bool	string_close(t_tokenizer *tokenizer, char c);
t_node	*make_leaf(t_tokenizer *tokenizer);
t_node	*make_tree(t_symbol node_type, t_node *left, t_node *right);
void	free_tree(t_node *root);
t_node	*merge_tree(t_node *parent, t_node *child);

#endif
