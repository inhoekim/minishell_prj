#ifndef MAKE_ARGV_UTIL_H
# define MAKE_ARGV_UTIL_H

# include "minishell.h"

t_list	*split_quotes(char *str);
t_list	*include_slice(char *str, int *i, char end);
t_bool	check_glob(t_list *list);
t_bool	list_search(t_list *list, char ch);
void	unquote(t_list *list);

#endif
