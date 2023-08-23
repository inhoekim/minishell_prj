#include "../include/execute.h"
#include "../include/execute_util.h"
#include "../include/exec_node_util.h"

void	enqueue(pid_t pid, t_context *p_ctx);
void	wait_queue(t_context *p_ctx);
void	enqueue_after(pid_t pid, t_context *p_ctx);
void	wait_queue_after(t_context *p_ctx);
