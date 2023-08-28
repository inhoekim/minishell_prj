/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhkim <inhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:33:04 by inhkim            #+#    #+#             */
/*   Updated: 2023/08/25 18:44:00 by inhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

t_node	*parser(char *line);
t_bool	check_first_set(t_nonterminal idx, t_symbol curr_token);
void	free_tree(t_node *root);
void	syntax_error(t_tokenizer *tokenizer);
void	free_tree(t_node *root);
#endif
