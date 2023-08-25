#include "../include/minishell.h"
#include "../include/execute.h"
#include "../include/exec_node_util.h"
#include "../include/exec_word_util.h"
#include "../include/make_argv_util.h"
#include "../include/execute_util.h"
#include "../include/filename_expansion.h"
#include "../include/arg_expansion.h"
#include "../include/wait_queue.h"
#include "../include/ms_signal.h"

static t_bool	check_str(char *argv, int idx, int size, char *sep);

void	fork_error(t_context *p_ctx)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		exit(p_ctx->exit_status);
	enqueue_after(pid, p_ctx);
}

void	exec_subshell(t_node *node, t_context *p_ctx)
{
	int		pid;
	t_node	*lhs;

	lhs = node->left;
	pid = fork();
	if (pid == 0)
	{
		exec_node(lhs, p_ctx);
		if (p_ctx->fd_close >= 0)
			close(p_ctx->fd_close);
		wait_queue_after(p_ctx);
		exit(p_ctx->exit_status);
	}
	if (p_ctx->fd[STDIN] != STDIN)
		close(p_ctx->fd[STDIN]);
	if (p_ctx->fd[STDOUT] != STDOUT)
		close(p_ctx->fd[STDOUT]);
	enqueue_after(pid, p_ctx);
}

void	exec_or(t_node *node, t_context *p_ctx)
{
	t_node	*lhs;
	t_node	*rhs;

	lhs = node->left;
	rhs = node->right;
	exec_node(lhs, p_ctx);
	find_last_pid(p_ctx);
	wait_queue_after(p_ctx);
	if (*get_last_exit_status() != 0)
		exec_node(rhs, p_ctx);
}

void	exec_and(t_node *node, t_context *p_ctx)
{
	t_node	*lhs;
	t_node	*rhs;

	lhs = node->left;
	rhs = node->right;
	exec_node(lhs, p_ctx);
	find_last_pid(p_ctx);
	wait_queue_after(p_ctx);
	if (*get_last_exit_status() == 0)
		exec_node(rhs, p_ctx);
}

void	exec_pipe(t_node *node, t_context *p_ctx)
{
	t_node		*lhs;
	t_node		*rhs;
	int			pipe_fd[2];
	t_context	aux;

	p_ctx->is_piped_cmd = TRUE;
	lhs = node->left;
	rhs = node->right;
	pipe(pipe_fd);
	aux = *p_ctx;
	aux.fd[STDOUT] = pipe_fd[STDOUT];
	aux.fd_close = pipe_fd[STDIN];
	exec_node(lhs, &aux);
	p_ctx->pid_list = aux.pid_list;
	p_ctx->pid_size = aux.pid_size;

	aux = *p_ctx;
	aux.fd[STDIN] = pipe_fd[STDIN];
	aux.fd_close = pipe_fd[STDOUT];
	exec_node(rhs, &aux);
	p_ctx->pid_list = aux.pid_list;
	p_ctx->pid_size = aux.pid_size;

	p_ctx->is_piped_cmd = FALSE;
}

static t_bool	is_regular_file(char *filename, t_context *p_ctx)
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
	return (TRUE);
}

t_bool	*get_redirect_ambiguity(void)
{
	static t_bool	redirect_ambiguity;

	return (&redirect_ambiguity);
}

void	set_redirect_ambiguity(t_bool value)
{
	*get_redirect_ambiguity() = value;
}

void	exec_input(t_node *node, t_context *p_ctx)
{
	t_node	*lhs;
	t_node	*rhs;
	char	**filename;

	lhs = node->left;
	rhs = node->right;
	if (p_ctx->fd[STDIN] != STDIN)
		close(p_ctx->fd[STDIN]);

	set_redirect_ambiguity(TRUE);
	filename = (char **)make_argv(rhs->word);
	if (*get_redirect_ambiguity() == FALSE)
	{
		p_ctx->exit_status = 1;
		fork_error(p_ctx);
		return ;
	}
	set_redirect_ambiguity(FALSE);
	if (!is_regular_file(filename[0], p_ctx))
	{
		fork_error(p_ctx);
		return ;
	}
	p_ctx->fd[STDIN] = open(filename[0], O_RDONLY, 0644);
	exec_node(lhs, p_ctx);
}

void	exec_heredoc(t_node *node, t_context *p_ctx)
{
	t_node	*lhs;

	lhs = node->left;
	if (p_ctx->fd[STDIN] != STDIN)
		close(p_ctx->fd[STDIN]);
	p_ctx->fd[STDIN] = open(p_ctx->heredoc_file_name[p_ctx->heredoc_file_idx++], O_RDONLY, 0644);
	exec_node(lhs, p_ctx);
}

static t_bool	is_not_directory(char *filename, t_context *p_ctx)
{
	struct stat	buff;

	stat(filename, &buff);
	if ((buff.st_mode & S_IFMT) == S_IFDIR)
	{
		msh_error(filename, NULL, EISDIR);
		p_ctx->exit_status = 126;
		return (FALSE);
	}
	return (TRUE);
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
	set_redirect_ambiguity(TRUE);
	filename = make_argv(rhs->word);
	if (*get_redirect_ambiguity() == FALSE)
	{
		p_ctx->exit_status = 1;
		fork_error(p_ctx);
		return ;
	}
	set_redirect_ambiguity(FALSE);
	if (!is_not_directory(filename[0], p_ctx))
	{
		fork_error(p_ctx);
		return ;
	}
	p_ctx->fd[STDOUT] = open(filename[0], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	exec_node(lhs, p_ctx);
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
	set_redirect_ambiguity(TRUE);
	filename = make_argv(rhs->word);
	if (*get_redirect_ambiguity() == FALSE)
	{
		p_ctx->exit_status = 1;
		fork_error(p_ctx);
		return ;
	}
	set_redirect_ambiguity(FALSE);
	if (!is_not_directory(filename[0], p_ctx))
	{
		fork_error(p_ctx);
		return ;
	}
	p_ctx->fd[STDOUT] = open(filename[0], O_CREAT | O_APPEND| O_WRONLY, 0644);
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
		if (p_ctx->fd[STDIN] != STDIN)
			close(p_ctx->fd[STDIN]);
		if (p_ctx->fd[STDOUT] != STDOUT)
			close(p_ctx->fd[STDOUT]);
		p_ctx->exit_status = 127;
		fork_error(p_ctx);
		msh_error(argv[0], "command not found", 0);
	}
	free_argv(path);
	free(temp_path);
}


void redirect_fd(int dst[2])
{
	dup2(dst[STDIN], STDIN);
	dup2(dst[STDOUT], STDOUT);
}

void forked_builtin(t_context *p_ctx, t_builtin	builtin_func, char **argv)
{
	int		pid;
	int		builtin_exit_status;

	pid = fork();
	sigact_fork_mode();
	if (pid == 0)
	{
		// @ sigaction set(fork interactive mode)
		// @ (구현x)sigint(2) 컨트롤+c -> 개행하고 default mode전환
		// @ (구현x)sigquit(3) 컨트롤+\ -> Quit: 3\n 출력 후 default mode전환
		// @ (구현o)eof 		컨트롤+ d -> eof (건들필요 x )
		sigact_modeoff();
		dup2(p_ctx->fd[STDIN], STDIN);
		dup2(p_ctx->fd[STDOUT], STDOUT);
		if (p_ctx->fd_close >= 0)
		{
			close(p_ctx->fd_close);
			p_ctx->fd_close = -1;
		}
		builtin_exit_status = builtin_func(argv);
		exit(builtin_exit_status);
	}
	if (p_ctx->fd[STDIN] != STDIN)
		close(p_ctx->fd[STDIN]);
	if (p_ctx->fd[STDOUT] != STDOUT)
		close(p_ctx->fd[STDOUT]);
	enqueue_after(pid, p_ctx);

}

t_bool	exec_builtin(char **argv, t_context *p_ctx)
{
	t_bool		can_builtin;
	t_builtin	builtin_func;
	int			builtin_exit_status;
	int			tmp_fd[2];

	can_builtin = FALSE;
	builtin_func = check_builtin(argv[0]); 
	/* @ Built_in 함수도 fork 해야하는 경우가 있음. 관련사항 수정해야할 것들 주석
       pipe 노드의 후손중에 빌트인 함수가 있다면 해당 빌트인은 fork된 쉘의 exec_word로 실행해야함
	   pipe 노드의 후손이 아닌 빌트인 함수들은 원래처럼 우리의 부모 미니쉘이 그냥 실행하면됨
	*/
	if (builtin_func)
	{
		// @ exec_pipe내에서 재귀적으로 호출된 cmd라면
		// @ piped_cmd는 IPC로 통신해야함.(sigpipe, eof)
		if (p_ctx->is_piped_cmd)
			forked_builtin(p_ctx, builtin_func, argv);
		else
		{
			// @ builtin cmd에도 redirection이 필요함. 복구도 할 수 있어야 함.
			// @ redirect 및 redirect 정보 백업
			tmp_fd[STDIN] = dup(STDIN);
			tmp_fd[STDOUT] = dup(STDOUT);
			redirect_fd(p_ctx->fd);
			builtin_exit_status = builtin_func(argv);
			// @ redirect 및 redirect 정보 복구
			redirect_fd(tmp_fd);
			p_ctx->exit_status = builtin_exit_status;
			set_last_exit_status(p_ctx->exit_status);
		}
		can_builtin = TRUE;
	}
	return (can_builtin);
}

t_builtin	check_builtin(char *argv)
{
	if (argv[0] == 'c' && check_str(argv, 1, 1, "d"))
		return (ft_cd);
	else if (argv[0] == 'e')
	{
		if (argv[1] == 'c' && check_str(argv, 2, 2, "ho"))
			return (ft_echo);
		else if (argv[1] == 'x')
		{
			if (argv[2] == 'p' && check_str(argv, 3, 3, "ort"))
				return (ft_export);
			else if (argv[2] == 'i' && check_str(argv, 3, 1, "t"))
				return (ft_exit);
		}
		else if (argv[1] == 'n' && check_str(argv, 2, 1, "v"))
			return (ft_env);
	}
	else if (argv[0] == 'p' && check_str(argv, 1, 2, "wd"))
		return (ft_pwd);
	else if (argv[0] == 'u' && check_str(argv, 1, 4, "nset"))
		return (ft_unset);
	return (NULL);
}

static t_bool	check_str(char *argv, int idx, int size, char *sep)
{
	return (ft_memcmp(argv + idx, sep, size + 1) == 0);
}

void	exec_word(t_node *node, t_context *p_ctx)
{
	char	**argv;

	argv = make_argv(node->word);
	if (ft_strchr(argv[0], '/') == NULL)
	{
		if (exec_builtin(argv, p_ctx) == FALSE)
			search_and_fork_exec(argv, p_ctx);
	}
	else if (can_access(argv[0], p_ctx))
		fork_exec(argv, p_ctx);
	else
		fork_error(p_ctx);
	free_argv(argv);
}
