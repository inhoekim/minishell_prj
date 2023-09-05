/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdg <sdg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:12:43 by seykim            #+#    #+#             */
/*   Updated: 2023/08/30 23:24:27 by sdg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <errno.h>

# include "../libft/libft.h"
# include "grammar.h"
# include "ft_signal.h"
# include "parser.h"
# include "execute.h"

# define PROC_MAX 1024
# define STDOUT 1
# define STDIN 0

typedef struct s_context	t_context;

t_list	*_delete_process(t_list **head, t_list *d_node);
t_list	**get_envp(void);
void	init_envp(char **envp);
void	print_eof_exit(void);
void	minishell_loop(void);
void	set_last_pid(int pid);
void	wait_list(t_context *p_ctx);
void	*wait_process(t_list *node, t_context *p_ctx, int flag);
void	_wait_process(t_list **ret, t_context *p_ctx, t_list *node, pid_t pid);
void	cir_lstadd(pid_t pid, t_context *p_ctx);
void	cir_lstadd_back(t_list **head, t_list *n_node);
int		*get_last_pid(void);
int		*get_last_exit_status(void);

#endif