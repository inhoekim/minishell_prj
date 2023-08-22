/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:48:17 by dasong            #+#    #+#             */
/*   Updated: 2023/08/22 12:11:59 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# define STDIN 0
# define STDOUT 1
# define PATH_MAX 1024
# define PROC_MAX 1024
#include "minishell.h"

typedef struct s_context
{
	int		exit_status;
	int		fd[2];
	int		fd_close;
	int		heredoc_file_idx;
	char	**heredoc_file_name;
	pid_t	queue[PROC_MAX];
	int		queue_size;
	t_bool		is_piped_cmd;
}	t_context;

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
char	*vaild_env(char **temp);
char	*special_case(char **temp);
char	*ft_strnjoin(char const *s1, char const *s2);
void	delete_node(t_list **head, t_list *node_to_delete);
char	*ft_getenv(char *pos);
t_list	*getenv_list(char *pos, size_t pos_len, t_list **env);
void	set_envp(char *pos, char *pwd);

void	enqueue(pid_t pid, t_context *p_ctx);
void	wait_queue(t_context *p_ctx);

#endif
