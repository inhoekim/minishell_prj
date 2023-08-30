#ifndef UTIL_H
# define UTIL_H

# define NONE -1
# define STDERR_FD 2
# define PATH_MAX 1024
# define PROC_MAX 1024
# define DELIMLEN 1024
# define HEREDOC_MAX 16
# define TOKEN_SIZE 1024
# define DELIMETER "<>&|() \t\n"
# define STDIN 0
# define STDOUT 1

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
}	t_nonterminal;

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
}	t_heredoc_data;

#endif