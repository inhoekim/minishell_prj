#include "../include/minishell.h"
#include "../include/execute.h"
#include "../include/exec_node_util.h"
#include "../include/exec_word_util.h"
#include "../include/filename_expansion.h"
#include "../include/arg_expansion.h"
#include "../include/make_argv_util.h"

char	**make_argv(char **word_arr)
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
		list = split_quotes(word_arr[i]);
		glob_flag = check_glob(list);
		arg_expansion(list);
		unquote(list);
		ft_lstadd_back(&argv_list, filename_expansion(list, glob_flag));
		ft_lstclear(&list, free);
		i++;
	}
	return (list_to_arr(argv_list));
}

//norm 규정에 맞게 수정, 함수 마지막에 ctx_status를 추가해서 or, and가 작동하도록 수정
void	fork_exec(char **argv, t_context *p_ctx)
{
	int		pid;
	t_list	*envl;

	envl = *get_envp();
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
		execve(argv[0], argv, list_to_arr(envl));
		exit(1);
	}
	if (p_ctx->fd[STDIN_FILENO] != STDIN_FILENO)
		close(p_ctx->fd[STDIN_FILENO]);
	if (p_ctx->fd[STDOUT_FILENO] != STDOUT_FILENO)
		close(p_ctx->fd[STDOUT_FILENO]);
	enqueue(pid, p_ctx);
	//set_ctx_status(p_ctx, pid, 0);
}

char	**list_to_arr(t_list *node)
{
	char	**arr;
	int		i;
	int		len;

	i = 0;
	len = ft_lstsize(node);
	arr = ft_calloc(len + 1 ,sizeof(t_list));
	while (node)
	{
		arr[i++] = node->content;
		node = node->next;
	}
	return (arr);
}

// S_IFMT	0170000	bitmask for the file type bitfields
// S_IFDIR	0040000	directory
t_bool	can_access(char *filename, t_context *p_ctx)
{
	struct stat	buff;

	if (access(filename, F_OK) != 0)
	{
		msh_error(filename, NULL, ENOENT);
		p_ctx->exit_status = 127;
		return (FALSE);
	}
	stat(filename, &buff);
	if ((buff.st_mode & S_IFMT) == S_IFDIR)
	{
		msh_error(filename, NULL, EISDIR);
		p_ctx->exit_status = 126;
		return (FALSE);
	}
	else if (access(filename, X_OK) != 0)
	{
		msh_error(filename, NULL, EACCES);
		p_ctx->exit_status = 126;
		return (FALSE);
	}
	return (TRUE);
}
