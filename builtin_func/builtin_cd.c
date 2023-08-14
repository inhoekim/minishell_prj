#include "../include/minishell.h"
#include "../libft/libft.h"
# define PATH_MAX 1024

// 환경변수의 PWD에 현재 폴더의 위치가 저장되어있는데, cd 상대경로 or 절대경로일 때, 이 환경변수의 PWD를 변경해줘야함
// 상대경로 -> 현재위치에서 바로 접근이 가능한 경로
// 절대경로 -> /USER/DESKTOP 처럼 정확하게 어떠한 경로가 주어질경우
// 마찬가지로 OLDPWD는 이전의 내용으로 이를 수정(추가)
// 에러문구 : No such file or directory / Not a directory
// ~ 의 경우 환경변수 HOME으로 치환
// cd의 가장 마지막 위치는 '/' 의 위치로 이 이상으로는 아무 변화 없음
t_bool	ft_cd(t_node *node)
{
	char	path[PATH_MAX];
	t_list	**env;
	char	*can_env;
	char	*newpwd;
	char	**temp;

	temp = node->left->word;
	can_env = vaild_env(temp);
	if (!can_env)
	{
		printf("cd: Too many arguments\n");
		return (TRUE);
	}
	newpwd = getcwd(path, PATH_MAX);
	if (chdir(can_env) != 0)
	{
		printf("cd : No such file or directory");
		return (TRUE);
	}
	set_envp("OLDPWD", newpwd);
	newpwd = getcwd(path, PATH_MAX);
	set_envp("PWD", newpwd);
	return (FALSE);
}

char	*vaild_env(char **temp)
{
	int		size;
	char	*parameter;

	size = 0;
	parameter = 0;
	while (temp[size])
		size++;
	if (size > 2)
		return (NULL);
	else if (size == 1)
		return (getenv("HOME"));
	parameter = special_case(temp);
	if (!parameter)
		parameter = temp[1];
	return (parameter);
}

char	*special_case(char **temp)
{
	size_t	temp_len;
	char	*parameter;
	char	path[PATH_MAX];

	temp_len = ft_strlen(temp[1]);
	parameter = 0;
	if (temp_len == 1 && ft_strncmp(temp[1], "~", 1) == 0)
		parameter =	getenv("HOME");
	else if (temp_len == 1 && ft_strncmp(temp[1], ".", 1) == 0)
	{
		getcwd(path, PATH_MAX);
		return (path);
	}
	else if (temp_len == 2 && ft_strncmp(temp[1], "..", 2) == 0)
		parameter = "..";
	return (parameter);
}

