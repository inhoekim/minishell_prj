#include "../include/execute.h"
#include <errno.h>

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
