/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:11:38 by seykim            #+#    #+#             */
/*   Updated: 2023/08/30 19:11:39 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	exec_input(t_node *node, t_context *p_ctx)
{
	t_node	*lhs;
	t_node	*rhs;
	char	**filename;

	lhs = node->left;
	rhs = node->right;
	if (p_ctx->fd[STDIN] != STDIN)
		close(p_ctx->fd[STDIN]);
	if (ambiguity_check(&filename, p_ctx, rhs))
		return ;
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
	if (ambiguity_check(&filename, p_ctx, rhs))
		return ;
	if (!is_not_directory(filename[0], p_ctx))
		fork_error(p_ctx);
	else
	{
		p_ctx->fd[STDOUT] = open(filename[0], \
		O_CREAT | O_TRUNC | O_WRONLY, 0644);
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
	if (ambiguity_check(&filename, p_ctx, rhs))
		return ;
	if (!is_not_directory(filename[0], p_ctx))
		fork_error(p_ctx);
	else
	{
		p_ctx->fd[STDOUT] = open(filename[0], \
		O_CREAT | O_APPEND | O_WRONLY, 0644);
		exec_node(lhs, p_ctx);
	}
	free_argv(filename);
	return ;
}

int	ambiguity_check(char ***filename, t_context *p_ctx, t_node	*rhs)
{
	set_redirect_ambiguity(TRUE);
	*filename = (char **)make_argv(rhs->word);
	if (*get_redirect_ambiguity() == FALSE)
	{
		p_ctx->exit_status = 1;
		fork_error(p_ctx);
		free_argv(*filename);
		return (1);
	}
	set_redirect_ambiguity(FALSE);
	return (0);
}
