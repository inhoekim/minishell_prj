/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:11:03 by seykim            #+#    #+#             */
/*   Updated: 2023/08/30 19:11:04 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

static char	*vaild_env(char **temp);
static char	*special_case(char **temp);

t_bool	ft_cd(char **argv)
{
	char	path[PATH_MAX];
	char	*can_env;
	char	*newpwd;

	can_env = vaild_env(argv);
	if (!can_env)
	{
		write(STDERR_FILENO, "cd: Too many arguments\n", 24);
		return (1);
	}
	newpwd = getcwd(path, PATH_MAX);
	if (chdir(can_env) != 0)
	{
		write(STDERR_FILENO, "cd : No such file or directory\n", 32);
		return (1);
	}
	set_envp("OLDPWD", newpwd);
	newpwd = getcwd(path, PATH_MAX);
	set_envp("PWD", newpwd);
	free(can_env);
	return (0);
}

static char	*vaild_env(char **temp)
{
	int		size;
	char	*parameter;

	size = 0;
	parameter = 0;
	while (temp[size])
		size++;
	if (size > 2)
		return (NULL);
	else if (size == 1)
		return (ft_getenv("HOME"));
	parameter = special_case(temp);
	if (!parameter)
		parameter = ft_strdup(temp[1]);
	return (parameter);
}

static char	*special_case(char **temp)
{
	size_t	temp_len;
	char	*parameter;

	temp_len = ft_strlen(temp[1]);
	parameter = 0;
	if (temp_len == 1 && ft_strncmp(temp[1], "~", 1) == 0)
		parameter = ft_getenv("HOME");
	else if (temp_len == 1 && ft_strncmp(temp[1], ".", 1) == 0)
		return (ft_strdup("."));
	else if (temp_len == 2 && ft_strncmp(temp[1], "..", 2) == 0)
		parameter = ft_strdup("..");
	return (parameter);
}
