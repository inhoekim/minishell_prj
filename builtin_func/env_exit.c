#include "../include/minishell.h"
#include "../libft/libft.h"
#include "../include/execute.h"

t_bool	ft_env(t_node *node)
{
	(void)node;
	t_list	**env;
	t_list	*temp;

	env = get_envp();
	temp = *env;
	while (temp != NULL)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
	return (FALSE);
}

t_bool	ft_exit(t_node *node)
{
	char	**temp;

	temp = node->left->word;
	if (!temp[1])
	{
		if (temp[2])
		{
			printf("exit: Too many arguments\n");
			exit(1);
		}
		exit_utils(temp);
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

void	exit_utils(char **temp)
{
	int	idx;

	idx = 0;
	while (temp[1][idx])
	{
		if (temp[1][idx] == '-' || temp[1][idx] == '+')
			idx++;
		if (ft_isdigit(temp[1][idx]) == 0)
		{
			printf("exit: %s: numeric argument required", temp[1]);
			exit(255);
		}
		idx++;
	}
}