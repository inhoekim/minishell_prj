#ifndef WAIT_QUEUE_H
# define WAIT_QUEUE_H

# include "execute.h"

void	enqueue(pid_t pid, t_context *p_ctx);
void	wait_queue(t_context *p_ctx);
// void	ft_cir_lstclear(t_context *p_ctx);
void	ft_cir_lstadd_back(t_list **head, t_list *n_node);
void	enqueue_after(pid_t pid, t_context *p_ctx);
void	wait_queue_after(t_context *p_ctx);
#endif