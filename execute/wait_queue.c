#include "../include/wait_queue.h"
#include "../include/execute.h"

void	enqueue(pid_t pid, t_context *p_ctx)
{
	if (PROC_MAX <= p_ctx->queue_size)
		exit(1);
	p_ctx->queue[p_ctx->queue_size] = pid;
	p_ctx->queue_size++;
}

// void	enqueue_n(pid_t pid, t_context *p_ctx)
// {
// 	// pid -> int new
// 	int *_pid = (int *)malloc(sizeof(int));
// 	*_pid = pid;
// 	ft_lstadd_back(p_ctx->pid_list, ft_lstnew(_pid));
// }


// void	wait_and_set_exit_status_n(t_list *node, t_context *p_ctx, int flag)
// {
// 	int		status;
// 	pid_t	pid;

// 	pid = *((int *)node->content);
// 	waitpid(pid, &status, flag);
// 	if (WIFEXITED(status))
// 	{
// 		p_ctx->exit_status = WEXITSTATUS(status);
// 		set_exit_status(p_ctx->exit_status);
// 		delete_node(p_ctx->pid_list, node);
// 		p_ctx->pid_size--;
// 	}
// 	else if (WIFSIGNALED(status))
// 	{
// 		p_ctx->exit_status = WTERMSIG(status) + 128;
// 		set_exit_status(p_ctx->exit_status);
// 		delete_node(p_ctx->pid_list, node);
// 		p_ctx->pid_size--;
// 	}
// }


// void	wait_queue_n(t_context *p_ctx)
// {
// 	t_list	*_pid_list;


// 	while (_pid_list && p_ctx->pid_size)
// 	{
// 		wait_and_set_exit_status_n(_pid_list, p_ctx, WNOHANG);
// 		_pid_list = _pid_list->next;
// 	}

// }

void	wait_queue(t_context *p_ctx)
{
	int	idx;
	int	size;

	idx = 0;
	size = p_ctx->queue_size;
	while (idx < size)
	{
		wait_and_set_exit_status(p_ctx->queue[idx], p_ctx, 0);
		idx++;
		p_ctx->queue_size--;
	}
}
