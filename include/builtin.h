#ifndef BUILTIN_H
# define BUILTIN_H

# include "../libft/libft.h"
# include "minishell2.h"
# include <errno.h>
# include <stdio.h>
# define PATH_MAX 1024

// builtin func
t_bool	ft_cd(char **argv);
t_bool	ft_echo(char **argv);
t_bool	ft_pwd(char **argv);
t_bool	ft_env(char **argv);
t_bool	ft_exit(char **argv);
t_bool	ft_export(char **argv);
t_bool	ft_unset(char **argv);

// set env func
t_list	*getenv_list(char *pos, size_t pos_len, t_list **env);
char	*ft_getenv(char *pos);
void	set_envp(char *pos, char *pwd);
char	*ft_strnjoin(char const *s1, char const *s2);
void	delete_node(t_list **head, t_list *node_to_delete);
void	exit_utils(char **temp);
int		check_argv(char *argv);
void	check_env(char **argv, t_list **env);
char	*make_temp(char *s1);

#endif