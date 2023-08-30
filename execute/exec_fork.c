/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:11:29 by seykim            #+#    #+#             */
/*   Updated: 2023/08/30 19:11:30 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

static void	order_check(char **argv, t_context *p_ctx, char *temp_path);

void	search_and_fork_exec(char **argv, t_context *p_ctx)
{
	char	*temp_path;

	temp_path = ft_getenv("PATH");
	if (!temp_path)
	{
		msh_error(argv[0], "command not found", 0);
		p_ctx->exit_status = 127;
		fork_error(p_ctx);
		return ;
	}
	order_check(argv, p_ctx, temp_path);
	free(temp_path);
}

static void	order_check(char **argv, t_context *p_ctx, char *temp_path)
{
	char	*order;
	char	**path;

	path = path_split(temp_path, ':');
	order = make_order(path, argv);
	if (order)
	{
		free(argv[0]);
		argv[0] = order;
		fork_exec(argv, p_ctx);
	}
	else
	{
		if (p_ctx->fd[STDIN] != STDIN)
			close(p_ctx->fd[STDIN]);
		if (p_ctx->fd[STDOUT] != STDOUT)
			close(p_ctx->fd[STDOUT]);
		msh_error(argv[0], "command not found", 0);
		p_ctx->exit_status = 127;
		fork_error(p_ctx);
	}
	free_argv(path);
}

char	*make_order(char **path, char **argv)
{
	struct stat	buff;
	int			idx;
	char		*order;

	idx = 0;
	order = NULL;
	while (path[idx])
	{
		order = ft_strjoin(path[idx], argv[0]);
		stat(order, &buff);
		if (access(order, X_OK) == 0 && (buff.st_mode & S_IFMT) != S_IFDIR)
			return (order);
		free(order);
		idx++;
	}
	return (NULL);
}

void	forked_builtin(t_context *p_ctx, t_builtin	builtin_func, char **argv)
{
	int		pid;
	int		builtin_exit_status;

	if (!*get_is_subshell())
		sigact_fork_mode();
	pid = fork();
	if (pid == 0)
	{
		sigact_modeoff();
		dup2(p_ctx->fd[STDIN], STDIN);
		dup2(p_ctx->fd[STDOUT], STDOUT);
		if (p_ctx->fd_close >= 0)
		{
			close(p_ctx->fd_close);
			p_ctx->fd_close = -1;
		}
		builtin_exit_status = builtin_func(argv);
		exit(builtin_exit_status);
	}
	if (p_ctx->fd[STDIN] != STDIN)
		close(p_ctx->fd[STDIN]);
	if (p_ctx->fd[STDOUT] != STDOUT)
		close(p_ctx->fd[STDOUT]);
	cir_lstadd(pid, p_ctx);
}
