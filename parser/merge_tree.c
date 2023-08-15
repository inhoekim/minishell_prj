#include "../include/minishell.h"
#include "../include/tokenizer.h"

t_node	*merge_tree(t_node *parent, t_node *child)
{
	if (!child)
		return (parent);
	if (!parent)
		return (child);
	if (parent && child)
		return (insert_left(parent, child));
	return (NULL);
}

static t_node	*insert_left(t_node *parent, t_node *child)
{
	t_node	*dock_node;
	
	dock_node = parent;
	while (dock_node->left)
		dock_node = dock_node->left;
	if (dock_node->type == COMMAND && child->type == COMMAND)
	{
		dock_node->word = append_cmd(child, dock_node->word);
		return (parent);
	}
	dock_node->left = child;
	return (parent);
}