#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <sys/wait.h>

void	ft_putendl_fd(char *s, int fd);
size_t	ft_strlen(const char *s);

int main(int argc, char **argv, char **envp) {
    (void)argc;
    (void)argv;
	
	// char buffer[30];
	char *input;

    int pid;
    int fd;
    char *arr[] = {"/bin/cat", NULL};

    pid = fork();
    if (pid == 0) {
		execve("/bin/cat", arr, envp);
		printf("This line will not be printed.\n");
    }
    else {
		pid = fork();
		if (pid == 0) {
			fd = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			while (1) {
				// read(0, buffer, 1);            
				// write(fd, buffer, 1);
				
				input = readline("> ");
				ft_putendl_fd(input, fd);
			}
		}
		int	wstatus;
        // heredoc_parent_sighandler();
		waitpid(pid, &wstatus, 0);
		// wait_user_signals();
    }
}

void	ft_putendl_fd(char *s, int fd)
{
	size_t	len;

	len = ft_strlen(s);
	(void)!write(fd, s, len);
	(void)!write(fd, "\n", 1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
