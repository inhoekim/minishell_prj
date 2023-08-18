#include "../include/minishell.h"
#include "../include/execute.h"
#include "../include/exec_node_util.h"

t_bool	execute(t_node *root)
{
	t_context	ctx;

	ctx.fd[STDIN_FILENO] = STDIN_FILENO;
	ctx.fd[STDOUT_FILENO] = STDOUT_FILENO;
	ctx.fd_close = -1;
	// exit함수 호출시, TRUE
	ctx.check_exit = FALSE;
	ctx.queue_size = 0;
	exec_node(root, &ctx);
	// reaper();
	return (ctx.check_exit);
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
