/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:29:20 by seykim            #+#    #+#             */
/*   Updated: 2023/09/18 13:29:21 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static t_node	*insert_left(t_node *parent, t_node *child);
static char		**append_cmd(char **front, char **back);
static int		get_wrapper_len(char **str, char **str2);
static int		str_copy(char **dest, char *src);

/* The child is joined to the left branch of the parent */
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

/* The child is joined to the left branch of the parent */
/* If both nodes are WORD type, they merge into one array */
static t_node	*insert_left(t_node *parent, t_node *child)
{
	t_node	*dock_node;

	dock_node = parent;
	while (dock_node->left)
		dock_node = dock_node->left;
	if (dock_node->type == COMMAND && child->type == COMMAND)
	{
		dock_node->word = append_cmd(child->word, dock_node->word);
		free(child);
		return (parent);
	}
	dock_node->left = child;
	return (parent);
}

/* It combines two-dimensional arrangements into one */
static char	**append_cmd(char **front, char **back)
{
	char	**new_str;
	int		wrapper_len;
	int		idx;
	int		i;

	wrapper_len = get_wrapper_len(front, back);
	new_str = (char **)malloc(sizeof(char *) * (wrapper_len + 1));
	if (new_str == NULL)
		exit(1);
	new_str[wrapper_len] = NULL;
	idx = -1;
	i = -1;
	while (front[++i])
		if (!str_copy(&(new_str[++idx]), front[i]))
			exit(1);
	i = -1;
	while (back[++i])
		if (!str_copy(&(new_str[++idx]), back[i]))
			exit(1);
	free(front);
	free(back);
	return (new_str);
}

/* Count the size of a two-dimensional array */
static int	get_wrapper_len(char **arr, char **arr2)
{
	int	idx;
	int	ret;

	idx = -1;
	ret = 0;
	while (arr[++idx])
		ret++;
	idx = -1;
	while (arr2[++idx])
		ret++;
	return (ret);
}

static	int	str_copy(char **dest, char *src)
{
	long long	len;
	int			i;

	len = (int)ft_strlen(src);
	*dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (FALSE);
	(*dest)[len] = '\0';
	i = -1;
	while (++i < len)
		(*dest)[i] = src[i];
	free(src);
	return (TRUE);
}
