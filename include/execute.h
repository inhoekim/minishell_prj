#ifndef EXECUTE_H
# define EXECUTE_H

// # include "../libft/libft.h"
// # include "util.h"

t_bool	ft_cd(char **argv);
t_bool	ft_echo(char **argv);
t_bool	ft_export(char **argv);
t_bool	ft_exit(char **argv);
t_bool	ft_env(char **argv);
t_bool	ft_pwd(char **argv);
t_bool	ft_unset(char **argv);

void	set_last_exit_status(int exit_status);

t_builtin	check_builtin(char *argv);
void	redirect_fd(int dst[2]);
t_bool	exec_builtin(char **argv, t_context *p_ctx);
void	exec_or(t_node *node, t_context *p_ctx);
void	exec_and(t_node *node, t_context *p_ctx);
void	exec_pipe(t_node *node, t_context *p_ctx);
void	exec_heredoc(t_node *node, t_context *p_ctx);
void	search_and_fork_exec(char **argv, t_context *p_ctx);
char	*make_order(char **path, char **argv);
void	forked_builtin(t_context *p_ctx, t_builtin	builtin_func, char **argv);
t_bool	*get_redirect_ambiguity(void);
void	set_redirect_ambiguity(t_bool value);
t_bool	is_regular_file(char *filename, t_context *p_ctx);
t_bool	is_not_directory(char *filename, t_context *p_ctx);
void	exec_input(t_node *node, t_context *p_ctx);
void	exec_output(t_node *node, t_context *p_ctx);
void	exec_append(t_node *node, t_context *p_ctx);
void	ambiguity_check(char **filename, t_node	*rhs, t_context *p_ctx);
void	exec_subshell(t_node *node, t_context *p_ctx);
void	free_argv(char **argv);
void	set_exit_status(int exit_status);
int		*get_exit_status(void);
void	fork_error(t_context *p_ctx);
void	msh_error(char *name, char *msg, int error);
t_list	*split_quotes(char *str);
t_list	*include_slice(char *str, int *i, char end);
t_bool	check_glob(t_list *list);
t_bool	list_search(t_list *list, char ch);
void	unquote(t_list *list);
void	exec_word(t_node *node, t_context *p_ctx);
void	fork_exec(char **argv, t_context *p_ctx);
char	**list_to_arr(t_list *node);
t_bool	can_access(char *filename, t_context *p_ctx);
char	**make_argv(char **word_arr);
void	execute(t_node *root);
void	exec_node(t_node *node, t_context *p_ctx);
void	find_last_pid(t_context	*p_ctx);
void	free_delete_heredoc(t_context *p_ctx);

#endif