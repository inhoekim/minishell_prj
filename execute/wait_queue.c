#include "../include/wait_queue.h"
#include "../include/execute.h"

#if WORKING == 0
void	enqueue_after(pid_t pid, t_context *p_ctx)
{
	if (PROC_MAX <= p_ctx->queue_size)
		exit(1);
	p_ctx->queue[p_ctx->queue_size] = pid;
	p_ctx->queue_size++;
}

void	wait_queue_after(t_context *p_ctx)
{
	int	idx;
	int	size;

	idx = 0;
	size = p_ctx->queue_size;
	while (idx < size)
	{
		wait_and_set_exit_status(p_ctx->queue[idx], p_ctx, 0);
		idx++;
		p_ctx->queue_size--;
	}
	sigact_default_mode();
}
#endif

#if WORKING == 1

void	ft_cir_lstclear(t_context *p_ctx)
{
	t_list *current;
	t_list *tmp;
	t_list **head;

	head = &(p_ctx->pid_list);
	current = (*head);
	while (current->next != *head)
	{
		tmp = current;
		current = current->next;
		ft_lstdelone(tmp, free);
	}
	ft_lstdelone(current, free);
}

void	ft_cir_lstadd_back(t_list **head, t_list *n_node)
{
	t_list	*tmp;

	if (*head == NULL)
	{
		*head = n_node;
		(*head)->next = *head;
	}
	else
	{
		tmp = *head;
		while (tmp->next != *head)
			tmp = tmp->next;
		tmp->next = n_node;
		n_node->next = *head;
	}
}

void	enqueue_after(pid_t pid, t_context *p_ctx)
{
	int	*_pid = (int *)malloc(sizeof(int));

	*_pid = pid;
	ft_cir_lstadd_back(&p_ctx->pid_list, ft_lstnew(_pid));
	p_ctx->pid_size++;
}

t_list	*ft_cir_lstdelete_node(t_list **head, t_list *d_node)
{
	t_list *prev;
	t_list *current;
	t_list *tmp;

	prev = *head;
	current = (*head)->next;
	// {echo , cat}
	while (current != d_node)
	{
		prev = current;
		current = current->next;
	}
	// list의 원소가 하나이고 *head == d_node인 경우
	if (current == *head && prev == *head)
	{
		ft_lstdelone(d_node, free);
		return (NULL);
	}
	// list의 원소가 하나가 아니고 *head == d_node인 경우
	else if (current == *head)
	{
		tmp = *head;
		while (tmp->next != *head)
			tmp = tmp->next;
		*head = current->next;
		tmp->next = *head;
		ft_lstdelone(current, free);
	}
	// 그 외
	else
	{
		prev->next = current->next;
		ft_lstdelone(current, free);
	}
	return (prev);
}

void	*wait_and_set_exit_status_n(t_list *node, t_context *p_ctx, int flag)
{
	int		status;
	pid_t	pid;
	t_list	*ret;

	ret = NULL;
	pid = *((int *)node->content);
	waitpid(pid, &status, flag);
	if (WIFEXITED(status))
	{
		// printf("exit: %d\n", WEXITSTATUS(status));
		p_ctx->exit_status = WEXITSTATUS(status);
		set_exit_status(p_ctx->exit_status);
		ret = ft_cir_lstdelete_node(&p_ctx->pid_list, node);
		p_ctx->pid_size--;
	}
	else if (WIFSIGNALED(status) && WTERMSIG(status) != 88)
	{
		// printf("signal: %d\n", WTERMSIG(status));
		p_ctx->exit_status = WTERMSIG(status) + 128;
		set_exit_status(p_ctx->exit_status);
		ret = ft_cir_lstdelete_node(&p_ctx->pid_list, node);
		p_ctx->pid_size--;
	}
	return (ret);
}
// #include <setjmp.h>

// sigjmp_buf env;
// struct sigaction sa;

// void delete_zombies(void);

// sigfillset(&sa.sa_mask);
// sa.sa_handler = delete_zombies;
// sa.sa_flags = 0;
// sigaction(SIGCHLD, &sa, NULL);

// void delete_zombies(void)
// {
//     pid_t kidpid;
//     int status;

//     printf("Inside zombie deleter:  ");
//     while ((kidpid = waitpid(-1, &status, WNOHANG)) > 0)
//     {
//          printf("Child %ld terminated\n", kidpid);
//     }
//     siglongjmp(env,1);
// }

void	wait_queue_after(t_context *p_ctx)
{
	t_list	*_pid_list;

	_pid_list = p_ctx->pid_list;
	// @ 지금 여기 있는 list node는 {echo, cat}이다. 
	while (_pid_list && p_ctx->pid_size)
	{

		_pid_list = wait_and_set_exit_status_n(_pid_list, p_ctx, 0);
		if (!_pid_list)
			break;
		_pid_list = _pid_list->next;
	}
}

#endif

