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
	printf("added size: %d\n", p_ctx->pid_size);
}

t_list	*ft_cir_lstdelete_node(t_list **head, t_list *d_node)
{
	t_list *prev;
	t_list *current;
	t_list *tmp;

	prev = *head;
	current = (*head)->next;
	while (current != d_node)
	{
		prev = current;
		current = current->next;
	}
	printf("here0-0\n");
	// list의 원소가 하나이고 *head == d_node인 경우
	if (current == *head && prev == *head)
	{
		printf("here0-1\n");
		printf("%p %p\n", d_node->content, d_node);
		ft_lstdelone(d_node, free); // seg
		printf("here0-2\n");
		return (NULL);
	}
	// list의 원소가 하나가 아니고 *head == d_node인 경우
	else if (current == *head)
	{
		printf("here0-3\n");
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
		printf("here0-4\n");
		prev->next = current->next;
		ft_lstdelone(current, free);
	}
	return (prev);
}

void	wait_and_set_exit_status_n(t_list *node, t_context *p_ctx, int flag)
{
	int		status;
	pid_t	pid;

	pid = *((int *)node->content);
	waitpid(pid, &status, flag);
	if (WIFEXITED(status))
	{
		printf("exit: %d\n", WEXITSTATUS(status));
		p_ctx->exit_status = WEXITSTATUS(status);
		set_exit_status(p_ctx->exit_status);
		printf("here0\n");
		ft_cir_lstdelete_node(&p_ctx->pid_list, node); // seg
		printf("here1\n");
		p_ctx->pid_size--;
	}
	else if (WIFSIGNALED(status) && WTERMSIG(status) != 88)
	{
		printf("signal: %d\n", WTERMSIG(status));
		p_ctx->exit_status = WTERMSIG(status) + 128;
		set_exit_status(p_ctx->exit_status);
		printf("here3\n");
		ft_cir_lstdelete_node(&p_ctx->pid_list, node);
		printf("here4\n");
		p_ctx->pid_size--;
	}
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
	printf("head: %p size: %d\n", _pid_list, p_ctx->pid_size);
	// @ 지금 여기 있는 list node는 {echo, cat}이다. 
	while (_pid_list && p_ctx->pid_size)
	{
		printf("start\n");
		wait_and_set_exit_status_n(_pid_list, p_ctx, 0);
		printf("end\n");
		_pid_list = _pid_list->next;
	}
}

#endif

