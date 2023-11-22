/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:29:47 by seykim            #+#    #+#             */
/*   Updated: 2023/09/18 13:29:48 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	printf("\n\
                    ____________   ____  ___   _____ __  __ \n\
                   / ____/_  __/  / __ )/   | / ___// / / / \n\
                  / /_    / /    / __  / /| | \\__ \\/ /_/ /  \n\
                 / __/   / /    / /_/ / ___ |___/ / __  /   \n\
                /_/     /_/    /_____/_/  |_/____/_/ /_/    \n\
\n");
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

void	print_eof_exit(void)
{
	ft_putstr_fd("\033[1A", STDOUT);
	ft_putstr_fd("\033[10C", STDOUT);
	printf("exit\n");
}

void	minishell_loop(void)
{
	t_node		*root;
	char		*line;

	sigact_default_mode();
	line = "";
	while (line)
	{
		set_heredoc_fault_flag(FALSE);
		line = readline("ft_bash > ");
		if (line)
		{
			if (*line != '\0')
				add_history(line);
			set_heredoc_eof_flag(FALSE);
			root = parser(line);
			execute(root);
			free_tree(root);
			free(line);
		}
	}
	print_eof_exit();
}
