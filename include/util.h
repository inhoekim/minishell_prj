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

typedef struct s_heredoc_data{
	int	heredoc_fault_flag;
	int	heredoc_eof_flag;
	int	temp_stdin_fd;
	int	cursor_size;
}	t_heredoc_data;

#endif