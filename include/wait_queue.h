#include "../include/execute.h"
#include "../include/execute_util.h"
#include "../include/exec_node_util.h"

#define WORKING 0

void	enqueue(pid_t pid, t_context *p_ctx);
void	wait_queue(t_context *p_ctx);
void	ft_cir_lstclear(t_context *p_ctx);
void	ft_cir_lstadd_back(t_list **head, t_list *n_node);
void	enqueue_after(pid_t pid, t_context *p_ctx);
void	wait_queue_after(t_context *p_ctx);
