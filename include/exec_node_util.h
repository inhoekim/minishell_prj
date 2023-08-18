/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node_util.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:38:34 by seykim            #+#    #+#             */
/*   Updated: 2023/08/18 12:21:16 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_NODE_UTIL_H
# define EXEC_NODE_UTIL_H

# include "minishell.h"
# include <sys/wait.h>

typedef t_bool	(*t_builtin)(char **args);
void		exec_word(t_node *node, t_context *p_ctx);
t_builtin	check_builtin(char *argv);
void		search_and_fork_exec(char **argv, t_context *p_ctx);
char		**ft_split2(char const *s, char c);
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
char		*make_temp(char *s1);
void		set_ctx_status(t_context *p_ctx, pid_t pid, int flag);
#endif
