/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:29:13 by seykim            #+#    #+#             */
/*   Updated: 2023/09/18 13:29:15 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define NONE -1
# define HEREDOC_MAX 16
# define TOKEN_SIZE 1024
# define DELIMETER "<>&|() \t\n"

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include "../libft/libft.h"
# include "grammar.h"
# include "execute.h"

typedef enum e_nonterminal		t_nonterminal;
typedef enum e_symbol			t_symbol;

typedef struct s_node			t_node;
typedef struct s_token			t_token;
typedef struct s_tokenizer		t_tokenizer;

//merge_tree
t_node	*merge_tree(t_node *parent, t_node *child);

//parser
t_node	*parser(char *line);
void	syntax_error(t_tokenizer *tokenizer);
void	free_tokenizer(t_tokenizer *tokenizer);
t_bool	check_first_set(t_nonterminal idx, t_symbol curr_token);

//tokenizer_scan
t_token	*scan_char_token(t_tokenizer *tokenizer);
t_token	*scan_word_token(t_tokenizer *tokenizer);
t_bool	string_close(t_tokenizer *tokenizer, char c);

//tokenizer_utils
void	set_tokenizer(t_tokenizer *tokenizer, char *line);
void	skip_whitespace(t_tokenizer *tokenizer);
t_bool	is_match(t_tokenizer *tokenizer, char matchword);

//tokenizer
t_token	*make_token(t_tokenizer *tokenizer, t_symbol type);
t_bool	match_token(t_symbol type, t_tokenizer *tokenizer, t_bool token_move);
t_token	*get_curr_token(t_tokenizer *tokenizer);
t_token	*get_next_token(t_tokenizer *tokenizer);

//tree
t_node	*make_leaf(t_tokenizer *tokenizer);
t_node	*make_tree(t_symbol node_type, t_node *left, t_node *right);
void	free_tree(t_node *root);

char	**alloc_heredoc_name(void);
#endif
