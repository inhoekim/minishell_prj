#include "../include/minishell.h"
#include "../include/execute_util.h"

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
