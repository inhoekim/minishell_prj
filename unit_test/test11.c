#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv, char **envp) {
    (void)argc;
    (void)argv;
	

    int pid;
	int status;
    char *arr[] = {"/bin/cat", NULL};

    pid = fork();
    if (pid == 0) {
		
		int ret = execve("/bin/fat", arr, envp);
		exit(ret + 128);
		
    }
	waitpid(pid, &status, 0);
	printf("exit status: %d\n", WEXITSTATUS(status));
}
