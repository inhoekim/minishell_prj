#include <stdio.h>
#include <string.h>
#include "../include/minishelllibft.h"
#include <unistd.h>
#include <signal.h>


void sigint_handler()
{
   close(0);
}

int main() {

	char buff[123];
	memset(buff, 0, sizeof(buff));
	struct sigaction act_new;

	act_new.sa_handler = sigint_handler; // 시그널 핸들러 지정
  	sigemptyset( &act_new.sa_mask);      // 시그널 처리 중 블록될 시그널은 없음

	sigaction(3, &act_new, 0);
	read(0, buff, 12);

	while(1) {
		sleep(1);
		printf("sleep..\n");
	}
	// printf("%s", buff);
	return 0;
}
