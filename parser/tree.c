/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:29:32 by seykim            #+#    #+#             */
/*   Updated: 2023/09/18 13:29:33 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static char	**make_word_data(char *src, int len);
static void	free_node(t_node *node);

/* Only WORD type can come to the leaf node */
t_node	*make_leaf(t_tokenizer *tokenizer)
{
	t_node	*node;
	t_token	*token;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		exit(ENOMEM);
	node->type = WORD;
	node->left = NULL;
	node->right = NULL;
	token = tokenizer->curr_token;
	node->word = make_word_data(token->str, token->len);
	get_next_token(tokenizer);
	return (node);
}

/* Create a new tree with the first parameter(node_type) as the parent */
t_node	*make_tree(t_symbol node_type, t_node *left, t_node *right)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->type = node_type;
	node->left = left;
	node->right = right;
	node->word = NULL;
	return (node);
}

/* Initialize the node's word-data variable for the first time */
static char	**make_word_data(char *src, int len)
{
	char	**new_str;
	int		idx;

	new_str = (char **)malloc(sizeof(char *) * 2);
	if (!new_str)
		exit(ENOMEM);
	new_str[0] = (char *)malloc(sizeof(char) * (len + 1));
	if (!(new_str[0]))
		exit(ENOMEM);
	new_str[0][len] = '\0';
	idx = 0;
	while (idx < len)
	{
		new_str[0][idx] = src[idx];
		idx++;
	}
	new_str[1] = NULL;
	return (new_str);
}

void	free_tree(t_node *root)
{
	t_node	*node_left;
	t_node	*node_right;

	node_left = NULL;
	node_right = NULL;
	if (root)
	{
		node_left = root->left;
		node_right = root->right;
		free_node(root);
		free_tree(node_left);
		free_tree(node_right);
	}
}

static void	free_node(t_node *node)
{	
	int	idx;

	idx = -1;
	if (node)
	{
		while (node->word && (node->word)[++idx])
			free((node->word)[idx]);
		free(node->word);
		free(node);
	}
}
