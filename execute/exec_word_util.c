#include "../include/minishell.h"
#include "../include/execute.h"
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
		//ex. echo "123""456";
		list = split_quotes(word_arr[i]);
		glob_flag = check_glob(list);
		// heredoc delimeter에 (',"")가 있었다면 그 내용은 효력상실.
		// heredoc delimeter에 (',"")가 없었다면 그 내용은 expansion.
		// heredoc delimeter는 효력상실.
		// ex. echo '$USER', echo "$USER"
		// arg_expansion내부에서 cmd가 heredoc인지 판단해야함.
		arg_expansion(list);
		unquote(list);
		ft_lstadd_back(&argv_list, filename_expansion(list, glob_flag));
		ft_lstclear(&list, free);
		i++;
	}
	return (list_to_arr(argv_list));
}

void	fork_exec(char **argv, t_context *p_ctx)
{
	int		pid;
	t_list	*envl;
	char	**envp;

	envl = *get_envp();
	pid = fork();
	if (pid)
	{
		dup2(p_ctx->fd[STDIN], STDIN);
		dup2(p_ctx->fd[STDOUT], STDOUT);
		envp = list_to_arr(envl);
		if (p_ctx->fd_close >= 0) {
			close(p_ctx->fd_close);
			p_ctx->fd_close = -1;
		}
		execve(argv[0], argv, envp);
		printf("execve error\n");
	}
}

char	**list_to_arr(t_list *node)
{
	char	**arr;
	int		i;
	int		len;

	i = 0;
	len = ft_lstsize(node);
	arr = malloc(sizeof(t_list) * (len + 1));
	arr[len] = NULL;
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