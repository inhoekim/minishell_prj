#include "../include/minishell.h"
#include "../include/execute.h"
#include "../include/exec_node_util.h"
#include "../include/exec_word_util.h"
#include "../include/make_argv_util.h"
#include "../include/execute_util.h"

void	enqueue(pid_t pid, t_context *p_ctx)
{
	p_ctx->queue[p_ctx->que_idx] = pid;
	p_ctx->que_idx++;
}

void	wait_queue(t_context *p_ctx)
{
	int	idx;
	int	pid_cnt;

	idx = 0;
	pid_cnt = p_ctx->que_idx;
	while (idx < pid_cnt)
	{
		waitpid(p_ctx->queue[idx], get_exit_status(), 0);
		p_ctx->exit_status = *get_exit_status();
		idx++;
		p_ctx->que_idx--;
	}
	if (*get_exit_status() != 0)
		p_ctx->exit_status = 1;
	else
		p_ctx->exit_status = 0;
}
