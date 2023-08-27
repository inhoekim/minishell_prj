#include <stdio.h>
#include <signal.h>
#include <termios.h>
#include "../include/execute.h"
#include "../include/minishell.h"
#include "../include/execute.h"

void	ms_signal(int signum, void *handler)
{
	struct sigaction	act;

	// 시그널 핸들러 지정
	act.sa_handler = handler;	
  	sigemptyset(&act.sa_mask);
	// 시그널 처리 중 블록될 시그널은 없음
	act.sa_flags = SA_RESTART;
	sigaction(signum, &act, 0);
}

