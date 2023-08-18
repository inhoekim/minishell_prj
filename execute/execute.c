#include "../include/minishell.h"
#include "../include/execute.h"
#include "../include/exec_node_util.h"

t_bool	execute(t_node *root)
{
	t_context	ctx;

	char *file_name[16] = \
	{"heredoc_0", "heredoc_1", "heredoc_2", "heredoc_3", "heredoc_4", "heredoc_5", "heredoc_6", "heredoc_7", "heredoc_8", "heredoc_9", "heredoc_10", "heredoc_11", "heredoc_12", "heredoc_13", "heredoc_14", "heredoc_15"};
	ctx.heredoc_file_name = (char *)file_name;
	ctx.heredoc_file_idx = 0;
	ctx.fd[STDIN_FILENO] = STDIN_FILENO;
	ctx.fd[STDOUT_FILENO] = STDOUT_FILENO;
	ctx.fd_close = -1;
	// exit함수 호출시, TRUE
	ctx.check_exit = FALSE;
	exec_node(root, &ctx);
	// reaper();
	return (ctx.check_exit);
}

void exec_node(t_node *node, t_context *p_ctx)
{
	if (node == NULL)
		return ;
	else if(node->type == WORD)
		exec_word(node, p_ctx);
	else if(node->type == LESS)
		exec_input(node, p_ctx);
	else if(node->type == GREAT)
		exec_output(node, p_ctx);
	else if(node->type == DGREAT)
		exec_append(node, p_ctx);
	else if(node->type == DLESS)
		exec_heredoc(node, p_ctx);
	else if(node->type == AND_IF)
		exec_and(node, p_ctx);
	else if(node->type == OR_IF)
		exec_or(node, p_ctx);
	else if(node->type == PIPE)
		exec_pipe(node, p_ctx);
	else if(node->type == SUBSHELL)
		exec_subshell(node, p_ctx);
	return ;
}
