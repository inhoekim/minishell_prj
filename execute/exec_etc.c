/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_etc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:11:26 by seykim            #+#    #+#             */
/*   Updated: 2023/08/30 19:11:27 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int		*get_last_exit_status(void);
void	wait_list(t_context *p_ctx);

void	exec_or(t_node *node, t_context *p_ctx)
{
	t_node	*lhs;
	t_node	*rhs;

	lhs = node->left;
	rhs = node->right;
	exec_node(lhs, p_ctx);
	find_last_pid(p_ctx);
	wait_list(p_ctx);
	if (*get_last_exit_status() != 0)
		exec_node(rhs, p_ctx);
}

void	exec_and(t_node *node, t_context *p_ctx)
{
	t_node	*lhs;
	t_node	*rhs;

	lhs = node->left;
	rhs = node->right;
	exec_node(lhs, p_ctx);
	find_last_pid(p_ctx);
	wait_list(p_ctx);
	if (*get_last_exit_status() == 0)
		exec_node(rhs, p_ctx);
}

void	exec_pipe(t_node *node, t_context *p_ctx)
{
	t_node		*lhs;
	t_node		*rhs;
	int			pipe_fd[2];
	t_context	aux;

	p_ctx->is_piped_cmd = TRUE;
	lhs = node->left;
	rhs = node->right;
	pipe(pipe_fd);
	aux = *p_ctx;
	aux.fd[STDOUT] = pipe_fd[STDOUT];
	aux.fd_close = pipe_fd[STDIN];
	exec_node(lhs, &aux);
	p_ctx->pid_list = aux.pid_list;
	p_ctx->pid_size = aux.pid_size;
	aux = *p_ctx;
	aux.fd[STDIN] = pipe_fd[STDIN];
	aux.fd_close = pipe_fd[STDOUT];
	exec_node(rhs, &aux);
	p_ctx->pid_list = aux.pid_list;
	p_ctx->pid_size = aux.pid_size;
	p_ctx->is_piped_cmd = FALSE;
}

void	exec_heredoc(t_node *node, t_context *p_ctx)
{
	t_node	*lhs;

	lhs = node->left;
	if (p_ctx->fd[STDIN] != STDIN)
		close(p_ctx->fd[STDIN]);
	p_ctx->fd[STDIN] = \
		open(p_ctx->heredoc_file_name[p_ctx->heredoc_file_idx++], \
		O_RDONLY, 0644);
	exec_node(lhs, p_ctx);
}
