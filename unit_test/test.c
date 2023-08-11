#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/libft.h"
#define PATH_MAX 1024
void	set_envp(char *pos, char *pwd);
void	init_envp(char **envp);
t_list	**get_envp(void);
t_list	*getenv_list(char *pos, size_t pos_len, t_list **env);
void	ft_env(void);

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
	t_list	**env;
	size_t	pos_len;
	(void)pwd;
	pos_len = ft_strlen(pos);
	temp = getenv_list(pos, pos_len, get_envp());
	env = 0;
	// 없을 경우 추가
	if (!temp)
		ft_lstadd_back(get_envp(), temp);
	// 있을 경우 삭제, 프리 하고 추가
	// else
	// {
	// 	*env = getenv_list(pwd, ft_strlen(pwd), get_envp());
		// free((*env)->content);
	// 	(*env)->content = ft_strdup(pwd);
	// }
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

void	ft_env(void)
{
	int	idx;
	t_list	**env;
	t_list	*temp;

	idx = 0;
	env = get_envp();
	temp = *env;
	while (temp->next != NULL)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char *test = "test99";
	char	*newpwd;
	char	path[PATH_MAX];

	init_envp(envp);
	// ft_env();
	if (chdir(test) != 0)
	{
		printf("error");
		exit(1);
	}
	// set_envp("OLDPWD", 0);
	newpwd = getcwd(path, PATH_MAX);
	// set_envp("PWD", newpwd);
	// printf("new PWD");
	// ft_env();
}