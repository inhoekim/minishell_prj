/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:27:11 by seykim            #+#    #+#             */
/*   Updated: 2023/09/18 13:27:12 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

t_bool	ft_echo(char **argv)
{
	int		idx;
	int		flag;

	flag = 0;
	idx = 0;
	if (!argv[1])
	{
		printf("\n");
		return (0);
	}
	else if (argv[1][0] == '-' && argv[1][1] == 'n')
	{
		idx = 1;
		flag = 1;
	}
	while (argv[++idx])
	{
		if (argv[idx + 1] != NULL)
			printf("%s ", argv[idx]);
		else
			printf("%s", argv[idx]);
	}
	if (flag == 0)
		printf("\n");
	return (0);
}

t_bool	ft_pwd(char **argv)
{
	char	path[PATH_MAX];

	(void)argv;
	getcwd(path, PATH_MAX);
	printf("%s\n", path);
	return (0);
}
