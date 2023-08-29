#include "../include/minishell.h"

void	arg_expansion(t_list *list)
{
	char	*content;

	while (list)
	{
		content = list->content;
		if (content[0] != '\'')
		{
			content = parameter_expansion(list->content);
			free(list->content);
			list->content = content;
		}
		list = list->next;
	}
}
