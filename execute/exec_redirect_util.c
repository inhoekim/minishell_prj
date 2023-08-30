/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:11:32 by seykim            #+#    #+#             */
/*   Updated: 2023/08/30 19:11:35 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

t_bool	*get_redirect_ambiguity(void)
{
	static t_bool	redirect_ambiguity;

	return (&redirect_ambiguity);
}

void	set_redirect_ambiguity(t_bool value)
{
	*get_redirect_ambiguity() = value;
}

t_bool	is_regular_file(char *filename, t_context *p_ctx)
{
	struct stat	buff;

	if (access(filename, F_OK) != 0)
	{
		msh_error(filename, NULL, ENOENT);
		p_ctx->exit_status = 127;
		return (FALSE);
	}
	stat(filename, &buff);
	if ((buff.st_mode & S_IFMT) == S_IFDIR)
	{
		msh_error(filename, NULL, EISDIR);
		p_ctx->exit_status = 126;
		return (FALSE);
	}
	return (TRUE);
}

t_bool	is_not_directory(char *filename, t_context *p_ctx)
{
	struct stat	buff;

	stat(filename, &buff);
	if ((buff.st_mode & S_IFMT) == S_IFDIR)
	{
		msh_error(filename, NULL, EISDIR);
		p_ctx->exit_status = 126;
		return (FALSE);
	}
	return (TRUE);
}
