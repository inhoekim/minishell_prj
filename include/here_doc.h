#ifndef HERE_DOC_H
# define DELIMLEN 1024
# define HEREDOC_MAX 16
# include "../include/make_argv_util.h"
# include "../include/arg_expansion.h"
# include "../include/filename_expansion.h"
# include "../include/exec_word_util.h"
# include "../gnl/get_next_line.h"

typedef struct s_heredoc_data{
	int	heredoc_fault_flag;
}t_heredoc_data;
void			set_delimiter(t_node *node, char buf[]);
char			*quote_removal(char *word);
void			here_doc(char *delimiter, t_tokenizer *tokenizer);
char			**alloc_heredoc_name(void);
t_heredoc_data	*get_heredoc_data(void);
void			set_heredoc_fault_flag(int flag);
void			delete_heredoc(t_tokenizer *tokenizer);
#endif
