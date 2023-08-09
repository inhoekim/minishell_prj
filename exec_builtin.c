#include "minishell.h"
# define PATH_MAX 1024
// echo, cd, pwd, export, unset, env, exit
t_bool	ft_echo(t_node *node)
{
	char	**temp;
	int		idx;

	// 트리의 왼쪽가지에 2차원배열로 값이 들어가있어야함
	temp = node->left->word.buf;
	if (!temp)
		printf("\n");
	// 2차원배열에서 idx가 1인 이유
	// echo / ~~~~ 이런식으로 저장이 되어있다고 가정할 경우, 뒤의 문자열들만 출력을 해야함
	if (temp[1][0] == '-' && temp[1][1] == 'n')
	{
		idx = 1;
		while (temp[++idx])
			printf("%s", temp[idx]);
	}
	else
	{
		idx = 0;
		while (temp[++idx])
			printf("%s\n", temp[idx]);
	}
	// 성공 시, 리턴코드 0 반환
	return (FALSE);
}

// 환경변수의 PWD에 현재 폴더의 위치가 저장되어있는데, cd 상대경로 or 절대경로일 때, 이 환경변수의 PWD를 변경해줘야함
t_bool	ft_cd(t_node *node)
{
	char	*path[PATH_MAX];

	// getcwd로 현재 폴더의 경로를 가져옴
	getcwd(path, PATH_MAX);
	// 성공 시, 리턴코드 0 반환
	return (FALSE);
}

t_bool	ft_pwd(t_node *node)
{
	char	*path[PATH_MAX];

	getcwd(path, PATH_MAX);
	printf("%s\n", path);
	// 성공 시, 리턴코드 0 반환
	return (FALSE);
}

t_bool	ft_export(t_node *node)
{
	// 성공 시, 리턴코드 0 반환
	return (FALSE);
}

t_bool	ft_unset(t_node *node)
{
	// 성공 시, 리턴코드 0 반환
	return (FALSE);
}

// 환경변수를 어디선가 끌고와야함
t_bool	ft_env(t_node *node, char **envp)
{
	int	idx;

	idx = 0;
	while (envp[idx])
	{
		printf("%s\n", envp[idx]);
		idx++;
	}
	// 성공 시, 리턴코드 0 반환
	return (FALSE);
}

t_bool	ft_exit(t_node *node)
{
	char	**temp;

	// 트리의 왼쪽가지에 2차원배열로 값이 들어가있어야함
	temp = node->left->word.buf;
	if (!temp[1])
	{
		printf("exit");
		exit(ft_atoi(temp[1]));
	}
	else
	{
		printf("exit");
		exit(0);
	}
	// 실패 시, 리턴코드 1반환
	return (TRUE);
}