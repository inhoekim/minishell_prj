#include <sys/signal.h>
#include <stdio.h>
#include <string.h>
//#include "../include/libft.h"
#include <unistd.h>
#include <signal.h>

void	signal(int signum, void *handler)
{
	struct sigaction	act;

	act.sa_handler = handler;	// 시그널 핸들러 지정
  	sigemptyset(&act.sa_mask);	// 시그널 처리 중 블록될 시그널은 없음
	sigaction(signum, &act, 0);
}

void	sigact_fork()
{
	
}
