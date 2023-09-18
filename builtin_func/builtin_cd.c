/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:27:06 by seykim            #+#    #+#             */
/*   Updated: 2023/09/18 13:48:23 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

static char	*vaild_env(char **temp);
static char	*special_case(char **temp);
static void	cd_util(char *newpwd);

t_bool	ft_cd(char **argv)
{
	char	path[PATH_MAX];
	char	*can_env;
	char	*newpwd;

	can_env = vaild_env(argv);
	if (!can_env)
	{
		ft_putendl_fd("cd : HOME not set", STDERR_FILENO);
		return (1);
	}
	newpwd = getcwd(path, PATH_MAX);
	if (chdir(can_env) != 0)
	{
		ft_putstr_fd("cd : ", STDERR_FILENO);
		ft_putstr_fd(can_env, STDERR_FILENO);
		ft_putendl_fd(" : No such directory", STDERR_FILENO);
		free(can_env);
		return (1);
	}
	cd_util(newpwd);
	free(can_env);
	return (0);
}

static void	cd_util(char *newpwd)
{
	char	*temp;
	char	path[PATH_MAX];

	if (newpwd)
		set_envp("OLDPWD", newpwd);
	else
	{
		newpwd = ft_getenv("PWD");
		temp = ft_getenv("OLDPWD");
		set_envp("OLDPWD", newpwd);
		set_envp("PWD", temp);
		free(temp);
		free(newpwd);
	}
	newpwd = getcwd(path, PATH_MAX);
	if (newpwd)
		set_envp("PWD", newpwd);
}

static char	*vaild_env(char **temp)
{
	int		size;
	char	*parameter;

	size = 0;
	parameter = 0;
	while (temp[size])
		size++;
	if (size == 1)
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
