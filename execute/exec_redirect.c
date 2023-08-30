
#include "../include/minishell.h"

void	exec_input(t_node *node, t_context *p_ctx)
{
	t_node	*lhs;
	t_node	*rhs;
	char	**filename;

	lhs = node->left;
	rhs = node->right;
	if (p_ctx->fd[STDIN] != STDIN)
		close(p_ctx->fd[STDIN]);
	set_redirect_ambiguity(TRUE);
	filename = (char **)make_argv(rhs->word);
	if (*get_redirect_ambiguity() == FALSE)
	{
		p_ctx->exit_status = 1;
		fork_error(p_ctx);
		return ;
	}
	set_redirect_ambiguity(FALSE);
	if (!is_regular_file(filename[0], p_ctx))
		fork_error(p_ctx);
	else
	{
		p_ctx->fd[STDIN] = open(filename[0], O_RDONLY, 0644);
		exec_node(lhs, p_ctx);
	}
	free_argv(filename);
	return ;
}

void	exec_output(t_node *node, t_context *p_ctx)
{
	t_node	*lhs;
	t_node	*rhs;
	char	**filename;

	lhs = node->left;
	rhs = node->right;
	if (p_ctx->fd[STDOUT] != STDOUT)
		close(p_ctx->fd[STDOUT]);
	set_redirect_ambiguity(TRUE);
	filename = make_argv(rhs->word);
	if (*get_redirect_ambiguity() == FALSE)
	{
		p_ctx->exit_status = 1;
		fork_error(p_ctx);
		return ;
	}
	set_redirect_ambiguity(FALSE);
	if (!is_not_directory(filename[0], p_ctx))
		fork_error(p_ctx);
	else
	{
		p_ctx->fd[STDOUT] = open(filename[0], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		exec_node(lhs, p_ctx);
	}
	free_argv(filename);
	return ;
}

void	exec_append(t_node *node, t_context *p_ctx)
{
	t_node	*lhs;
	t_node	*rhs;
	char	**filename;

	lhs = node->left;
	rhs = node->right;
	if (p_ctx->fd[STDOUT] != STDOUT)
		close(p_ctx->fd[STDOUT]);
	set_redirect_ambiguity(TRUE);
	filename = make_argv(rhs->word);
	if (*get_redirect_ambiguity() == FALSE)
	{
		p_ctx->exit_status = 1;
		fork_error(p_ctx);
		return ;
	}
	set_redirect_ambiguity(FALSE);
	if (!is_not_directory(filename[0], p_ctx))
		fork_error(p_ctx);
	else
	{
		p_ctx->fd[STDOUT] = open(filename[0], O_CREAT | O_APPEND | O_WRONLY, 0644);
		exec_node(lhs, p_ctx);
	}
	free_argv(filename);
	return ;
}
