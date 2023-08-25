#include <stdio.h>
#include "../libft/libft.h"
#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/execute.h"
#include "../include/execute_util.h"
#include "../include/here_doc.h"
#include "../include/ms_signal.h"

void __leak()
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	atexit(__leak);
	(void)argc;
	(void)argv;
	init_envp(envp);
	minishell_loop();
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

void	minishell_loop(void)
{
	t_node		*root;
	char		*line;

	sigact_default_mode();
	line = ft_strdup("");
	while (line)
	{
		set_heredoc_fault_flag(FALSE);
		set_cursor_size(0);
		line = readline("prompt> ");
		if (line)
		{
			if (*line != '\0')
				add_history(line);
			set_heredoc_visit_flag(FALSE);
			root = parser(line);
			execute(root);
			free(line);
		}
	}
	ft_putstr_fd("\033[1A", STDOUT);
	for (int i = 1; i <= get_heredoc_data()->cursor_size; i++)
		ft_putstr_fd("\033[2C", STDOUT);
	ft_putstr_fd("\033[8C", STDOUT);
	printf("exit\n");
}
