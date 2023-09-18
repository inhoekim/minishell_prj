/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:28:54 by seykim            #+#    #+#             */
/*   Updated: 2023/09/18 13:28:55 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "builtin.h"
# include "parser.h"
# include "signal.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <stdio.h>
# include <errno.h>
# include "util.h"
# define STDIN 0
# define STDOUT 1

typedef enum e_nonterminal		t_nonterminal;
typedef enum e_symbol			t_symbol;

typedef struct s_node			t_node;
typedef struct s_token			t_token;
typedef struct s_tokenizer		t_tokenizer;
typedef t_bool					(*t_builtin)(char **args);

typedef struct s_context
{
	int		exit_status;
	int		fd[2];
	int		fd_close;
	int		heredoc_file_idx;
	char	**heredoc_file_name;
	t_list	*pid_list;
	int		pid_size;
	t_bool	is_piped_cmd;
}	t_context;

t_builtin	check_builtin(char *argv);
t_list		*split_quotes(char *str);
t_list		*include_slice(char *str, int *i, char end);
t_bool		exec_builtin(char **argv, t_context *p_ctx);
t_bool		*get_redirect_ambiguity(void);
t_bool		is_regular_file(char *filename, t_context *p_ctx);
t_bool		is_not_directory(char *filename, t_context *p_ctx);
t_bool		check_glob(t_list *list);
t_bool		list_search(t_list *list, char ch);
t_bool		can_access(char *filename, t_context *p_ctx);
char		*make_order(char **path, char **argv);
char		**list_to_arr(t_list *node);
char		**make_argv(char **word_arr);
void		redirect_fd(int dst[2]);
void		exec_or(t_node *node, t_context *p_ctx);
void		exec_and(t_node *node, t_context *p_ctx);
void		exec_pipe(t_node *node, t_context *p_ctx);
void		exec_heredoc(t_node *node, t_context *p_ctx);
void		search_and_fork_exec(char **argv, t_context *p_ctx);
void		set_redirect_ambiguity(t_bool value);
void		exec_input(t_node *node, t_context *p_ctx);
void		exec_output(t_node *node, t_context *p_ctx);
void		exec_append(t_node *node, t_context *p_ctx);
int			ambiguity_check(char ***filename, t_context *p_ctx, t_node	*rhs);
void		exec_subshell(t_node *node, t_context *p_ctx);
void		free_argv(char **argv);
void		set_exit_status(int exit_status);
void		fork_error(t_context *p_ctx);
void		msh_error(char *name, char *msg, int error);
void		unquote(t_list *list);
void		exec_word(t_node *node, t_context *p_ctx);
void		fork_exec(char **argv, t_context *p_ctx);
void		execute(t_node *root);
void		exec_node(t_node *node, t_context *p_ctx);
void		find_last_pid(t_context *p_ctx);
void		free_delete_heredoc(t_context *p_ctx);
void		set_last_exit_status(int exit_status);
void		forked_builtin(t_context *p_ctx, \
t_builtin builtin_func, char **argv);
int			*get_exit_status(void);
t_bool		check_permission(char *filename, t_context *p_ctx, int mode_bit);
#endif