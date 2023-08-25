#include <stdio.h>
#include "../libft/libft.h"
#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/execute.h"
#include "../include/execute_util.h"
#include "../include/here_doc.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	// init_paser();
	// envp -> env_list
	init_envp(envp);
	minishell_loop();
	// free_parser();
	// free_tree();
	// set_exit_status();
}
void	init_envp(char **envp)
{
	t_list	**env;
	int		idx;

	env = get_envp();
	idx = 0;
	ft_lstadd_back(env, NULL);
	while (envp[idx])
	{
		ft_lstadd_back(env, ft_lstnew(ft_strdup(envp[idx])));
		idx++;
	}
}

t_list	**get_envp(void)
{
	static t_list	*env_list;

	return (&env_list);
}

void	new_prompt(int signum)
{
	if (signum != SIGINT)
		return ;
	// if (!*get_heredoc_exit_flag())
		// printf("\n");
	printf("default\n");
	rl_on_new_line(); 
    rl_replace_line("", 1);
    rl_redisplay();
	set_last_exit_status(1);
}

// @ sigaction set(default mode)
// @(구현o) sigint(2) 	컨트롤+c -> 개행후 새로운 프롬프트 출력
// @(구현o) sigquit(3) 컨트롤+\ -> 아무동작안함 (무시)
// @(구현o) eof 		컨트롤+ d -> minishell 종료 
void	sigact_default_mode(void)
{
	struct sigaction	intsig;
	struct sigaction	quitsig;

	struct termios attributes;

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

void	minishell_loop(void) 
{
	t_node		*root;
	char		*line;

	sigact_default_mode();
	line = ft_strdup("");
	while (line)
	{
		line = readline("prompt> ");
		// ctrl+d(eof trigger)시 if 블록 pass
		if (line)
		{
			// 히스토리 기록 -> readline의 함수
			if (*line != '\0')
				add_history(line);
			// parser를 통해 트리생성
			root = parser(line);
			// 생성된 트리를 재귀를 통해서 execve함수 호출 && type bool로 exit의 입력여부 판단
			execute(root);
 			// exit입력 시 종료, 아니면 while문을 통해 입력 대기상태 돌입
			free(line);
		}
	}
	ft_putstr_fd("\033[1A", STDOUT);
	ft_putstr_fd("\033[8C", STDOUT);
	printf("exit\n");
}
