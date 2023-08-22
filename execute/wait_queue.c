#include "../include/wait_queue.h"

void	enqueue(pid_t pid, t_context *p_ctx)
{
	if (PROC_MAX <= p_ctx->queue_size)
		exit(1);
	p_ctx->queue[p_ctx->queue_size] = pid;
	p_ctx->queue_size++;
}

void	wait_queue(t_context *p_ctx)
{
	int	idx;
	int	size;

	idx = 0;
	size = p_ctx->queue_size;
	while (idx < size)
	{
		wait_and_set_exit_status(p_ctx->queue[idx], p_ctx, WNOHANG);
		idx++;
		idx %= size;
		p_ctx->queue_size--;
	}
	if (*get_exit_status() != 0)
		p_ctx->exit_status = 1;
	else
		p_ctx->exit_status = 0;
}
