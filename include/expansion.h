#ifndef EXPANSION_H
# define EXPANSION_H

// # include "minishell2.h"
// # include "util.h"

t_list	*filename_expansion(t_list *list, t_bool glob_flag);
void	arg_expansion(t_list *list);
char	*concatenate(t_list *list);
int		wildcard(char *pattern, char *word, int p_idx, int w_idx);
void	dir_search(char *pattern, t_list *matches, int *p_file_cnt);
char	*parameter_expansion(char *str);

#endif