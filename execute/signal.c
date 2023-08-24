#include <stdio.h>
#include <signal.h> 

void	ms_signal(int signum, void *handler)
{
	struct sigaction	act;

	act.sa_handler = handler;	// 시그널 핸들러 지정
  	sigemptyset(&act.sa_mask);	// 시그널 처리 중 블록될 시그널은 없음
	act.sa_flags = SA_RESTART;
	sigaction(signum, &act, 0);
}

void	sigquit_parent(int signum)
{
	if (signum != SIGQUIT)
		return ;
	printf("Quit: %d\n", signum);
}
void	sigact_fork_parent()
{
	ms_signal(SIGINT, SIG_IGN);
	ms_signal(SIGQUIT, sigquit_parent);
}

void sigact_fork_child()
{
	ms_signal(SIGINT, SIG_DFL);
	ms_signal(SIGQUIT, SIG_DFL);
}
