#include "../include/minishell.h"
#include "../libft/libft.h"
# define PATH_MAX 1024

// 등록한 환경변수는 쉘이 종료됨에 따라 같이 환경변수에서 삭제되야함
t_bool	ft_export(t_node *node)
{
	char	**temp;
	int		idx;
	t_list	**env;

	temp = node->left->word;
	idx = -1;
	env = get_envp();
	if (!temp[1])
		while ((*env)->next != NULL)
			printf("declare -x %s\n", (*env)->content);
	else
	{
		env = get_envp();
		while (temp[++idx])
			ft_lstadd_back(env, ft_lstnew(ft_strdup(temp[idx])));
		ft_lstadd_back(env, ft_lstnew(NULL));
	}
	return (FALSE);
}

t_bool	ft_unset(t_node *node)
{
	char	**temp;
	int		idx;
	t_list	**env;
	t_list	*check;

	temp = node->left->word;
	idx = -1;
	if (temp[1])
	{
		env = get_envp();
		while (temp[++idx])
		{
			check = *env;
			while (check->next != NULL)
			{
				if (ft_memcmp(temp[idx], check->content, \
				ft_strlen(temp[idx])) == 0)
				{
					delete_node((*env), check);
					break ;
				}
				check = check->next;
			}
		}
	}
	return (FALSE);
}

// 노드 삭제 함수
void	delete_node(t_list **head, t_list *node_to_delete)
{
    t_list	*current;
    t_list	*prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if (current == node_to_delete)
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}