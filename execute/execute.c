#include "../include/minishell.h"
#include "../include/execute.h"
#include "../include/exec_node_util.h"
#include "../include/here_doc.h"
#include "../include/wait_queue.h"

void	free_delete_heredoc(t_context *p_ctx);

int *get_last_pid()
{
	static int last_pid;
	return (&last_pid);
}

void	set_last_pid(int pid)
{
	*get_last_pid() = pid;
}

int *get_last_exit_status()
{
	static int last_exit_status;
	return (&last_exit_status);
}

void	set_last_exit_status(int exit_status)
{
	*get_last_exit_status() = exit_status;
}

void	find_last_pid(t_context	*p_ctx)
{
	t_list	**head;
	t_list	*prev;
	t_list	*current;
	t_list	*tmp;

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
	// list의 원소가 하나인 경우
	if (current == *head && prev == *head)
		set_last_pid(*((int *)current->content));
	// list의 원소가 하나가 아닌 경우
	else if (current == *head)
	{
		tmp = *head;
		while (tmp->next != *head)
			tmp = tmp->next;
		set_last_pid(*((int *)tmp->content));
	}
	return ;
}

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
	set_redirect_ambiguity(FALSE);
	exec_node(root, &ctx);
	find_last_pid(&ctx);
	wait_queue_after(&ctx);
	free_delete_heredoc(&ctx);
}

void	free_delete_heredoc(t_context *p_ctx)
{
	int	i;

	i = 0;
	while (i < p_ctx->heredoc_file_idx)
	{
		unlink(p_ctx->heredoc_file_name[i]);
		free(p_ctx->heredoc_file_name[i++]);
	}
	free(p_ctx->heredoc_file_name);
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
