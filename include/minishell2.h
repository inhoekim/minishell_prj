#ifndef MINISHELL2_H
# define MINISHELL2_H

#include "util.h"

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
void	cir_lstadd(pid_t pid, t_context *p_ctx);
void	cir_lstadd_back(t_list **head, t_list *n_node);
#endif