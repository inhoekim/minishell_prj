/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:13:08 by seykim            #+#    #+#             */
/*   Updated: 2023/08/30 19:13:09 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_signal.h"

static void	signal_changer(int signum, void *handler);
static void	fork_mode_handler(int signum);

void	sigact_fork_mode(void)
{
	struct termios	attributes;

	tcgetattr(STDIN, &attributes);
	attributes.c_lflag |= (ECHOCTL);
	tcsetattr(STDIN, TCSANOW, &attributes);
	signal_changer(SIGINT, fork_mode_handler);
	signal_changer(SIGQUIT, fork_mode_handler);
}

void	sigact_modeoff(void)
{
	signal_changer(SIGINT, SIG_DFL);
	signal_changer(SIGQUIT, SIG_DFL);
}

static void	signal_changer(int signum, void *handler)
{
	struct sigaction	act;

	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	sigaction(signum, &act, 0);
}

static void	fork_mode_handler(int signum)
{
	if (signum == SIGINT)
		printf("\n");
	if (signum == SIGQUIT)
		printf("Quit: %d\n", signum);
}
