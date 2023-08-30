/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:11:45 by seykim            #+#    #+#             */
/*   Updated: 2023/08/30 19:12:00 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	cir_lstadd(pid_t pid, t_context *p_ctx);

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
	cir_lstadd(pid, p_ctx);
}

void	msh_error(char *name, char *msg, int error)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (msg == NULL && error == 0)
	{
		perror(name);
		return ;
	}
	if (name)
	{
		ft_putstr_fd(name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	else if (error)
		ft_putendl_fd(strerror(error), STDERR_FILENO);
}
