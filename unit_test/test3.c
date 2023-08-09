#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fd1 = 1;
	int fd2 = open("a.txt", O_CREAT | O_WRONLY, 0644); // 3

	write(fd1, "error\n", 6); // 성공
	printf("first : %d\n", fd2);

	dup2(fd2, fd1);
	write(fd1, "hello\n", 6);
	printf("second : %d\n", fd2);

	close(fd2); // 3
	write(fd1, "haha\n", 6);  // 실패
	printf("Third : %d\n", fd2);
}