#include <stdio.h>
#include "../include/minishelllibft.h"
#include <unistd.h>
#include <fcntl.h>

int main() {

	// int pid;
	int pipe_fd[2];
	char buffer[1024];

	pipe(pipe_fd);
	write(pipe_fd[1], "123", 3);
	read(pipe_fd[0], buffer, 3);
	printf("%s\n", buffer);
	// int fd1 = open("a.txt", O_WRONLY | O_APPEND, 0644);
	// printf("fd: %d\n", fd1);
	// // int fd2 = open("a.txt", O_WRONLY | O_APPEND, 0644);
	
	// pid = fork();
	// if(pid == 0) {
	// 	// fd1/
	// 	// close(fd1);
	// 	exit(0);
	// }
	// close(fd1); // 여기서 close했지만 a.txt은 사라지지 않는지 확인하고 싶음
	// printf("fd: %d\n", fd1);
	// // sleep(1);

	// // 부모에서 fd1을 close했으니까 a.txt에 더이상 접근못하는게 맞는거같음.
	// write(fd1, "hello\n", 6); 	
	// // 그럼 어떻게 a.txt이 사라지지 않았는지 확인하지? 
	// // access를 쓰면 되지만 생각해보니까 pipe랑 a.txt는 다를거같다

	// // unlink(fd1);
	return 0;
}
