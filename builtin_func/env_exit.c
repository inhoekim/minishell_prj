#include "../include/minishell.h"
#include "../libft/libft.h"
# define PATH_MAX 1024

// 환경변수를 어디선가 끌고와야함
t_bool	ft_env(t_node *node)
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
	return (FALSE);
}

t_bool	ft_exit(t_node *node)
{
	char	**temp;
	int		idx;

	temp = node->left->word;
	if (!temp[1])
	{
		idx = 0;
		while (temp[1][idx])
		{
			if (ft_isdigit(temp[1][idx]) == 0)
			{
				printf("exit: %s: numeric argument required", temp[1]);
				exit(255);
			}
			idx++;
		}
		printf("exit\n");
		exit(ft_atoi(temp[1]));
	}
	else
	{
		printf("exit\n");
		exit(0);
	}
	return (TRUE);
}