#include "../include/minishell.h"
#include "../include/execute.h"
#include "../include/exec_node_util.h"
#include "../include/exec_word_util.h"
#include "../include/make_argv_util.h"
#include "../include/execute_util.h"
#include "../include/filename_expansion.h"


void	exec_subshell(t_node *node, t_context *p_ctx)
{
	int		pid;
	t_node	*lhs;

	lhs = node->left;
	pid = fork();
	if (pid)
	{
		exec_node(lhs, p_ctx);
	}
	waitpid(pid, 0, 0);
	// reaper();
}

void	exec_or(t_node *node, t_context *p_ctx)
{
	t_node	*lhs;
	t_node	*rhs;

	lhs = node->left;
	rhs = node->right;
	exec_node(lhs, p_ctx);
	// reaper();
	// @ reaper로 pid종료상태업데이트 필요
	printf("exit status: %d\n", *get_exit_status());
	if (*get_exit_status() != 0)
	{
		exec_node(rhs, p_ctx);
	}
}

void	exec_and(t_node *node, t_context *p_ctx)
{
	t_node	*lhs;
	t_node	*rhs;

	lhs = node->left;
	rhs = node->right;
	exec_node(lhs, p_ctx);
	// reaper();
	// @ reaper로 pid종료상태업데이트 필요
	printf("exit status: %d\n", *get_exit_status());
	if (*get_exit_status() == 0)
	{
		exec_node(rhs, p_ctx);
	}
}

void	exec_pipe(t_node *node, t_context *p_ctx)
{
	t_node		*lhs;
	t_node		*rhs;
	int			pipe_fd[2];
	t_context	aux;

	lhs = node->left;
	rhs = node->right;
	pipe(pipe_fd);
	aux = *p_ctx;
	aux.fd[STDIN] = STDIN;
	aux.fd[STDOUT] = pipe_fd[STDOUT];
	aux.fd_close = pipe_fd[STDIN];
	exec_node(lhs, &aux);
	aux = *p_ctx;
	aux.fd[STDIN] = pipe_fd[STDIN];
	aux.fd[STDOUT] = STDOUT;
	aux.fd_close = pipe_fd[STDOUT];
	exec_node(rhs, &aux);
}

void	exec_input(t_node *node, t_context *p_ctx)
{
	t_node	*lhs;
	t_node	*rhs;

	lhs = node->left;
	rhs = node->right;

	p_ctx->fd[STDIN] = open(rhs->word[0], O_RDONLY, 0644);
	exec_node(lhs, p_ctx);
}

void	exec_heredoc(t_node *node, t_context *p_ctx)
{
	t_node	*lhs;
	t_node	*rhs;

	lhs = node->left;
	rhs = node->right;

	p_ctx->fd[STDIN] = open(rhs->word[0], O_RDONLY, 0644);
	exec_node(lhs, p_ctx);
}

void	exec_output(t_node *node, t_context *p_ctx)
{
	t_node	*lhs;
	t_node	*rhs;

	lhs = node->left;
	rhs = node->right;

	p_ctx->fd[STDOUT] = open(rhs->word[0], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	exec_node(lhs, p_ctx);
}

void	exec_append(t_node *node, t_context *p_ctx)
{
	t_node	*lhs;
	t_node	*rhs;

	lhs = node->left;
	rhs = node->right;

	p_ctx->fd[STDOUT] = open(rhs->word[0], O_CREAT | O_APPEND| O_WRONLY, 0644);
	exec_node(lhs, p_ctx);
}

char	*make_order(char **path, char **argv)
{
	struct stat	buff;
	int			idx;
	int			total;
	char		*order;

	idx = 0;
	order = NULL;
	while (path[idx])
	{
		total = ft_strlen(path[idx]) + ft_strlen(argv[0]) + 1;
		order = (char *)malloc(sizeof(char) * total + 1);
		if (!order)
			return (NULL);
		order = ft_strjoin(path[idx], argv[0]);
		stat(order, &buff);
		if (access(order, X_OK) == 0 && (buff.st_mode & S_IFMT) != S_IFDIR)
			break ;
		free(order);
		order = NULL;
		idx++;
	}
	return (order);
}

void	search_and_fork_exec(char **argv, t_context *p_ctx)
{
	char	*order;
	char	**path;
	char	*temp_path;

	temp_path = ft_getenv("PATH");
	if (!temp_path)
	{
		p_ctx->exit_status = 127;
		msh_error(argv[0], "command not found", 0);
		return ;
	}
	path = ft_split2(temp_path, ':');
	order = make_order(path, argv);
	if (order)
	{
		free(argv[0]);
		argv[0] = order;
		fork_exec(argv, p_ctx);
	}
	else
	{
		p_ctx->exit_status = 127;
		msh_error(argv[0], "command not found", 0);
	}
}

// @ reaper에서 사용될 함수인 것같음.
// @ 자식프로세스 종료 상태에 따라 exit_status를 달리 저장해야하므로 사용됨.
void	set_ctx_status(t_context *p_ctx, pid_t pid, int flag)
{
	waitpid(pid, &flag, 0);
	if (flag != 0)
	// 이거 왜 안되는지 모르겠음
	// if (WIFSIGNALED(flag))
		p_ctx->exit_status = 1;
	else
		p_ctx->exit_status = 0;
}

t_bool	exec_builtin(char **argv)
{
	t_bool		can_builtin;
	t_builtin	builtin_func;
	int			builtin_exit_status;

	can_builtin = FALSE;
	builtin_func = check_builtin(argv[0]);
	if (builtin_func)
	{
		builtin_exit_status = builtin_func(argv);
		set_exit_status(builtin_exit_status);
		can_builtin = TRUE;
	}
	return (can_builtin);
}

t_builtin	check_builtin(char *argv)
{
	if (argv[0] == 'c' && argv[1] == 'd' && argv[2] == '\0')
		return (ft_cd);
	else if (argv[0] == 'e')
	{
		if (argv[1] == 'c' && argv[2] == 'h' && argv[3] == 'o' && argv[4] == '\0')
			return (ft_echo);
		else if (argv[1] == 'x')
		{
			if (argv[2] == 'p' && argv[3] == 'o' && argv[4] == 'r'  && argv[5] == 't' && argv[6] == '\0')
				return (ft_export);
			else if (argv[2] == 'i' && argv[3] == 't' && argv[4] == '\0')
				return (ft_exit);
		}
		else if (argv[1] == 'n' && argv[2] == 'v' && argv[3] == '\0')
			return (ft_env);
	}
	else if (argv[0] == 'p' && argv[1] == 'w' && argv[2] == 'd' && argv[3] == 0)
		return (ft_pwd);
	else if (argv[0] == 'u' && argv[1] == 'n' && argv[2] == 's' && argv[3] == 'e' && argv[4] == 't' && argv[5] == '\0')
		return (ft_unset);
	return (NULL);
}

void	exec_word(t_node *node, t_context *p_ctx)
{
	char	**argv;

	argv = make_argv(node->word);
	if (ft_strchr(argv[0], '/') == NULL)
	{
		if (exec_builtin(argv) == FALSE)
			search_and_fork_exec(argv, p_ctx);
	}
	else if (can_access(argv[0], p_ctx))
		fork_exec(argv, p_ctx);
	set_exit_status(p_ctx->exit_status);
	free_argv(argv);
}
