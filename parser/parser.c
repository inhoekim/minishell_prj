/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasong <dasong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:25:54 by naylee            #+#    #+#             */
/*   Updated: 2023/08/15 14:28:41 by dasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/rule.h"

t_node	*parser(char *line)
 {
	t_node		*root;
	t_tokenizer	tokenizer;

	set_tokenizer(&tokenizer, line);
	if (get_curr_token(&tokenizer)->type == E0F)
		return (NULL);
	root = msh_grammar(&tokenizer);
	if (get_curr_token(&tokenizer)->type != E0F)
	{
		syntax_error("error");
		//free_tree(root);
	}
	free(tokenizer.curr_token);
	return (root);
 }

void	syntax_error(char * str)
{
	return ;
}

void	free_tree(t_node *root)
{
	return ;
}

int	main(void)
{
	t_node *test;
	test = parser("< a.txt > b.txt > c.txt");
	int a = 3;
	a++;
	return (0);
}