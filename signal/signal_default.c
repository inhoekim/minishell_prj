#include <signal.h>
#include <termios.h>
#include "../include/here_doc.h"
#include "../include/execute_util.h"

static void	new_prompt(int signum);

// @ sigaction set(default mode)
// @(구현o) sigint(2) 	컨트롤+c -> 개행후 새로운 프롬프트 출력
// @(구현o) sigquit(3) 컨트롤+\ -> 아무동작안함 (무시)
// @(구현o) eof 		컨트롤+ d -> minishell 종료 
void	sigact_default_mode(void)
{
	struct sigaction	intsig;
	struct sigaction	quitsig;
	struct termios		attributes;

	tcgetattr(STDIN, &attributes);
	attributes.c_lflag &= (~ECHOCTL);
	tcsetattr(STDIN, TCSANOW, &attributes);

	intsig.sa_handler = new_prompt;
	sigemptyset(&intsig.sa_mask);
	intsig.sa_flags = 0;
	sigaction(SIGINT, &intsig, 0);
	quitsig.sa_handler = SIG_IGN;
	sigemptyset(&quitsig.sa_mask);
	quitsig.sa_flags = 0;
	sigaction(SIGQUIT, &quitsig, 0);
}

static void	new_prompt(int signum)
{
	if (signum != SIGINT)
		return ;
	if (!get_heredoc_data()->heredoc_eof_flag)
		printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	set_last_exit_status(1);
}
