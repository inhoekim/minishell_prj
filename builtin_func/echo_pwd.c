#include "../include/minishell.h"
#include "../libft/libft.h"
#include "../include/execute.h"

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
