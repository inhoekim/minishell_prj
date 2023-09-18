/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_static.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:28:26 by seykim            #+#    #+#             */
/*   Updated: 2023/09/18 13:28:28 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	set_tmp_stdin_fd(int fd)
{
	get_heredoc_data()->temp_stdin_fd = fd;
}
