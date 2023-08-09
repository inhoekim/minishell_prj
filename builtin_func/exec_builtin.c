#include "../include/minishell.h"
#include "../libft/libft.h"
# define PATH_MAX 1024

// echo, cd, pwd, export, unset, env, exit
t_bool	ft_echo(t_node *node)
{
	char	**temp;
	int		idx;
	int		flag;

	temp = node->left->word;
	flag = 0;
	if (!temp)
		printf("\n");
	else if (temp[1][0] == '-' && temp[1][1] == 'n')
	{
		idx = 1;
		flag = 1;
	}
	else
		idx = 0;
	while (temp[++idx])
	{
		// 환경변수일 경우, 해당 문자열을 환경변수의 문자열로 변경해줘야함
		if (temp[idx][0] == '$')
		{

		}
		else
		{
			if (temp[idx + 1] != NULL)
				printf("%s ", temp[idx]);
			else
				printf("%s", temp[idx]);
		}
	}
	if (flag == 0)
		printf("\n");
	return (FALSE);
}

t_bool	ft_pwd(t_node *node)
{
	char	*path[PATH_MAX];

	getcwd(path, PATH_MAX);
	printf("%s\n", path);
	return (FALSE);
}

// 환경변수의 PWD에 현재 폴더의 위치가 저장되어있는데, cd 상대경로 or 절대경로일 때, 이 환경변수의 PWD를 변경해줘야함
// 마찬가지로 OLDPWD는 이전의 내용으로 이를 제거해야함
// cd와 export와 unset은 한 세트로, 비슷한 흐름으로 제어되야함 -> 환경변수를 사용하기 때문
t_bool	ft_cd(t_node *node)
{
	char	*path[PATH_MAX];

	// getcwd로 현재 폴더의 경로를 가져옴
	getcwd(path, PATH_MAX);
	// 성공 시, 리턴코드 0 반환
	return (FALSE);
}
