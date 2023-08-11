/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naylee <naylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:25:54 by naylee            #+#    #+#             */
/*   Updated: 2023/08/11 11:25:54 by naylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/tokenizer.h"

t_node	*parser(t_tokenizer *line)
 {
	t_node		*node;
	t_node 		*root;
	t_tokenizer	*tokenizer;

	tokenizer = set_tokenizer(line);
	get_next_token(tokenizer); //최초 1회, 첫 토큰 가리킴
 	while (tokenizer->type != E0F)
	{
		node = msh_grammer(tokenizer);
		if (!root) //head 노드를 root에 저장
			root = node;
		get_next_token(tokenizer);
		//make_tree
		//tree로 계속 붙이는 과정
	}
	return (root);
 }

