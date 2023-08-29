#ifndef MINISHELL_H
# define MINISHELL_H
# define NONE -1
# define STDERR_FD 2

# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <errno.h> 
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>

# define PATH_MAX 1024
# define PROC_MAX 1024
# define DELIMLEN 1024
# define HEREDOC_MAX 16
# define TOKEN_SIZE 1024
# define DELIMETER "<>&|() \t\n"

# define STDIN 0
# define STDOUT 1

typedef enum e_bool
{
	FALSE,
	TRUE,
} t_bool;

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

typedef struct s_heredoc_data{
	int	heredoc_fault_flag;
	int	heredoc_eof_flag;
	int	temp_stdin_fd;
	int	cursor_size;
}t_heredoc_data;

void	init_envp(char **envp);
t_list	**get_envp(void);
void	print_eof_exit();
void	minishell_loop(void);


void	arg_expansion(t_list *list);
char	*parameter_expansion(char *str);
t_list	*make_key_listist(char *str, int i);

void		exec_word(t_node *node, t_context *p_ctx);
void		search_and_fork_exec(char **argv, t_context *p_ctx);
char		**path_split(char *s, char c);
char		*make_order(char **path, char **argv);
void		exec_subshell(t_node *node, t_context *p_ctx);
void		exec_or(t_node *node, t_context *p_ctx);
void		exec_and(t_node *node, t_context *p_ctx);
void		exec_pipe(t_node *node, t_context *p_ctx);
void		exec_input(t_node *node, t_context *p_ctx);
void		exec_heredoc(t_node *node, t_context *p_ctx);
void		exec_output(t_node *node, t_context *p_ctx);
void		exec_append(t_node *node, t_context *p_ctx);
void		check_env(char **argv, t_list **env);
int			check_argv(char *argv);
char		*make_temp(char *s1);
t_bool		exec_builtin(char **argv, t_context *p_ctx);


char	**make_argv(char **word_arr);
void	fork_exec(char **argv, t_context *p_ctx);
char	**list_to_arr(t_list *node);
t_bool	can_access(char *filename, t_context *p_ctx);

void	free_argv(char **argv);
void	set_exit_status(int exit_status);
int		*get_exit_status(void);
void	fork_error(t_context *p_ctx);

void	execute(t_node *root);
void	exec_node(t_node *node, t_context *p_ctx);

t_bool	ft_cd(char **argv);

t_bool	ft_echo(char **argv);
t_bool	ft_pwd(char **argv);
t_bool	ft_env(char **argv);
t_bool	ft_exit(char **argv);
t_bool	ft_export(char **argv);
t_bool	ft_unset(char **argv);
void	exit_utils(char **temp);
char	*ft_strnjoin(char const *s1, char const *s2);
void	delete_node(t_list **head, t_list *node_to_delete);
char	*ft_getenv(char *pos);
t_list	*getenv_list(char *pos, size_t pos_len, t_list **env);
void	set_envp(char *pos, char *pwd);
int		*get_last_pid(void);
void	set_last_pid(int pid);
void	find_last_pid(t_context	*p_ctx);
int		*get_last_exit_status(void);
void	set_last_exit_status(int exit_status);

t_list	*filename_expansion(t_list *list, t_bool glob_flag);
char	*concatenate(t_list *list);
t_list	*globbing(char *pattern);
int		**allocate_dp(int row, int col);
void	msh_error(char *name, char *msg, int error);

void			set_delimiter(t_node *node, char buf[]);
char			*quote_removal(char *word);
void			heredoc(char *delimiter, t_tokenizer *tokenizer);
char			**alloc_heredoc_name(void);
t_heredoc_data	*get_heredoc_data(void);
void			set_tmp_stdin_fd(int fd);
void			set_heredoc_fault_flag(int flag);
void			set_heredoc_eof_flag(int flag);
void			set_cursor_size(int size);
void			delete_heredoc(t_tokenizer *tokenizer);

t_list	*split_quotes(char *str);
t_list	*include_slice(char *str, int *i, char end);
t_bool	check_glob(t_list *list);
t_bool	list_search(t_list *list, char ch);
void	unquote(t_list *list);


void	sigact_default_mode(void);
void	sigact_heredoc_mode(void);
void	sigact_fork_mode(void);
void	sigact_modeoff(void);
t_bool	*get_is_subshell(void);
void	set_is_subshell(t_bool flag);


t_node	*parser(char *line);
t_bool	check_first_set(t_nonterminal idx, t_symbol curr_token);
void	free_tree(t_node *root);
void	syntax_error(t_tokenizer *tokenizer);
void	free_tree(t_node *root);

t_node	*msh_grammar(t_tokenizer *tokenizer);
t_node	*conditional(t_tokenizer *tokenizer);
t_node	*pipeline(t_tokenizer *tokenizer);
t_node	*piped_command(t_tokenizer *tokenizer);
t_node	*command(t_tokenizer *tokenizer);
t_node	*ssh(t_tokenizer *tokenizer);
t_node	*simple_cmd(t_tokenizer *tokenizer);
t_node	*io_redirect_or_word_star(t_tokenizer *tokenizer);
t_node	*io_redirect_dagger(t_tokenizer *tokenizer);
t_node	*io_redirect_dg_after_simple_cmd(t_tokenizer *tokenizer);
t_node	*io_redirect_star(t_tokenizer *tokenizer);
t_node	*io_redirect(t_tokenizer *tokenizer);
t_node	*io_file(t_tokenizer *tokenizer);
t_node	*io_here(t_tokenizer *tokenizer);
t_node	*merge_tree(t_node *parent, t_node *child);
t_node	*make_leaf(t_tokenizer *tokenizer);
t_node	*make_tree(t_symbol node_type, t_node *left, t_node *right);
t_bool	is_match(t_tokenizer *tokenizer, char matchword);
t_bool	match_token(t_symbol type, t_tokenizer *tokenizer, t_bool token_move);
t_token		*get_curr_token(t_tokenizer *tokenizer);
t_token		*get_next_token(t_tokenizer *tokenizer);
t_token		*make_token(t_tokenizer *tokenizer, t_symbol type);
void		set_tokenizer(t_tokenizer *tokenizer, char *line);
void		reset_start_ptr(t_tokenizer *tokenizer);
void		skip_whitespace(t_tokenizer *tokenizer);
t_token		*scan_char_token(t_tokenizer *tokenizer);
t_token		*scan_word_token(t_tokenizer *tokenizer);
t_bool		string_close(t_tokenizer *tokenizer, char c);
t_bool		check_first_set(t_nonterminal idx, t_symbol curr_token);
void		free_tokenizer(t_tokenizer *tokenizer);


void	enqueue(pid_t pid, t_context *p_ctx);
void	wait_queue(t_context *p_ctx);
void	cir_lstadd_back(t_list **head, t_list *n_node);
void	cir_lstadd(pid_t pid, t_context *p_ctx);
void	wait_list(t_context *p_ctx);

void	set_redirect_ambiguity(t_bool value);
t_bool	*get_redirect_ambiguity(void);
t_bool	is_regular_file(char *filename, t_context *p_ctx);
t_bool	is_not_directory(char *filename, t_context *p_ctx);

void	forked_builtin(t_context *p_ctx, t_builtin	builtin_func, char **argv);
void	free_delete_heredoc(t_context *p_ctx);
int		wildcard(char *pattern, char *word, int p_idx, int w_idx);
void	*wait_process(t_list *node, t_context *p_ctx, int flag);
t_list	*_delete_process(t_list **head, t_list *d_node);
t_list	*make_key_list(char *str, int i);
t_bool	is_same_str(char *word1, char *word2);

t_bool	*get_is_subshell(void);
void	set_is_subshell(t_bool flag);

#endif
