#ifndef GRAMMAR_H
# define GRAMMAR_H
# define DELIMLEN 1024
# define HEREDOC_MAX 16
# define STDIN 0
# define STDOUT 1

# include "../libft/libft.h"

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
}	t_symbol;

/* binary tree */
typedef struct s_node
{
	t_symbol		type;
	struct s_node	*left;
	struct s_node	*right;
	char			**word;
}	t_node;

typedef struct s_token
{
	t_symbol	type;
	char		*str;
	int			len;
}	t_token;

/* object that separate tokens */
typedef struct s_tokenizer
{
	t_token	*curr_token;
	char	*start;
	char	*end;
	int		heredoc_file_idx;
	char	**heredoc_file_name;
	int		token_size;
}	t_tokenizer;

typedef struct s_heredoc_data{
	int	heredoc_fault_flag;
	int	heredoc_eof_flag;
	int	temp_stdin_fd;
	int	cursor_size;
} t_heredoc_data;

//heredoc
t_heredoc_data	*get_heredoc_data(void);
t_bool			is_same_str(char *word1, char *word2);
void			heredoc(char *delimiter, t_tokenizer *tokenizer);
void			set_heredoc_eof_flag(int flag);
void			set_tmp_stdin_fd(int fd);
void			set_heredoc_fault_flag(int flag);
void			delete_heredoc(t_tokenizer *tokenizer);
void			set_delimiter(t_node *node, char buf[]);

// rule
t_node			*msh_grammar(t_tokenizer *tokenizer);
t_node			*conditional(t_tokenizer *tokenizer);
t_node			*pipeline(t_tokenizer *tokenizer);
t_node			*piped_command(t_tokenizer *tokenizer);
t_node			*command(t_tokenizer *tokenizer);
t_node			*ssh(t_tokenizer *tokenizer);
t_node			*simple_cmd(t_tokenizer *tokenizer);
t_node			*io_redirect_or_word_star(t_tokenizer *tokenizer);
t_node			*io_redirect_dagger(t_tokenizer *tokenizer);
t_node			*io_redirect_dg_after_simple_cmd(t_tokenizer *tokenizer);
t_node			*io_redirect_star(t_tokenizer *tokenizer);
t_node			*io_redirect(t_tokenizer *tokenizer);
t_node			*io_file(t_tokenizer *tokenizer);
t_node			*io_here(t_tokenizer *tokenizer);

#endif