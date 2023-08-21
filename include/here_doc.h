# define DELIMLEN 1024
# define HEREDOC_MAX 16
#include "../include/make_argv_util.h"
#include "../include/arg_expansion.h"
#include "../include/filename_expansion.h"
#include "../include/exec_word_util.h"

void	set_delimiter(t_node *node, char buf[]);
char	*quote_removal(char *word);
int 	*get_heredoc_exit_flag(void);
void 	set_heredoc_exit_flag(int flag);
void	here_doc(char *delimiter, t_tokenizer *tokenizer);
char	**alloc_heredoc_name(void);
