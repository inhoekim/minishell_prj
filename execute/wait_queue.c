#include "../include/wait_queue.h"
#include "../include/minishell.h"
#include "../include/execute.h"
#include "../include/exec_node_util.h"
#include "../include/exec_word_util.h"
#include "../include/filename_expansion.h"
#include "../include/arg_expansion.h"
#include "../include/make_argv_util.h"

void	enqueue(pid_t pid, t_context *p_ctx)
{
	if (PROC_MAX <= p_ctx->queue_size)
		exit(1);
	p_ctx->queue[p_ctx->queue_size] = pid;
	p_ctx->queue_size++;
}

void	wait_queue(t_context *p_ctx)
{
	int	last_idx;
	int	idx;

	last_idx = p_ctx->queue_size;
	idx = last_idx;
	last_idx--;
	while (--idx >= 0)
	{
		if (idx == last_idx)
			wait_and_set_exit_status(p_ctx->queue[idx], p_ctx, 1);
		else
			wait_and_set_exit_status(p_ctx->queue[idx], p_ctx, 0);
		p_ctx->queue_size--;
	}
	if (p_ctx->queue_size == -1)
		p_ctx->queue_size = 0;
}
