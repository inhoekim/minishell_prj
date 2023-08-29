#ifndef FILENAME_EXPANSION_H
# define FILENAME_EXPANSION_H

# include "../include/minishell.h"
# include <sys/stat.h>
# include <errno.h>
# include <dirent.h>

t_list	*filename_expansion(t_list *list, t_bool glob_flag);
char	*concatenate(t_list *list);
t_list	*globbing(char *pattern);
int		**allocate_dp(int row, int col);
int		is_match(char *pattern, char *word, int p_idx, int w_idx);
void	msh_error(char *name, char *msg, int error);

#endif
