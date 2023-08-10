#include "../include/minishell.h"
#include <fcntl.h>

#define STDIN 0
#define STDOUT 1

typedef struct s_ctx
{
	int	exit_status;
	int	fd[2];
	int	fd_close;

}	t_ctx;


t_bool	execute(t_node *root)
{
	t_bool	check_exit;
	t_node	*node;
	t_ctx	ctx;

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

void	exec_word(t_node *node, t_ctx *p_ctx)
{
	char	**argv;

	argv = globbing(node->word);
	if (ft_strchr(argv, '/') == NULL)
	{
		if (exec_builtin() == NULL) {
			search_and_fork_exec();
		}
	}
	else {
		fork_exec(argv, p_ctx);
	}
}

char	**globbing(char **word_arr)
{
	int		i;
	t_list	*list;
	t_list	*argv_list;
	t_bool	glob_flag;

	i = 0;
	list = NULL;
	argv_list = NULL;
	while (word_arr[i])
	{
		//echo "123""456";
		list = split_quote(word_arr[i]);
		glob_flag = check_glob(list);
		// parameter가 quotation(')안에 있으면 효력상실.
		parameter_expansion(list);
		unquote(list);
		ft_lstadd_back(&argv_list, pathname_expansion(list, glob_flag));
		ft_lstclear(&list, free);
		i++;
	}
	return (list_to_arr(argv_list));
}

t_bool	check_glob(t_list *list)
{
	// globbing character가 quotation(', "")안에 있으면 효력상실.
	return (has_pattern(list, '*') || has_pattern(list, '?'));
}


t_bool	has_pattern(t_list *list, char chr)
{
	char	*aux;
	t_bool	pattern;

	pattern = FALSE;
	while (list)
	{
		aux = list->content;
		if (ft_strchr(aux, chr))
		{
			if (!ft_strchr(aux, '"') && !ft_strchr(aux, '\''))
				pattern = TRUE;
		}
		list = list->next;
	}
	return (pattern);
}

// parameter_expansion;
// unquote;
// pathname_expansion;

void	fork_exec(t_node *node, t_ctx *p_ctx)
{
	int		pid;
	char	**envp;
	char	**env_strarr;
	char	*cmd_path;

	dup2(p_ctx->fd[STDIN], STDIN);
	dup2(p_ctx->fd[STDOUT], STDOUT);
	pid = fork();
	if (pid)
	{
		env_strarr = list_to_arr();
		cmd_path = cmd_path_find(node->word[0], envp);
		execve(node->word[0], node->word, env_strarr);
		
	}
}

char	**list_to_arr()
{
	t_list	**env;
	t_list	*env_node;
	char	**env_strarr;
	int		i;
	int		len;

	i = 0;
	env = get_envp();
	env_node = *env;
	len = ft_lstsize(env_node);
	env_strarr = malloc(sizeof(t_list) * (len + 1));
	env_strarr[len] = NULL;
	while (env_node != NULL)
	{
		env_strarr[i++] = env_node->content;
		env_node = env_node->next;
	}
	return (env_strarr);
}

char	*cmd_path_find(char *cmd, char **envp)
{
	char	**env_pt;
	char	**res1;
	char	**res2;
	int		i;
	char	*cmd_path;

	env_pt = envp;
	while (*env_pt)
	{
		res1 = ft_split(*(env_pt++), '=');
		if (!ft_strncmp(res1[0], "PATH", 4))
		{
			res2 = ft_split(res1[1], ':');
			i = 0;
			while (res2[i])
			{
				cmd_path = ft_strjoin(res2[i++], cmd);
				if (access(cmd_path, X_OK) != -1)
					return (cmd_path);
			}
			free(res2);
			free(res1);
		}
	}
	return (0);
}