#include "../include/grammar.h"

t_heredoc_data	*get_heredoc_data(void)
{
	static t_heredoc_data	data;

	return (&data);
}

void	set_heredoc_fault_flag(int flag)
{
	get_heredoc_data()->heredoc_fault_flag = flag;
}

void	set_heredoc_eof_flag(int flag)
{
	get_heredoc_data()->heredoc_eof_flag = flag;
}
