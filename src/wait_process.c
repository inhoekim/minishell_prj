/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:29:51 by seykim            #+#    #+#             */
/*   Updated: 2023/09/18 13:29:53 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	wait_list(t_context *p_ctx)
{
	t_list	*_pid_list;

	_pid_list = p_ctx->pid_list;
	while (_pid_list && p_ctx->pid_size)
	{
		_pid_list = wait_process(_pid_list, p_ctx, WNOHANG);
		if (!_pid_list)
			break ;
		_pid_list = _pid_list->next;
	}
	p_ctx->pid_list = NULL;
	sigact_default_mode();
}

void	*wait_process(t_list *node, t_context *p_ctx, int flag)
{
	int		status;
	pid_t	pid;
	t_list	*ret;
	int		wnohang_ret;

	ret = node;
	pid = *((int *)node->content);
	status = 0;
	wnohang_ret = waitpid(pid, &status, flag);
	if (!wnohang_ret)
		return (ret);
	else if (WIFEXITED(status))
	{
		p_ctx->exit_status = WEXITSTATUS(status);
		_wait_process(&ret, p_ctx, node, pid);
	}
	else if (WIFSIGNALED(status))
	{
		p_ctx->exit_status = WTERMSIG(status) + 128;
		_wait_process(&ret, p_ctx, node, pid);
	}
	return (ret);
}

void	_wait_process(t_list **ret, t_context *p_ctx, t_list *node, pid_t pid)
{
	*ret = _delete_process(&p_ctx->pid_list, node);
	p_ctx->pid_size--;
	if (pid == *get_last_pid())
		set_last_exit_status(p_ctx->exit_status);
}

void	cir_lstadd(pid_t pid, t_context *p_ctx)
{
	int	*_pid;

	if (PROC_MAX <= p_ctx->pid_size)
	{
		printf("minishell: Process size over.\n");
		return ;
	}
	_pid = (int *)malloc(sizeof(int));
	if (!_pid)
		exit(ENOMEM);
	*_pid = pid;
	cir_lstadd_back(&p_ctx->pid_list, ft_lstnew(_pid));
	p_ctx->pid_size++;
}

void	cir_lstadd_back(t_list **head, t_list *n_node)
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
