/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:48:17 by dasong            #+#    #+#             */
/*   Updated: 2023/08/15 18:33:22 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# define STDIN 0
# define STDOUT 1
# define PATH_MAX 1024

typedef struct s_context
{
	int	exit_status;
	int	fd[2];
	int	fd_close;
	int	exit_status;
}	t_context;

t_bool	ft_cd(t_node *node);
t_bool	ft_echo(t_node *node);
t_bool	ft_pwd(t_node *node);
t_bool	ft_env(t_node *node);
t_bool	ft_exit(t_node *node);
t_bool	ft_export(t_node *node);
t_bool	ft_unset(t_node *node);
void	exit_utils(char **temp);
char	*vaild_env(char **temp);
char	*special_case(char **temp);
char	*ft_strnjoin(char const *s1, char const *s2);
void	delete_node(t_list **head, t_list *node_to_delete);
char	*getenv(char *pos);
t_list	*getenv_list(char *pos, size_t pos_len, t_list **env);
void	set_envp(char *pos, char *pwd);

#endif