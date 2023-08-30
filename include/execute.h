#ifndef EXECUTE_H
# define EXECUTE_H

# include "signal.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/stat.h>
# define STDIN 0
# define STDOUT 1

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
} t_nonterminal;

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

typedef struct s_heredoc_data{
	int	heredoc_fault_flag;
	int	heredoc_eof_flag;
	int	temp_stdin_fd;
	int	cursor_size;
} t_heredoc_data;


typedef struct s_context
{
	int		exit_status;
	int		fd[2];
	int		fd_close;
	int		heredoc_file_idx;
	char	**heredoc_file_name;
	t_list	*pid_list;
	int		pid_size;
	t_bool	is_piped_cmd;
}	t_context;

typedef t_bool	(*t_builtin)(char **args);

t_builtin	check_builtin(char *argv);
t_list		*split_quotes(char *str);
t_list		*include_slice(char *str, int *i, char end);
t_bool		exec_builtin(char **argv, t_context *p_ctx);
t_bool		*get_redirect_ambiguity(void);
t_bool		is_regular_file(char *filename, t_context *p_ctx);
t_bool		is_not_directory(char *filename, t_context *p_ctx);
t_bool		check_glob(t_list *list);
t_bool		list_search(t_list *list, char ch);
t_bool		can_access(char *filename, t_context *p_ctx);
char		*make_order(char **path, char **argv);
char		**list_to_arr(t_list *node);
char		**make_argv(char **word_arr);
void		redirect_fd(int dst[2]);
void		exec_or(t_node *node, t_context *p_ctx);
void		exec_and(t_node *node, t_context *p_ctx);
void		exec_pipe(t_node *node, t_context *p_ctx);
void		exec_heredoc(t_node *node, t_context *p_ctx);
void		search_and_fork_exec(char **argv, t_context *p_ctx);
void		set_redirect_ambiguity(t_bool value);
void		exec_input(t_node *node, t_context *p_ctx);
void		exec_output(t_node *node, t_context *p_ctx);
void		exec_append(t_node *node, t_context *p_ctx);
void		ambiguity_check(char **filename, t_node *rhs, t_context *p_ctx);
void		exec_subshell(t_node *node, t_context *p_ctx);
void		free_argv(char **argv);
void		set_exit_status(int exit_status);
void		fork_error(t_context *p_ctx);
void		msh_error(char *name, char *msg, int error);
void		unquote(t_list *list);
void		exec_word(t_node *node, t_context *p_ctx);
void		fork_exec(char **argv, t_context *p_ctx);
void		execute(t_node *root);
void		exec_node(t_node *node, t_context *p_ctx);
void		find_last_pid(t_context *p_ctx);
void		free_delete_heredoc(t_context *p_ctx);
void		set_last_exit_status(int exit_status);
void		forked_builtin(t_context *p_ctx, \
t_builtin builtin_func, char **argv);
int			*get_exit_status(void);
#endif