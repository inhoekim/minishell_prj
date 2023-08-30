/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:12:33 by seykim            #+#    #+#             */
/*   Updated: 2023/08/30 19:12:34 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../libft/libft.h"
# include "minishell.h"
# include <errno.h>
# include <stdio.h>
# define PATH_MAX 1024
# include "util.h"

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
char	*make_temp(char *s1);
char	*ft_strnjoin(char const *s1, char const *s2);
void	set_envp(char *pos, char *pwd);
void	delete_node(t_list **head, t_list *node_to_delete);
void	exit_utils(char **temp);
void	check_env(char **argv, t_list **env);
int		check_argv(char *argv);

#endif