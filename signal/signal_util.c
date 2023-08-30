#include "signal.h"

t_bool	*get_is_subshell(void)
{
	static t_bool	is_subshell;

	return (&is_subshell);
}

void	set_is_subshell(t_bool flag)
{
	*get_is_subshell() = flag;
}
