#include "execute.h"

void	*make_argv(char **word_arr, int flag);
void	fork_exec(char **argv, t_context *p_ctx);
char	**list_to_arr(t_list *node);
t_bool	can_access(char *filename, t_context *p_ctx);
