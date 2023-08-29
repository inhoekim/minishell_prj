#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"

void	arg_expansion(t_list *list);
t_list	*filename_expansion(t_list *list, t_bool glob_flag);
char	*concatenate(t_list *list);
int		wildcard(char *pattern, char *word, int p_idx, int w_idx);

#endif