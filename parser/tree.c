/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhkim <inhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 07:46:37 by inhkim            #+#    #+#             */
/*   Updated: 2023/08/14 08:06:52 by inhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/tokenizer.h"

<<<<<<< HEAD
static char	**make_first_word(char *src, int len);
=======
static char	**make_node_word(char *src, int len);
>>>>>>> 240_develop

t_node	*make_leaf(t_tokenizer *tokenizer)
{
	t_node	*node;
	t_token	*token;

<<<<<<< HEAD
	node = (t_node *)malloc(sizeof(t_node));
=======
	node = (t_node *)malloc(sizeof(node));
>>>>>>> 240_develop
	node->type = WORD;
	node->left = NULL;
	node->right = NULL;
	token = tokenizer->curr_token;
	node->word = make_first_word(token->str, token->len);
<<<<<<< HEAD
	get_next_token(tokenizer);
=======
>>>>>>> 240_develop
	return (node);
}

t_node	*make_tree(t_symbol node_type, t_node *left, t_node *right)
{
	t_node	*node;

<<<<<<< HEAD
	node = (t_node *)malloc(sizeof(t_node));
=======
	node = (t_node *)malloc(sizeof(node));
>>>>>>> 240_develop
	node->type = node_type;
	node->left = left;
	node->right = right;
	node->word = NULL;
	return (node);
}

static char	**make_first_word(char *src, int len)
{
	char	**new_str;
	int		idx;

	new_str = (char **)malloc(sizeof(char *) * 2);
	new_str[0] = (char *)malloc(sizeof(char) * (len + 1));
	idx = 0;
	while (idx < len)
	{
		new_str[0][idx] = src[idx];
		idx++;
	}
	new_str[0][len] = '\0';
	new_str[1] = NULL;
	return (new_str);
}
