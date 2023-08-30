#ifndef MINISHELL2_H
# define MINISHELL2_H

// #include "util.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>

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


void	init_envp(char **envp);
t_list	**get_envp(void);
void	print_eof_exit(void);
void	minishell_loop(void);
int		*get_last_pid(void);
void	set_last_pid(int pid);
int		*get_last_exit_status(void);
void	set_last_exit_status(int exit_status);
t_list	*_delete_process(t_list **head, t_list *d_node);
void	wait_list(t_context *p_ctx);
void	*wait_process(t_list *node, t_context *p_ctx, int flag);
void	_wait_process(t_list *ret, t_context *p_ctx, t_list *node, pid_t pid);
void	cir_lstadd(pid_t pid, t_context *p_ctx);
void	cir_lstadd_back(t_list **head, t_list *n_node);
#endif