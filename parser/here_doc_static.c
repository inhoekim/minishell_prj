#include "here_doc.h"

t_heredoc_data	*get_heredoc_data(void)
{
	static t_heredoc_data	data;

	return (&data);
}

void	set_heredoc_fault_flag(int flag)
{
	get_heredoc_data()->heredoc_fault_flag = flag;
}

void	set_heredoc_visit_flag(int flag)
{
	get_heredoc_data()->heredoc_visit_flag = flag;
}

void	set_tmp_stdin_fd(int fd)
{
	get_heredoc_data()->temp_stdin_fd = fd;
}
