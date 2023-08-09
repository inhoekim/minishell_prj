#include <stdio.h>
#include <unistd.h>
int			pid;
int main(void)
{
	int			pid;

    pid = fork();
	if(!pid) {
		printf("%d\n", pid);
		sleep(30);
	}

}