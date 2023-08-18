#include "../include/wait_queue.h"

void	enqueue(pid_t pid, t_context *p_ctx)
{
	p_ctx->queue[p_ctx->queue_size] = pid;
	p_ctx->queue_size++;
}

void	wait_queue(t_context *p_ctx)
{
	int	idx;
	int	pid_cnt;
	int	status;

	idx = 0;
	pid_cnt = p_ctx->queue_size;
	while (idx < pid_cnt)
	{
		waitpid(p_ctx->queue[idx], &status, 0);
		set_exit_status(WEXITSTATUS(status));
		idx++;
		p_ctx->queue_size--;
	}
}
