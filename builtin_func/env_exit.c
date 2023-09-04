/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasong <dasong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:11:10 by seykim            #+#    #+#             */
/*   Updated: 2023/09/04 17:50:20 by dasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

t_bool	ft_env(char **argv)
{
	t_list	**env;
	t_list	*tp;
	int		ret;
	char	*tp_str;

	(void)argv;
	env = get_envp();
	tp = *env;
	while (tp != NULL)
	{
		ret = check_argv((char *)tp->content);
		if (ret != 0)
		{
			if (ret == 3)
			{
				tp_str = ft_substr(tp->content, 0, ft_strlen(tp->content) - 2);
				printf("%s\n", tp_str);
				free(tp_str);
			}
			else
				printf("%s\n", (char *)tp->content);
		}
		tp = tp->next;
	}
	return (0);
}

t_bool	ft_exit(char **argv)
{
	if (argv[1] != 0)
	{
		if (argv[2] != 0)
		{
			printf("exit: Too many arguments\n");
			exit(1);
		}
		exit_utils(argv);
		printf("exit\n");
		exit(ft_atoi(argv[1]));
	}
	else
	{
		printf("exit\n");
		exit(0);
	}
	return (1);
}

void	exit_utils(char **temp)
{
	int	idx;

	idx = 0;
	while (temp[1][idx])
	{
		if (temp[1][idx] == '-' || temp[1][idx] == '+')
			idx++;
		if (ft_isdigit(temp[1][idx]) == 0)
		{
			printf("exit: %s: numeric argument required", temp[1]);
			exit(255);
		}
		idx++;
	}
}
