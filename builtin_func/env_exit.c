/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:11:10 by seykim            #+#    #+#             */
/*   Updated: 2023/08/30 19:11:11 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

static t_bool	check_long_range(long long *num, char ch_num, int sign);

t_bool	ft_env(char **argv)
{
	t_list	**env;
	t_list	*temp;

	(void)argv;
	env = get_envp();
	temp = *env;
	while (temp != NULL)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
	return (0);
}

t_bool	ft_exit(char **argv)
{
	if (argv[1] != 0)
	{
		exit_utils(argv);
		if (argv[2] != 0)
		{
			ft_putendl_fd("exit", STDOUT);
			ft_putendl_fd("exit: too many arguments", STDOUT);
			exit(1);
			return (1);
		}
		ft_putendl_fd("exit", STDOUT);
		exit(ft_atoi(argv[1]));
	}
	ft_putendl_fd("exit", STDOUT);
	exit(0);
	return (0);
}

void	exit_utils(char **temp)
{
	int			idx;
	long long	num;
	int			sign;

	idx = 0;
	num = 0;
	sign = 1;
	if (temp[1][idx] == '-' || temp[1][idx] == '+')
	{
		if (temp[1][idx++] == '-')
			sign = -1;
	}
	while (temp[1][idx])
	{
		if (!ft_isdigit(temp[1][idx]) || \
		!check_long_range(&num, temp[1][idx], sign))
		{
			printf("exit\n");
			printf("exit: %s: numeric argument required\n", temp[1]);
			exit(255);
		}
		idx++;
	}
}

static t_bool	check_long_range(long long *num, char ch_num, int sign)
{
	if (*num > 922337203685477580)
		return (FALSE);
	if (*num == 922337203685477580 && ch_num - '0' > 7)
	{
		if (sign == -1 && ch_num - '0' == 8)
		{
			*num = (*num * 10);
			return (TRUE);
		}
		return (FALSE);
	}
	*num = (*num * 10) + (ch_num - '0');
	return (TRUE);
}