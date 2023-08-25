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

void	exec_subshell(t_node *node, t_context *p_ctx)
{
	int		pid;
	t_node	*lhs;

	lhs = node->left;
	pid = fork();
	if (pid == 0)
	{
		exec_node(lhs, p_ctx);
		//여기서 자식쉘의 pipe[stdin]과 fork할 ls의 pipe[stdin]은 닫힘
		if (p_ctx->fd_close >= 0)
			close(p_ctx->fd_close);
		wait_queue_after(p_ctx);
		exit(p_ctx->exit_status);
	}
	//(ls) | cat 에서 exec_subshell은 1번만 호출되는데
	//여기서 들어갈때 p_ctx->fd[0] = stdin / p_ctx->fd[1] = pipe[stdout]
	//그래서 부모쉘의 pipe[stdout]은 닫히는데 pipe[stdin]이 안닫히는 것 같아요
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
	wait_queue_after(p_ctx);
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
	wait_queue_after(p_ctx);
	if (*get_exit_status() == 0)
	{
		exec_node(rhs, p_ctx);
	}
}

#if WORKING == 0
void	copy_queue(t_context *dst, t_context *src)
{
	int	idx;
	int	size;

	idx = 0;
	size = src->queue_size;
	while (idx < size)
	{
		dst->queue[idx] = src->queue[idx];
		idx++;
	}
	dst->queue_size = idx;
	dst->exit_status = src->exit_status;
}
#endif

#if WORKING == 1
void	copy_queue(t_context *dst, t_context *src)
{
	t_list *current;
	t_list	**head;

	printf("copy state: %p %p %d\n", src->pid_list, src->pid_list->content, *((int *)(src->pid_list->content)));
	// clear dst
	if (dst->pid_list)
	{
		ft_cir_lstclear(dst);
		dst->pid_list = NULL;
	}
	printf("copy state: %p %p %d\n", src->pid_list, src->pid_list->content, *((int *)(src->pid_list->content)));
	head = &(src->pid_list);
	printf("copy state: %p %p %d\n", src->pid_list, *head, *((int *)(src->pid_list->content)));
	current = *head;
	printf("copy state: %p %p %d\n", current, current->content, *((int *)(current->content)));
	while (current->next != *head)
	{	
		ft_cir_lstadd_back(&dst->pid_list, current);
		
		// printf("pid: %d\n", *(int *)(current->content));
		// ft_cir_lstadd_back(&dst->pid_list, ft_lstnew(current->content));
		// free(current->content);
		// @ current->content도 복사되어야 함.
		current = current->next;
	}
	ft_cir_lstadd_back(&dst->pid_list, current);
	dst->pid_size = src->pid_size;
	dst->exit_status = src->exit_status;
}
#endif

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
	// *p_ctx와 aux가 pid_list의 주소를 공유하고 있음
	// *p_ctx에 새로 복사하기 위해 초기화
	p_ctx->pid_list = NULL;
	copy_queue(p_ctx, &aux);
	// @ piped_command에서 fork된 pid는 aux.queue에 반영되어있음.
	// @ ctx.queue에도 반영해야 함.
	// @ aux.queue -> ctx.queue 로 queue복사
	aux = *p_ctx;
	aux.fd[STDIN] = pipe_fd[STDIN];
	aux.fd_close = pipe_fd[STDOUT];
	exec_node(rhs, &aux);
	printf("aux state: %p %p %d\n", aux.pid_list, aux.pid_list->content, *((int *)(aux.pid_list->content)));
	// *p_ctx와 aux가 pid_list의 주소를 공유하고 있음
	// *p_ctx에 새로 복사하기 위해 초기화
	p_ctx->pid_list = NULL;
	copy_queue(p_ctx, &aux);
	printf("not seg\n");
	// @ piped_command에서 fork된 pid는 aux.queue에 반영되어있음.
	// @ ctx.queue에도 반영해야 함.
	// @ aux.queue -> ctx.queue 로 queue 복사
	

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

t_bool *get_redirect_ambiguity(void)
{
	static t_bool redirect_ambiguity;
	return (&redirect_ambiguity);
}

void set_redirect_ambiguity(t_bool value)
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
		return ;
	set_redirect_ambiguity(FALSE);
	if (!is_regular_file(filename[0], p_ctx))
	{
		set_exit_status(p_ctx->exit_status);
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
		return ;
	set_redirect_ambiguity(FALSE);
	if (!is_not_directory(filename[0], p_ctx))
	{
		set_exit_status(p_ctx->exit_status);
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
		return ;
	set_redirect_ambiguity(FALSE);
	if (!is_not_directory(filename[0], p_ctx))
	{
		set_exit_status(p_ctx->exit_status);
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
		msh_error(argv[0], "command not found", 0);
	}
	free_argv(path);
	free(temp_path);
}

void	wait_and_set_exit_status(pid_t pid, t_context *p_ctx, int flag)
{
	int	status;

	waitpid(pid, &status, flag);
	if (WIFEXITED(status))
	{
		p_ctx->exit_status = WEXITSTATUS(status);
		set_exit_status(p_ctx->exit_status);
	}
	else if (WIFSIGNALED(status))
	{
		p_ctx->exit_status = WTERMSIG(status) + 128;
		if (status == 13)
		{
			set_exit_status(p_ctx->exit_status);
			return ;
		}
		set_exit_status(p_ctx->exit_status);
	}
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
		if (p_ctx->is_piped_cmd)
		{
			// @ piped_cmd는 IPC로 통신해야함.(sigpipe, eof)
			// @ fork후 builtin_func(argv); 실행
			// @ "fork후 builtin_func(argv)"에는 sigaction set(fork interactive mode) 포함해야 함.
			forked_builtin(p_ctx, builtin_func, argv);
			// @ sigint(2) 컨트롤+c -> exit(2)
			// @ sigquit(3) 컨트롤+d -> exit(3)
			// @ is_piped_cmd는 가장 조상 pipe가 끝나면서(재귀적으로는 첫번째 pipe함수) 0으로 초기화 되어야함
		}
		else
		{
			// @ builtin cmd에도 redirection이 필요함. 복구도 할 수 있어야 함.
			// @ redirect 및 redirect 정보 백업
			// redirect_and_p_ctx_fd_copy(p_ctx, tmp);
			tmp_fd[STDIN] = dup(STDIN);
			tmp_fd[STDOUT] = dup(STDOUT);
			redirect_fd(p_ctx->fd);
			builtin_exit_status = builtin_func(argv);
			// @ redirect 및 redirect 정보 복구
			// p_ctx_fd_copy(tmp, p_ctx);
			redirect_fd(tmp_fd);
			p_ctx->exit_status = builtin_exit_status;
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
	set_exit_status(p_ctx->exit_status);
	free_argv(argv);
}
