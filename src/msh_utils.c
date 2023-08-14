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

int stauts = set_exit_status(p_ctx->exit_status);
if (stauts == 127)
{

}
else if (status == 126)
{
	
}
else
{
	status += 128;
}
//