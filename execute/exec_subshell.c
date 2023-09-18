/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:27:34 by seykim            #+#    #+#             */
/*   Updated: 2023/09/18 13:27:34 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

t_bool	*get_is_subshell(void);

void	exec_subshell(t_node *node, t_context *p_ctx)
{
	int		pid;
	t_node	*lhs;

	lhs = node->left;
	if (!*get_is_subshell())
		sigact_fork_mode();
	set_is_subshell(TRUE);
	pid = fork();
	if (pid == 0)
	{
		sigact_modeoff();
		if (p_ctx->fd_close >= 0)
			close(p_ctx->fd_close);
		exec_node(lhs, p_ctx);
		wait_list(p_ctx);
		exit(p_ctx->exit_status);
	}
	set_is_subshell(FALSE);
	if (p_ctx->fd[STDIN] != STDIN)
		close(p_ctx->fd[STDIN]);
	if (p_ctx->fd[STDOUT] != STDOUT)
		close(p_ctx->fd[STDOUT]);
	cir_lstadd(pid, p_ctx);
}
