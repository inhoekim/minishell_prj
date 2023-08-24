#include <stdio.h>
#include <signal.h>
#include <termios.h>
#include "../include/minishell.h"
#include "../include/execute.h"

void	ms_signal(int signum, void *handler)
{
	struct sigaction	act;

	act.sa_handler = handler;	// 시그널 핸들러 지정
  	sigemptyset(&act.sa_mask);	// 시그널 처리 중 블록될 시그널은 없음
	act.sa_flags = SA_RESTART;
	sigaction(signum, &act, 0);
}

void	fork_mode_handler(int signum)
{
	if (signum == SIGINT)
		printf("fork\n");
	if (signum == SIGQUIT)
		printf("Quit: %d\n", signum);
}

void	sigact_fork_mode()
{
	struct termios attributes;

	tcgetattr(STDIN, &attributes);
    attributes.c_lflag |= (ECHOCTL);
	tcsetattr(STDIN, TCSANOW, &attributes);
	ms_signal(SIGINT, fork_mode_handler);
	ms_signal(SIGQUIT, fork_mode_handler);
}



void	sigact_modeoff()
{
	ms_signal(SIGINT, SIG_DFL);
	ms_signal(SIGQUIT, SIG_DFL);
	// @ 좀비 죽이는 로직
	struct sigaction	act;

	act.sa_handler = SIG_IGN;
  	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGCHLD, &act, 0);
}

