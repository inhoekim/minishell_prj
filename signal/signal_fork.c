#include <signal.h>
#include <termios.h>
#include "../include/here_doc.h"
#include "../include/execute_util.h"

static void	signal_changer(int signum, void *handler);
static void	fork_mode_handler(int signum);

void	sigact_fork_mode(void)
{
	struct termios	attributes;

	tcgetattr(STDIN, &attributes);
	attributes.c_lflag |= (ECHOCTL);
	tcsetattr(STDIN, TCSANOW, &attributes);
	signal_changer(SIGINT, fork_mode_handler);
	signal_changer(SIGQUIT, fork_mode_handler);
}

t_bool	*get_is_subshell(void)
{
	static t_bool	is_subshell;

	return (&is_subshell);
}

void	set_is_subshell(t_bool flag)
{
	*get_is_subshell() = flag;
}

void	sigact_modeoff(void)
{
	signal_changer(SIGINT, SIG_DFL);
	signal_changer(SIGQUIT, SIG_DFL);
}

static void	signal_changer(int signum, void *handler)
{
	struct sigaction	act;

	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	sigaction(signum, &act, 0);
}

static void	fork_mode_handler(int signum)
{
	if (signum == SIGINT)
		printf("\n");
	if (signum == SIGQUIT)
		printf("Quit: %d\n", signum);
}

// void zobmie_handler(int signum)
// {
// 	pid_t pid;

// 	if (signum != SIGCHLD)
// 		return ;
// 	pid = wait(0);
// 	printf("%d terminated.\n", pid);

// }
// void	sigact_zobmie_setmode(void)
// {
// 	signal_changer(SIGCHLD, zobmie_handler);
// }