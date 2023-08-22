#include <sys/signal.h>
#include <stdio.h>
#include <string.h>
//#include "../include/libft.h"
#include <unistd.h>
#include <signal.h> 

void	ms_signal(int signum, void *handler)
{
	struct sigaction	act;

	act.sa_handler = handler;	// 시그널 핸들러 지정
  	sigemptyset(&act.sa_mask);	// 시그널 처리 중 블록될 시그널은 없음
	sigaction(signum, &act, 0);
}
void	sigint_handler2(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("\n");
    rl_on_new_line();
    rl_replace_line("", 1);
    rl_redisplay();
}
void	sigquit_handler(int signum)
{
	if (signum != SIGQUIT)
		return ;
	printf("Quit: %d\n", signum);
	rl_on_new_line();
    rl_replace_line("", 1);
    rl_redisplay();
}

void	sigact_fork_parent()
{
	ms_signal(SIGINT, SIG_IGN);
	ms_signal(SIGQUIT, SIG_IGN);
}

void sigact_fork_child()
{
	ms_signal(SIGINT, sigint_handler2);
	ms_signal(SIGQUIT, sigquit_handler);
}
