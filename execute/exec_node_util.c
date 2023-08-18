#include "../include/minishell.h"
#include "../include/execute.h"
#include "../include/exec_node_util.h"
#include "../include/exec_word_util.h"
#include "../include/make_argv_util.h"
#include "../include/execute_util.h"
#include "../include/filename_expansion.h"


// waitpid, enqueue -> 주석 처리
// or, and -> int pid remove
// word.buf -> word[0] change / seykim 8/16
void	exec_subshell(t_node *node, t_context *p_ctx)
{
	int		pid;
	t_node	*lhs;

	lhs = node->left;
	pid = fork();
	if (pid)
	{
		exec_node(lhs, p_ctx);
		// wait_queue();
	}
	waitpid(pid, 0, 0);
	// enqueue(pid);
	// wait_queue();
}

void	exec_or(t_node *node, t_context *p_ctx)
{
	t_node	*lhs;
	t_node	*rhs;

	lhs = node->left;
	rhs = node->right;
	exec_node(lhs, p_ctx);
	if (p_ctx->exit_status != 0)
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
	if (p_ctx->exit_status == 0)
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

char	*make_order(char **path, char **argv, t_context *p_ctx)
{
	int		idx;
	int		total;
	char	*order;

	idx = 0;
	order = 0;
	while (path[idx])
	{
		total = ft_strlen(path[idx]) + ft_strlen(argv[0]) + 1;
		order = (char *)malloc(sizeof(char) * total + 1);
		if (!order)
			return (NULL);
		order = ft_strjoin(path[idx], argv[0]);
		// @ if (access(order, X_OK) != -1)의 역할은 can_access가 하기때문에 필요없어보임
		if (access(order, X_OK) != -1)
		{
			if (can_access(order, p_ctx))
				break ;
		}
		free(order);
		order = 0;
		idx++;
	}
	return (order);
}

void	search_and_fork_exec(char **argv, t_context *p_ctx)
{
	char	*order;
	char	**path;
	pid_t	pid;

	path = ft_split2(ft_getenv("PATH"), ':');
	// @ unset PATH
	order = make_order(path, argv, p_ctx);
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
	(void)pid;
	// @ fork_exec와 기능이 같아서 수정했음
	// pid = fork();
	// if (pid == 0)
	// {
	// 	dup2(p_ctx->fd[STDIN], STDIN);
	// 	dup2(p_ctx->fd[STDOUT], STDOUT);
	// 	if (p_ctx->fd_close >= 0)
	// 	{
	// 		close(p_ctx->fd_close);
	// 		p_ctx->fd_close = -1;
	// 	}
	// 	if (!order)
	// 		msh_error(argv[0], "command not found", 0);
	// 	execve(order, argv, list_to_arr(*get_envp()));
	// 	exit(1);
	// }
	// set_ctx_status(p_ctx, pid, 0);
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

	can_builtin = FALSE;
	builtin_func = check_builtin(argv[0]);
	if (builtin_func)
	{
		builtin_func(argv);
		can_builtin = TRUE;
		// printf("not make builtin_func build\n");
		// exit(1);
	}
	return (can_builtin);
}
// cd, env, export, unset, exit, echo, pwd
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
			//	export 추가하는 파트에서 export test=3 입력시, export, test=3이 들어감
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

	// node에 저장된 cmd line argument 배열 parsing
	argv = make_argv(node->word);
	// 빌드인 or PATH에 경로등록 or 현재 디렉토리에 존재하는 명령
	if (ft_strchr(argv[0], '/') == NULL)
	{
		// 빌트인
		if (exec_builtin(argv) == FALSE)
			// PATH(argv에 경로를 붙혀서 실행해야하는 경우), 현재 디렉토리 search
			search_and_fork_exec(argv, p_ctx);
			
	}
	// 경로가 명시된 경우(상대경로 or 절대경로)
	else if (can_access(argv[0], p_ctx))
		fork_exec(argv, p_ctx);
		
	set_exit_status(p_ctx->exit_status);
	free_argv(argv);
}
