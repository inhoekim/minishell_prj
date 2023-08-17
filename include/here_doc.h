#define DELIMLEN 1024

#include "../include/make_argv_util.h"
#include "../include/arg_expansion.h"
#include "../include/filename_expansion.h"

void	set_delimiter(t_node *node, char buf[]);
char	*quote_removal(char *word);
int *get_heredoc_exit_flag(void);
void set_heredoc_exit_flag(int flag);
void	here_doc(char *delimiter, t_tokenizer *tokenizer);
