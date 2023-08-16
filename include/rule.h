/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rule.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhkim <inhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:41:23 by inhkim            #+#    #+#             */
/*   Updated: 2023/08/16 12:42:23 by inhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RULE_H
# define RULE_H
# include "minishell.h"

t_node	*msh_grammar(t_tokenizer *tokenizer);
t_node	*conditional(t_tokenizer *tokenizer);
t_node	*pipeline(t_tokenizer *tokenizer);
t_node	*piped_command(t_tokenizer *tokenizer);
t_node	*command(t_tokenizer *tokenizer);
t_node	*ssh(t_tokenizer *tokenizer);
t_node	*simple_cmd(t_tokenizer *tokenizer);
t_node	*io_redirect_or_word_star(t_tokenizer *tokenizer);
t_node	*io_redirect_dagger(t_tokenizer *tokenizer);
t_node	*io_redirect_dg_after_simple_cmd(t_tokenizer *tokenizer);
t_node	*io_redirect_star(t_tokenizer *tokenizer);
t_node	*io_redirect(t_tokenizer *tokenizer);
t_node	*io_file(t_tokenizer *tokenizer);
t_node	*io_here(t_tokenizer *tokenizer);
t_node	*merge_tree(t_node *parent, t_node *child);
t_node	*make_leaf(t_tokenizer *tokenizer);
t_node	*make_tree(t_symbol node_type, t_node *left, t_node *right);
#endif