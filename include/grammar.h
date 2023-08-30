#ifndef GRAMMAR_H
# define GRAMMAR_H

// # include "util.h"

typedef struct s_heredoc_data{
	int	heredoc_fault_flag;
	int	heredoc_eof_flag;
	int	temp_stdin_fd;
	int	cursor_size;
}	t_heredoc_data;

//heredoc
void			heredoc(char *delimiter, t_tokenizer *tokenizer);
t_heredoc_data	*get_heredoc_data(void);
void			set_heredoc_eof_flag(int flag);
void			set_tmp_stdin_fd(int fd);
void			set_heredoc_fault_flag(int flag);
void			delete_heredoc(t_tokenizer *tokenizer);
void			set_delimiter(t_node *node, char buf[]);
t_bool			is_same_str(char *word1, char *word2);

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