/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhkim <inhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 07:46:28 by inhkim            #+#    #+#             */
/*   Updated: 2023/08/18 12:32:04 by inhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/tokenizer.h"

static t_node	*insert_left(t_node *parent, t_node *child);
static char		**append_cmd(char **front, char **back);
static int		get_wrapper_len(char **str, char **str2);
static int		str_copy(char **dest, char *src);

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
		dock_node->word = append_cmd(child->word, dock_node->word);
		return (parent);
	}
	dock_node->left = child;
	return (parent);
}

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

static int	get_wrapper_len(char **str, char **str2)
{
	int	idx;
	int	ret;

	idx = -1;
	ret = 0;
	while (str[++idx])
		ret++;
	idx = -1;
	while (str2[++idx])
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
