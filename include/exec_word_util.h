#ifndef EXEC_WORD_UTIL_H
# define EXEC_WORD_UTIL_H

# include "execute.h"

char	**make_argv(char **word_arr);
void	fork_exec(char **argv, t_context *p_ctx);
char	**list_to_arr(t_list *node);
t_bool	can_access(char *filename, t_context *p_ctx);

#endif
