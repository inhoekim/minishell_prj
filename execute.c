#include "minishell.h"

t_bool  execute(t_node *root)
{
	t_bool check_exit;

	// ctx.check_exit
	check_exit = FALSE;
	exec_node(root);
	// if EOF
	// 

	return (check_exit);
}

exec_node(t_node *root)
{
	if (root == NULL)
		return ;
	else if(root->type == WORD) {
		exec_word(root);
	}
	else if(root->type == LESS) {
		exec_input();
	}
	else if(root->type == GREAT) {
		exec_output();
	}
	else if(root->type == DGREAT) {
		exec_append();
	}
	else if(root->type == DLESS) {
		exec_heredoc();
	}
	else if(root->type == AND_IF) {
		exec_and();
	}
	else if(root->type == OR_IF) {
		exec_or();
	}
	else if(root->type == PIPE) {
		exec_pipe();
	}
	else if(root->type == SUBSHELL) {
		exec_subshell(root);
	}
	else if(root->type == E0F) {
		exec_eof();
	}
}

void	exec_subshell(t_node *root)
{
	int	pid;
	t_node *lfs;

	lfs = root->left;
	pid = fork();
	if (pid)
	{
		// execev();
	}
}

// void exec_word(t_node *root)
// {
// 	// 큰 산이다..
// 	// fork_exec();
// }
