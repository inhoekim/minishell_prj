#include <stdio.h>
#include "../libft/libft.h"
#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/execute.h"
#include "../include/execute_util.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init_envp(envp);
	minishell_loop();
	// free_parser();
	// free_tree();
}

void	init_envp(char **envp)
{
	t_list	**env;
	int		idx;

	env = get_envp();
	idx = 0;
	ft_lstadd_back(env, NULL);
	while (envp[idx])
	{
		ft_lstadd_back(env, ft_lstnew(ft_strdup(envp[idx])));
		idx++;
	}
}

t_list	**get_envp(void)
{
	static t_list	*env_list;

	return (&env_list);
}

void	new_prompt(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	set_exit_status(1);
}

void	sigact_default(void)
{
	struct sigaction	intsig;
	struct sigaction	quitsig;
	struct termios		attributes;

	tcgetattr(STDIN, &attributes);
	attributes.c_lflag &= (~ECHOCTL);
	tcsetattr(STDIN, TCSANOW, &attributes);
	intsig.sa_handler = new_prompt;
	sigemptyset(&intsig.sa_mask);
	intsig.sa_flags = 0;
	sigaction(SIGINT, &intsig, 0);
	quitsig.sa_handler = SIG_IGN;
	sigemptyset(&quitsig.sa_mask);
	quitsig.sa_flags = 0;
	sigaction(SIGQUIT, &quitsig, 0);
}

void	minishell_loop(void)
{
	t_node		*root;
	char		*line;

	sigact_default();
	line = ft_strdup("");
	while (line)
	{
		line = readline("prompt> ");
		if (line)
		{
			if (*line != '\0')
				add_history(line);
			root = parser(line);
			execute(root);
			free(line);
		}
	}
	ft_putstr_fd("\033[1A", STDOUT);
	ft_putstr_fd("\033[8C", STDOUT);
	printf("exit\n");
}
