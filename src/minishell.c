#include <stdio.h>
#include "../libft/libft.h"
#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/execute.h"


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

void	init_parser()
{

}

void	minishell_loop(void) 
{
	t_node		*root;
	char		*line;

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
	ft_putstr_fd("\x1b[1A", STDOUT);
	ft_putstr_fd("\033[8C", STDOUT);
	printf("exit\n");
}
