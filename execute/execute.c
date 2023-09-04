/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:12:05 by seykim            #+#    #+#             */
/*   Updated: 2023/08/30 19:12:06 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

char	**alloc_heredoc_name(void);
void	sigact_default_mode(void);
void	set_is_subshell(t_bool flag);
void	wait_list(t_context *p_ctx);
void	set_last_pid(int pid);

void	execute(t_node *root)
{
	t_context	ctx;

	ctx.fd[STDIN_FILENO] = STDIN_FILENO;
	ctx.fd[STDOUT_FILENO] = STDOUT_FILENO;
	ctx.fd_close = -1;
	ctx.is_piped_cmd = FALSE;
	ctx.heredoc_file_idx = 0;
	ctx.heredoc_file_name = alloc_heredoc_name();
	ctx.pid_list = NULL;
	ctx.pid_size = 0;
	sigact_default_mode();
	set_is_subshell(FALSE);
	set_redirect_ambiguity(FALSE);
	exec_node(root, &ctx);
	find_last_pid(&ctx);
	wait_list(&ctx);
	free_delete_heredoc(&ctx);
}

void	exec_node(t_node *node, t_context *p_ctx)
{
	if (node == NULL)
		return ;
	else if (node->type == WORD)
		exec_word(node, p_ctx);
	else if (node->type == LESS)
		exec_input(node, p_ctx);
	else if (node->type == GREAT)
		exec_output(node, p_ctx);
	else if (node->type == DGREAT)
		exec_append(node, p_ctx);
	else if (node->type == DLESS)
		exec_heredoc(node, p_ctx);
	else if (node->type == AND_IF)
		exec_and(node, p_ctx);
	else if (node->type == OR_IF)
		exec_or(node, p_ctx);
	else if (node->type == PIPE)
		exec_pipe(node, p_ctx);
	else if (node->type == SUBSHELL)
		exec_subshell(node, p_ctx);
	return ;
}

void	find_last_pid(t_context	*p_ctx)
{
	t_list	**head;
	t_list	*prev;
	t_list	*current;

	head = &(p_ctx->pid_list);
	if (!(*head))
		return ;
	prev = *head;
	current = (*head)->next;
	while (current != *head)
	{
		prev = current;
		current = current->next;
	}
	set_last_pid(*((int *)prev->content));
	return ;
}

void	free_delete_heredoc(t_context *p_ctx)
{
	int	i;

	i = 0;
	while (i < p_ctx->heredoc_file_idx)
		unlink(p_ctx->heredoc_file_name[i++]);
	i = 0;
	while (i < 16)
		free(p_ctx->heredoc_file_name[i++]);
	free(p_ctx->heredoc_file_name);
}
