#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
int main() {
	// int fd = open("a.txt", O_CREAT|O_WRONLY, 0644);
	// close(fd);
	char *arr = (char *)malloc(sizeof(char) * 2147483649);
	memset(arr, 1, sizeof(arr) - 1);
	// arr[2147483648] = 0;
	// close(fd);
	
	// return (write(1, arr, 2147483649));
	return (write(1, arr, -1));
}