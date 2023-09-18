/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:27:23 by seykim            #+#    #+#             */
/*   Updated: 2023/09/18 13:27:24 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"
#include "../include/builtin.h"

static t_bool	check_str(char *argv, int idx, int size, char *sep);

t_builtin	check_builtin(char *argv)
{
	if (argv[0] == 'c' && check_str(argv, 1, 1, "d"))
		return (ft_cd);
	else if (argv[0] == 'e')
	{
		if (argv[1] == 'c' && check_str(argv, 2, 2, "ho"))
			return (ft_echo);
		else if (argv[1] == 'x')
		{
			if (argv[2] == 'p' && check_str(argv, 3, 3, "ort"))
				return (ft_export);
			else if (argv[2] == 'i' && check_str(argv, 3, 1, "t"))
				return (ft_exit);
		}
		else if (argv[1] == 'n' && check_str(argv, 2, 1, "v"))
			return (ft_env);
	}
	else if (argv[0] == 'p' && check_str(argv, 1, 2, "wd"))
		return (ft_pwd);
	else if (argv[0] == 'u' && check_str(argv, 1, 4, "nset"))
		return (ft_unset);
	return (NULL);
}

void	redirect_fd(int dst[2])
{
	dup2(dst[STDIN], STDIN);
	dup2(dst[STDOUT], STDOUT);
}

t_bool	exec_builtin(char **argv, t_context *p_ctx)
{
	t_bool		can_builtin;
	t_builtin	builtin_func;
	int			builtin_exit_status;
	int			tmp_fd[2];

	can_builtin = FALSE;
	builtin_func = check_builtin(argv[0]);
	if (builtin_func)
	{
		if (p_ctx->is_piped_cmd)
			forked_builtin(p_ctx, builtin_func, argv);
		else
		{
			tmp_fd[STDIN] = dup(STDIN);
			tmp_fd[STDOUT] = dup(STDOUT);
			redirect_fd(p_ctx->fd);
			builtin_exit_status = builtin_func(argv);
			redirect_fd(tmp_fd);
			p_ctx->exit_status = builtin_exit_status;
			set_last_exit_status(p_ctx->exit_status);
		}
		can_builtin = TRUE;
	}
	return (can_builtin);
}

static t_bool	check_str(char *argv, int idx, int size, char *sep)
{
	return (ft_memcmp(argv + idx, sep, size + 1) == 0);
}
