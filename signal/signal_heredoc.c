/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:13:10 by seykim            #+#    #+#             */
/*   Updated: 2023/08/30 19:13:11 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_signal.h"

static void	quit_heredoc(int signum);

void	sigact_heredoc_mode(void)
{
	struct sigaction	intsig;
	struct sigaction	quitsig;

	intsig.sa_handler = quit_heredoc;
	sigemptyset(&intsig.sa_mask);
	intsig.sa_flags = SA_RESTART;
	sigaction(SIGINT, &intsig, 0);
	quitsig.sa_handler = SIG_IGN;
	sigemptyset(&quitsig.sa_mask);
	quitsig.sa_flags = 0;
	sigaction(SIGQUIT, &quitsig, 0);
}

static void	quit_heredoc(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("\n");
	set_heredoc_fault_flag(TRUE);
	set_tmp_stdin_fd(dup(STDIN));
	close(STDIN);
}
