

#define PATH_MAX 4096
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"
// #include "../include/minishellminishell.h"
void	init_envp(char **envp);
void	ft_env(void);
t_list	**get_envp(void);
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

t_list	**get_envp(void)
{
	static t_list	*env_list;

	return (&env_list);
}

int main(int argc, char **argv, char **envp) 
{
//   char path[PATH_MAX];
	(void)argc;
	(void)argv;
	t_list	**temp;

	init_envp(envp);
	temp = get_envp();
	ft_env();
	printf("Asd\n");
	ft_env();

//   getcwd(path, PATH_MAX);
// //   printf("Current Directory: %s\n", path) ;
//   int idx = 0;
//   while (envp[idx])
//   {
// 	printf("%s\n", envp[idx]);
// 	idx++;
//   }
	// char *aaa = "temp";
	// char	*temp = "123";
	// printf("%d\n", ft_atoi(aaa));
  return 0 ;
}