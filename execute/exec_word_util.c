#include "../include/minishell.h"
#include "../include/execute.h"
#include "../include/exec_node_util.h"
#include "../include/exec_word_util.h"
#include "../include/filename_expansion.h"
#include "../include/arg_expansion.h"
#include "../include/make_argv_util.h"

void	*make_argv(char **word_arr, int flag)
{
	int		i;
	t_list	*list;
	t_list	*argv_list;
	t_bool	glob_flag;

	i = 0;
	list = NULL;
	argv_list = NULL;
	glob_flag = FALSE;
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
	if (flag == 0)
		return (argv_list);
	else
		return (list_to_arr(argv_list));
}

void	sigact_fork(void)
{
	struct sigaction	intsig;
	struct sigaction	quitsig;

	intsig.sa_handler = 0;
	sigemptyset(&intsig.sa_mask);
	intsig.sa_flags = 0;
	sigaction(SIGINT, &intsig, 0);
	quitsig.sa_handler = 0;
	sigemptyset(&quitsig.sa_mask);
	quitsig.sa_flags = 0;
	sigaction(SIGQUIT, &quitsig, 0);
}

void	sigact_forkset(void)
{
	struct sigaction	intsig;
	struct sigaction	quitsig;
	struct termios		attributes;

	tcgetattr(STDIN, &attributes);
	attributes.c_lflag |= ECHOCTL;
	tcsetattr(STDIN, TCSANOW, &attributes);
	intsig.sa_handler = SIG_IGN;
	quitsig.sa_handler = SIG_IGN;
	sigemptyset(&intsig.sa_mask);
	sigemptyset(&quitsig.sa_mask);
	intsig.sa_flags = 0;
	quitsig.sa_flags = 0;
	sigaction(SIGINT, &intsig, 0);
	sigaction(SIGQUIT, &quitsig, 0);
}

void	fork_exec(char **argv, t_context *p_ctx)
{
	int		pid;
	t_list	*envl;

	envl = *get_envp();
	sigact_forkset();
	pid = fork();
	if (pid == 0)
	{
		dup2(p_ctx->fd[STDIN], STDIN);
		dup2(p_ctx->fd[STDOUT], STDOUT);
		sigact_fork();
		if (p_ctx->fd_close >= 0)
		{
			close(p_ctx->fd_close);
			p_ctx->fd_close = -1;
		}
		execve(argv[0], argv, list_to_arr(envl));
		exit(1);
	}
	if (p_ctx->fd[STDIN] != STDIN)
		close(p_ctx->fd[STDIN]);
	if (p_ctx->fd[STDOUT] != STDOUT)
		close(p_ctx->fd[STDOUT]);
	enqueue(pid, p_ctx);
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
