# include "../libft/libft.h"

# define STDIN 0
# define STDOUT 1

typedef enum e_bool
{
	FALSE,
	TRUE,
} t_bool;

typedef t_bool	(*t_builtin)(char **args);

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

t_bool	ft_cd(char **argv);
t_bool	ft_echo(char **argv);
t_bool	ft_export(char **argv);
t_bool	ft_exit(char **argv);
t_bool	ft_env(char **argv);
t_bool	ft_pwd(char **argv);
t_bool	ft_unset(char **argv);

void	set_last_exit_status(int exit_status);

t_builtin	check_builtin(char *argv);
void	redirect_fd(int dst[2]);
t_bool	exec_builtin(char **argv, t_context *p_ctx);
void	exec_or(t_node *node, t_context *p_ctx);
void	exec_and(t_node *node, t_context *p_ctx);
void	exec_pipe(t_node *node, t_context *p_ctx);
void	exec_heredoc(t_node *node, t_context *p_ctx);
void	search_and_fork_exec(char **argv, t_context *p_ctx);
char	*make_order(char **path, char **argv);
void	forked_builtin(t_context *p_ctx, t_builtin	builtin_func, char **argv);
t_bool	*get_redirect_ambiguity(void);
void	set_redirect_ambiguity(t_bool value);
t_bool	is_regular_file(char *filename, t_context *p_ctx);
t_bool	is_not_directory(char *filename, t_context *p_ctx);
void	exec_input(t_node *node, t_context *p_ctx);
void	exec_output(t_node *node, t_context *p_ctx);
void	exec_append(t_node *node, t_context *p_ctx);
void	exec_subshell(t_node *node, t_context *p_ctx);
void	free_argv(char **argv);
void	set_exit_status(int exit_status);
int	*get_exit_status(void);
void	fork_error(t_context *p_ctx);
void	msh_error(char *name, char *msg, int error);
t_list	*split_quotes(char *str);
t_list	*include_slice(char *str, int *i, char end);
t_bool	check_glob(t_list *list);
t_bool	list_search(t_list *list, char ch);
void	unquote(t_list *list);
void	exec_word(t_node *node, t_context *p_ctx);
void	fork_exec(char **argv, t_context *p_ctx);
char	**list_to_arr(t_list *node);
t_bool	can_access(char *filename, t_context *p_ctx);
char	**make_argv(char **word_arr);
void	execute(t_node *root);
void	exec_node(t_node *node, t_context *p_ctx);
void	find_last_pid(t_context	*p_ctx);
void	free_delete_heredoc(t_context *p_ctx);
