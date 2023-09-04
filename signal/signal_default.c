/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:13:06 by seykim            #+#    #+#             */
/*   Updated: 2023/08/30 19:13:07 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_signal.h"

static void	new_prompt(int signum);

void	sigact_default_mode(void)
{
	struct sigaction	intsig;
	struct sigaction	quitsig;
	struct termios		attributes;

	tcgetattr(STDIN, &attributes);
	attributes.c_lflag &= (~ECHOCTL);
	tcsetattr(STDIN, TCSANOW, &attributes);
	intsig.sa_handler = new_prompt;
	sigemptyset(&intsig.sa_mask);
	intsig.sa_flags = 0;
	sigaction(SIGINT, &intsig, 0);
	quitsig.sa_handler = SIG_IGN;
	sigemptyset(&quitsig.sa_mask);
	quitsig.sa_flags = 0;
	sigaction(SIGQUIT, &quitsig, 0);
}

static void	new_prompt(int signum)
{
	if (signum != SIGINT)
		return ;
	if (!get_heredoc_data()->heredoc_eof_flag)
		printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	set_last_exit_status(1);
}
