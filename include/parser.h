#ifndef PARSER_H
# define PARSER_H

# include "util.h"

t_node	*parser(char *line);
void	syntax_error(t_tokenizer *tokenizer);
void	free_tokenizer(t_tokenizer *tokenizer);
t_bool	check_first_set(t_nonterminal idx, t_symbol curr_token);
t_token	*make_token(t_tokenizer *tokenizer, t_symbol type);
t_bool	match_token(t_symbol type, t_tokenizer *tokenizer, t_bool token_move);
t_token	*get_curr_token(t_tokenizer *tokenizer);
t_token	*get_next_token(t_tokenizer *tokenizer);
void	set_tokenizer(t_tokenizer *tokenizer, char *line);
void	skip_whitespace(t_tokenizer *tokenizer);
t_bool	is_match(t_tokenizer *tokenizer, char matchword);
char	**alloc_heredoc_name(void);
t_token	*scan_char_token(t_tokenizer *tokenizer);
t_token	*scan_word_token(t_tokenizer *tokenizer);
t_bool	string_close(t_tokenizer *tokenizer, char c);
t_node	*make_leaf(t_tokenizer *tokenizer);
t_node	*make_tree(t_symbol node_type, t_node *left, t_node *right);
void	free_tree(t_node *root);
t_node	*merge_tree(t_node *parent, t_node *child);

#endif
