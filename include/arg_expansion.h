#ifndef ARG_EXPANSION_H
# define ARG_EXPANSION_H

# include "minishell.h"

void	arg_expansion(t_list *list);
char	*parameter_expansion(char *str);
char	*str_replace(char *str, char *old, char *new);
int		word_cnt(char *str, char *word);
char	*get_value(char *key);
t_list	*search_key(char *str, int i);

#endif
