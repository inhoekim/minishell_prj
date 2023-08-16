#include "../include/minishell.h"
#include "../include/execute.h"
#include "../include/exec_node_util.h"
#include "../include/exec_word_util.h"
#include "../include/make_argv_util.h"
#include "../include/execute_util.h"
#include "../include/filename_expansion.h"

// #include "../include/exec_word_util.h"

// void	exec_subshell(t_node *node, t_ctx *p_ctx)
// {
// 	int		pid;
// 	t_node	*lhs;

// 	lhs = node->left;
// 	pid = fork();
// 	if (pid)
// 	{
// 		exec_word(lhs, p_ctx);
// 		wait_queue();
// 	}
// 	enqueue(pid);
// 	wait_queue();
// }

// void	exec_or(t_node *node, t_ctx *p_ctx)
// {
// 	int		pid;
// 	t_node	*lhs;
// 	t_node	*rhs;

// 	lhs = node->left;
// 	rhs = node->right;
// 	exec_word(lhs, p_ctx);
// 	if (p_ctx->exit_status != 0)
// 	{
// 		exec_word(rhs, p_ctx);
// 	}
// }

// void	exec_and(t_node *node, t_ctx *p_ctx)
// {
// 	int		pid;
// 	t_node	*lhs;
// 	t_node	*rhs;

// 	lhs = node->left;
// 	rhs = node->right;
// 	exec_word(lhs, p_ctx);
// 	if (p_ctx->exit_status == 0)
// 	{
// 		exec_word(rhs, p_ctx);
// 	}
// }

// void exec_pipe(t_node *node, t_ctx *p_ctx)
// {
// 	t_node	*lhs;
// 	t_node	*rhs;
// 	int		pipe_fd[2];
// 	t_ctx	*aux;

// 	lhs = node->left;
// 	rhs = node->right;
// 	pipe(pipe_fd);
// 	*aux = *p_ctx;
// 	aux->fd_close = pipe_fd[STDIN];
// 	aux->fd[STDOUT] = pipe_fd[STDOUT];
// 	exec_word(lhs, aux);

// 	*aux = *p_ctx;
// 	aux->fd[STDIN] = pipe_fd[STDIN];
// 	aux->fd_close = pipe_fd[STDOUT];
// 	exec_word(rhs, aux);
// }

// void	exec_input(t_node *node, t_ctx *p_ctx)
// {
// 	t_node	*lhs;
// 	t_node	*rhs;

// 	lhs = node->left;
// 	rhs = node->right;

// 	p_ctx->fd[STDIN] = open(rhs->word.buf, O_RDONLY, 0644);
// 	exec_word(lhs, p_ctx);
// }

// void exec_heredoc(t_node *node, t_ctx *p_ctx)
// {
// 	t_node	*lhs;
// 	t_node	*rhs;

// 	lhs = node->left;
// 	rhs = node->right;

// 	p_ctx->fd[STDIN] = open(rhs->word.buf, O_RDONLY, 0644);
// 	exec_word(lhs, p_ctx);
// }

// void exec_output(t_node *node, t_ctx *p_ctx)
// {
// 	t_node	*lhs;
// 	t_node	*rhs;

// 	lhs = node->left;
// 	rhs = node->right;

// 	p_ctx->fd[STDOUT] = open(rhs->word.buf, O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 	exec_word(lhs, p_ctx);
// }

// void exec_append(t_node *node, t_ctx *p_ctx)
// {
// 	t_node	*lhs;
// 	t_node	*rhs;

// 	lhs = node->left;
// 	rhs = node->right;

// 	p_ctx->fd[STDOUT] = open(rhs->word.buf, O_CREAT | O_APPEND| O_WRONLY, 0644);
// 	exec_word(lhs, p_ctx);
// }

char	*make_order(char **path, char **argv, t_context *p_ctx)
{
	int		idx;
	int		total;
	char	*order;

	idx = 0;
	order = 0;
	while (path[idx])
	{
		total = ft_strlen(argv[0]) + ft_strlen(path[idx]) + 1;
		order = (char *)malloc(sizeof(char) * total + 1);
		if (!order)
			return (0);
		order = ft_strjoin(path[idx], argv[0]);
		if (access(order, X_OK) != -1)
		{
			if (can_access(order, p_ctx))
				break ;
		}
		free(order);
		order = 0;
		idx++;
	}
	return (order);
}

void	search_and_fork_exec(char **argv, t_context *p_ctx)
{
	char	*order;
	char	**path;
	pid_t	pid;

	path = ft_split2(ft_getenv("PATH"), ':');
	order = make_order(path, argv, p_ctx);
	if (!order)
		p_ctx->exit_status = 127;
	pid = fork();
	if (pid == 0)
	{
		dup2(p_ctx->fd[STDIN], STDIN);
		dup2(p_ctx->fd[STDOUT], STDOUT);
		if (p_ctx->fd_close >= 0)
		{
			close(p_ctx->fd_close);
			p_ctx->fd_close = -1;
		}
		if (!order)
			msh_error(argv[0], "command not found", 0);
		execve(order, argv, list_to_arr(*get_envp()));
		exit(1);
	}
	waitpid(pid, 0, 0);
}

t_bool	exec_builtin(char **argv)
{
	t_bool		can_builtin;
	t_builtin	builtin_func;

	can_builtin = FALSE;
	builtin_func = check_builtin(argv[0]);
	if (builtin_func)
	{
		printf("not make builtin_func build\n");
		exit(1);
	}
	return (can_builtin);
}

t_builtin	check_builtin(char *argv)
{
	if (argv[0] == 'c')
		return (ft_cd);
	else if (argv[0] == 'e')
	{
		return (ft_echo);
	}
	else if (argv[0] == 'p')
		return (ft_pwd);
	else if (argv[0] == 'u')
		return (ft_unset);
	return (NULL);
}

void	exec_word(t_node *node, t_context *p_ctx)
{
	char	**argv;

	argv = make_argv(node->word);
	if (ft_strchr(argv[0], '/') == NULL)
	{
		if (exec_builtin(argv) == FALSE)
			search_and_fork_exec(argv, p_ctx);
	}
	else if (can_access(argv[0], p_ctx))
		fork_exec(argv, p_ctx);
	set_exit_status(p_ctx->exit_status);
	free_argv(argv);
}
