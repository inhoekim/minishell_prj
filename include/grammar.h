/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:29:09 by seykim            #+#    #+#             */
/*   Updated: 2023/09/18 13:29:10 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAMMAR_H
# define GRAMMAR_H
# define DELIMLEN 1024
# define HEREDOC_MAX 16
# define STDIN 0
# define STDOUT 1

# include "../libft/libft.h"
# include "parser.h"
# include "ft_signal.h"
# include "expansion.h"
# include <fcntl.h>

typedef enum e_nonterminal		t_nonterminal;
typedef enum e_symbol			t_symbol;

typedef struct s_node			t_node;
typedef struct s_token			t_token;
typedef struct s_tokenizer		t_tokenizer;
typedef struct s_heredoc_data	t_heredoc_data;

//heredoc
t_heredoc_data	*get_heredoc_data(void);
t_bool			is_same_str(char *word1, char *word2);
void			heredoc(char *delimiter, t_tokenizer *tokenizer);
void			set_heredoc_eof_flag(int flag);
void			set_tmp_stdin_fd(int fd);
void			set_heredoc_fault_flag(int flag);
void			delete_heredoc(t_tokenizer *tokenizer);
void			set_delimiter(t_node *node, char buf[]);
void			set_tmp_stdin_fd(int fd);

// rule
t_node			*msh_grammar(t_tokenizer *tokenizer);
t_node			*conditional(t_tokenizer *tokenizer);
t_node			*pipeline(t_tokenizer *tokenizer);
t_node			*piped_command(t_tokenizer *tokenizer);
t_node			*command(t_tokenizer *tokenizer);
t_node			*ssh(t_tokenizer *tokenizer);
t_node			*simple_cmd(t_tokenizer *tokenizer);
t_node			*io_redirect_or_word_star(t_tokenizer *tokenizer);
t_node			*io_redirect_dagger(t_tokenizer *tokenizer);
t_node			*io_redirect_dg_after_simple_cmd(t_tokenizer *tokenizer);
t_node			*io_redirect_star(t_tokenizer *tokenizer);
t_node			*io_redirect(t_tokenizer *tokenizer);
t_node			*io_file(t_tokenizer *tokenizer);
t_node			*io_here(t_tokenizer *tokenizer);

#endif