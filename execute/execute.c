#include "../include/minishell.h"
#include "../include/execute.h"
#include "../include/exec_node_util.h"
#include "../include/here_doc.h"

void	free_delete_heredoc(t_context *p_ctx);

void	execute(t_node *root)
{
	t_context	ctx;

	ctx.fd[STDIN_FILENO] = STDIN_FILENO;
	ctx.fd[STDOUT_FILENO] = STDOUT_FILENO;
	ctx.fd_close = -1;
	ctx.is_piped_cmd = FALSE;
	ctx.heredoc_file_idx = 0;
	ctx.heredoc_file_name = alloc_heredoc_name();
	ctx.queue_size = 0;
	// @ sigaction set(default mode)
	// @ sigint(2) 컨트롤+c -> 개행후 새로운 프롬프트 출력
	// @ sigquit(3) 컨트롤+d -> 아무동작안함 (무시)
	exec_node(root, &ctx);
	wait_queue(&ctx);
	free_delete_heredoc(&ctx);
}

void	free_delete_heredoc(t_context *p_ctx)
{
	int	i;

	i = 0;
	while (i < p_ctx->heredoc_file_idx)
	{
		unlink(p_ctx->heredoc_file_name[i]);
		free(p_ctx->heredoc_file_name[i++]);
	}
	free(p_ctx->heredoc_file_name);
}

void	exec_node(t_node *node, t_context *p_ctx)
{
	if (node == NULL)
		return ;
	else if (node->type == WORD)
		exec_word(node, p_ctx);
	else if (node->type == LESS)
		exec_input(node, p_ctx);
	else if (node->type == GREAT)
		exec_output(node, p_ctx);
	else if (node->type == DGREAT)
		exec_append(node, p_ctx);
	else if (node->type == DLESS)
		exec_heredoc(node, p_ctx);
	else if (node->type == AND_IF)
		exec_and(node, p_ctx);
	else if (node->type == OR_IF)
		exec_or(node, p_ctx);
	else if (node->type == PIPE)
		exec_pipe(node, p_ctx);
	else if (node->type == SUBSHELL)
		exec_subshell(node, p_ctx);
	return ;
}
