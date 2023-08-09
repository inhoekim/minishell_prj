#include "minishell.h"

#include <fcntl.h>
#define STDIN 0
#define STDOUT 1

typedef struct s_ctx
{
	int	exit_status;
	int	fd[2];
	int	fd_close;

}	t_ctx;


t_bool 	execute(t_node *root)
{
	t_bool	check_exit;
	t_node	*node;

	t_ctx ctx;
	// ctx.exit_status;

	check_exit = FALSE;
	node = exec_node(root, &ctx);
	if (node->type != E0F)
	{
		syntax_error();
	}
	return (check_exit);
}

t_node *exec_node(t_node *node, t_ctx *p_ctx)
{
	if (node == NULL)
		return ;
	else if(node->type == WORD) {
		exec_word(node, p_ctx);
	}
	else if(node->type == LESS) {
		exec_input(node, p_ctx);
	}
	else if(node->type == GREAT) {
		exec_output(node, p_ctx);
	}
	else if(node->type == DGREAT) {
		exec_append(node, p_ctx);
	}
	else if(node->type == DLESS) {
		exec_heredoc(node, p_ctx);
	}
	else if(node->type == AND_IF) {
		exec_and(node, p_ctx);
	}
	else if(node->type == OR_IF) {
		exec_or(node, p_ctx);
	}
	else if(node->type == PIPE) {
		exec_pipe(node, p_ctx);
	}
	else if(node->type == SUBSHELL) {
		exec_subshell(node, p_ctx);
	}
}

void	exec_subshell(t_node *node, t_ctx *p_ctx)
{
	int		pid;
	t_node	*lhs;

	lhs = node->left;
	pid = fork();
	if (pid)
	{
		exec_word(lhs, p_ctx);
		wait_queue();
	}
	enqueue(pid);
	wait_queue();
}

void	exec_or(t_node *node, t_ctx *p_ctx)
{
	int		pid;
	t_node	*lhs;
	t_node	*rhs;

	lhs = node->left;
	rhs = node->right;
	exec_word(lhs, p_ctx);
	if (p_ctx->exit_status != 0)
	{
		exec_word(rhs, p_ctx);
	}
}

void	exec_and(t_node *node, t_ctx *p_ctx)
{
	int		pid;
	t_node	*lhs;
	t_node	*rhs;

	lhs = node->left;
	rhs = node->right;
	exec_word(lhs, p_ctx);
	if (p_ctx->exit_status == 0)
	{
		exec_word(rhs, p_ctx);
	}
}

void exec_pipe(t_node *node, t_ctx *p_ctx)
{
	t_node	*lhs;
	t_node	*rhs;
	int		pipe_fd[2];
	t_ctx	*aux;

	lhs = node->left;
	rhs = node->right;
	pipe(pipe_fd);
	*aux = *p_ctx;
	aux->fd_close = pipe_fd[STDIN];
	aux->fd[STDOUT] = pipe_fd[STDOUT];
	exec_word(lhs, aux);

	*aux = *p_ctx;
	aux->fd[STDIN] = pipe_fd[STDIN];
	aux->fd_close = pipe_fd[STDOUT];
	exec_word(rhs, aux);
}

void	exec_input(t_node *node, t_ctx *p_ctx)
{
	t_node	*lhs;
	t_node	*rhs;

	lhs = node->left;
	rhs = node->right;

	p_ctx->fd[STDIN] = open(rhs->word.buf, O_RDONLY, 0644);
	exec_word(lhs, p_ctx);
}

void exec_heredoc(t_node *node, t_ctx *p_ctx)
{
	t_node	*lhs;
	t_node	*rhs;

	lhs = node->left;
	rhs = node->right;

	p_ctx->fd[STDIN] = open(rhs->word.buf, O_RDONLY, 0644);
	exec_word(lhs, p_ctx);
}

void exec_output(t_node *node, t_ctx *p_ctx)
{
	t_node	*lhs;
	t_node	*rhs;

	lhs = node->left;
	rhs = node->right;

	p_ctx->fd[STDOUT] = open(rhs->word.buf, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	exec_word(lhs, p_ctx);
}

void exec_append(t_node *node, t_ctx *p_ctx)
{
	t_node	*lhs;
	t_node	*rhs;

	lhs = node->left;
	rhs = node->right;

	p_ctx->fd[STDOUT] = open(rhs->word.buf, O_CREAT | O_APPEND| O_WRONLY, 0644);
	exec_word(lhs, p_ctx);
}

void exec_word(t_node *node, t_ctx *p_ctx)
{
	if (ft_strchr(node->word.buf, '/') == NULL) {
		if (exec_builtin() == NULL) {
			search_and_fork_exec();
		}
	}
	else {
		fork_exec(node, p_ctx);
	}
}

void fork_exec(t_node *node, t_ctx *p_ctx)
{
	int		pid;

	dup2(p_ctx->fd[STDIN], STDIN);
	dup2(p_ctx->fd[STDOUT], STDOUT);
	pid = fork();
	if (pid)
	{
		node->word.buf
		execev();
	}
}
