#include "../include/minishell.h"
#include "../libft/libft.h"
# define PATH_MAX 1024

// echo, cd, pwd, export, unset, env, exit
t_bool	ft_echo(t_node *node)
{
	char	**temp;
	int		idx;
	int		flag;

	temp = node->right->word;
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
		if (temp[idx + 1] != NULL)
			printf("%s ", temp[idx]);
		else
			printf("%s", temp[idx]);
	}
	if (flag == 0)
		printf("\n");
	return (FALSE);
}

t_bool	ft_pwd(t_node *node)
{
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	printf("%s\n", path);
	return (FALSE);
}

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
	char	*oldpwd;
	char	*newpwd;
	char	**temp;

	temp = node->left->word;
	can_env = vaild_env(temp);
	if (!can_env)
	{
		printf("cd: Too many arguments\n");
		return (TRUE);
	}
	if (chdir(can_env) != 0)
	{
		printf("cd : No such file or directory");
		return (TRUE);
	}
	// getcwd로 현재 폴더의 경로를 가져옴
	set_envp("OLDPWD", 0);
	newpwd = getcwd(path, PATH_MAX);
	set_envp("PWD", newpwd);
	// 성공 시, 리턴코드 0 반환
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
	//HOME 디렉토리 반환
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
	//HOME 디렉토리 반환
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

char	*getenv(char *pos)
{
	size_t	pos_len;
	t_list	*cur_env;
	char	*temp;

	pos_len = ft_strlen(pos);
	cur_env = getenv_list(pos, pos_len, get_envp());
	if (cur_env)
	{
		temp = ft_strdup((char *)cur_env->content);
		return (temp + pos_len + 1);
	}
	return (NULL);
}

t_list	*getenv_list(char *pos, size_t pos_len, t_list **env)
{
	t_list	*temp;
	t_list	*prev;
	char	*var;

	temp = *env;
	while (temp != NULL)
	{
		var = temp->content;
		if (ft_strncmp((char *)temp->content, pos, pos_len) == 0)
		{
			if (var[pos_len] == '=')
				return (temp);
		}
		prev = temp;
		temp = temp->next;
	}
	return (NULL);
}

void	set_envp(char *pos, char *pwd)
{
	t_list	*temp;
	t_list	**env;
	size_t	pos_len;

	pos_len = ft_strlen(pos);
	temp = getenv_list(pos, pos_len, get_envp());
	env = 0;
	// 없을 경우 추가
	if (!temp)
		ft_lstadd_back(get_envp(), temp);
	// 있을 경우 삭제, 프리 하고 추가
	else
	{
		*env = getenv_list(pwd, ft_strlen(pwd), get_envp());
		free((*env)->content);
		(*env)->content = ft_strdup(pwd);
	}
}