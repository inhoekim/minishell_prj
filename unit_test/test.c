#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/minishelllibft.h"
#define PATH_MAX 1024
void	set_envp(char *pos, char *pwd);
void	init_envp(char **envp);
t_list	**get_envp(void);
t_list	*getenv_list(char *pos, size_t pos_len, t_list **env);
void	ft_env(void);
char	*ft_strnjoin(char const *s1, char const *s2);

char	*ft_strnjoin(char const *s1, char const *s2)
{
	int		total;
	char	*res;
	int		i;

	if (!s1 || !s2)
		return (0);
	total = ft_strlen(s1) + ft_strlen(s2) + 2;
	res = (char *)malloc(sizeof(char) * total);
	if (!res)
		return (0);
	res[total - 1] = '\0';
	i = 0;
	while (*s1)
	{
		res[i] = *s1;
		s1++;
		i++;
	}
	res[i] = '=';
	while (*s2)
	{
		res[++i] = *s2;
		s2++;
	}
	return (res);
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
	ft_lstadd_back(env, ft_lstnew(NULL));
}

t_list	**get_envp(void)
{
	static t_list	*env_list;

	return (&env_list);
}

void	set_envp(char *pos, char *pwd)
{
	t_list	*temp;
	size_t	pos_len;
	char	*newpwd;

	pos_len = ft_strlen(pos);
	temp = getenv_list(pos, pos_len, get_envp());
	if (!temp)
	{
		newpwd = ft_strnjoin(pos, pwd);
		ft_lstadd_back(get_envp(), ft_lstnew(newpwd));
		free(newpwd);
	}
	else
	{
		newpwd = ft_strnjoin(pos, pwd);
		free(temp->content);
		temp->content = ft_strdup(newpwd);
		free(newpwd);
	}
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
		if (ft_strncmp(var, pos, pos_len) == 0)
		{
			if (var[pos_len] == '=')
				return (temp);
		}
		prev = temp;
		temp = temp->next;
	}
	return (NULL);
}

void	ft_env(void)
{
	int	idx;
	t_list	**env;
	t_list	*temp;

	idx = 0;
	env = get_envp();
	temp = *env;
	// while (temp->next != 0)
	// {
	// 	printf("%s\n", temp->content);
	// 	temp = temp->next;
	// }
}

char	**list_to_arr(t_list *node)
{
	char	**arr;
	int		i;
	int		len;

	i = 0;
	len = ft_lstsize(node);
	arr = malloc(sizeof(t_list) * (len + 1));
	arr[len] = NULL;
	while (node)
	{
		arr[i++] = node->content;
		node = node->next;
	}
	return (arr);
}


int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char *test = "test99";
	char	*newpwd;
	char	path[PATH_MAX];
	t_list	**list;
	char	**temp_envp;
	char *ls[] = {"/bin/ls", "-al", NULL};

	init_envp(envp);
	// ft_env();
	newpwd = getcwd(path, PATH_MAX);
	if (chdir(test) != 0)
	{
		printf("error");
		exit(1);
	}
	set_envp("OLDPWD", newpwd); // 새로 추가되는 파트
	newpwd = getcwd(path, PATH_MAX);
	set_envp("PWD", newpwd); // 수정파트 -> 동작O
	ft_env(); // -> PWD가 갱신된것을 확인 / OLDPWD가 없음 -> 추가 -> (NULL)
	list = get_envp();
	temp_envp = list_to_arr(*list);
	execve("/bin/ls", ls, temp_envp);
}