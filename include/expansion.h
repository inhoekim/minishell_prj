#ifndef EXPANSION_H
# define EXPANSION_H

# include "../libft/libft.h"
# include "execute.h"
# include <dirent.h>
# include <errno.h>

t_list	*filename_expansion(t_list *list, t_bool glob_flag);
char	*concatenate(t_list *list);
char	*parameter_expansion(char *str);
void	arg_expansion(t_list *list);
void	arg_expansion(t_list *list);
void	dir_search(char *pattern, t_list *matches, int *p_file_cnt);
int		wildcard(char *pattern, char *word, int p_idx, int w_idx);
t_list	*make_key_list(char *str, int i);
char	**path_split(char *s, char c);
#endif