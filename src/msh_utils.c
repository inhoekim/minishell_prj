#include <stdio.h>
#include "../libft/libft.h"
#include "../include/minishell.h"
# define STDERR_FD 2


void	syntax_error(t_tokenizer *tokenizer)
{
	t_token	token;

	token = get_curr_token(tokenizer);
	ft_putstr_fd("minishell : syntax error near unexpected token ", STDERR_FD);
	ft_putchar_fd('\'', STDERR_FD);
	ft_putstr_fd(token->str, STDERR_FD);
	ft_putchar_fd('\'', STDERR_FD);
	ft_putchar_fd("\n", STDERR_FD);
	set_exit_status(STDERR_FD);
}

void	exec_error(t_context *p_ctx)
{
	int status;
	
	status = set_exit_status(p_ctx->exit_status);
	if (status == 127)
		ft_putstr_fd("minishell : Command not found ", STDERR_FD);
	else if (status == 126)
		ft_putstr_fd("minishell : Permision Denied ", STDERR_FD);
	else
	{
		status += 128;
		set_exit_status(status);
		p_ctx->exit_status = status;
	}
}
