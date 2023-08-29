#include "../include/minishell.h"

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	if (argv == NULL)
		return ;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

void	set_exit_status(int exit_status)
{
	int	*p_exit_status;

	p_exit_status = get_exit_status();
	*p_exit_status = exit_status;
}

int	*get_exit_status(void)
{
	static int	exit_status;

	return (&exit_status);
}

void	fork_error(t_context *p_ctx)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		exit(p_ctx->exit_status);
	enqueue_after(pid, p_ctx);
}
