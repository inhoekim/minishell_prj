/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:12:03 by seykim            #+#    #+#             */
/*   Updated: 2023/08/30 19:12:04 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"
#include <errno.h>

t_bool	*get_is_subshell(void);
t_list	**get_envp(void);

void	exec_word(t_node *node, t_context *p_ctx)
{
	char	**argv;

	argv = make_argv(node->word);
	if (ft_strchr(argv[0], '/') == NULL)
	{
		if (exec_builtin(argv, p_ctx) == FALSE)
			search_and_fork_exec(argv, p_ctx);
	}
	else if (can_access(argv[0], p_ctx))
		fork_exec(argv, p_ctx);
	else
		fork_error(p_ctx);
	free_argv(argv);
}

void	fork_exec(char **argv, t_context *p_ctx)
{
	int		pid;
	t_list	*envl;

	envl = *get_envp();
	if (!*get_is_subshell())
		sigact_fork_mode();
	pid = fork();
	if (pid == 0)
	{
		sigact_modeoff();
		dup2(p_ctx->fd[STDIN], STDIN);
		dup2(p_ctx->fd[STDOUT], STDOUT);
		if (p_ctx->fd_close >= 0)
			close(p_ctx->fd_close);
		execve(argv[0], argv, list_to_arr(envl));
		exit(1);
	}
	if (p_ctx->fd[STDIN] != STDIN)
		close(p_ctx->fd[STDIN]);
	if (p_ctx->fd[STDOUT] != STDOUT)
		close(p_ctx->fd[STDOUT]);
	cir_lstadd(pid, p_ctx);
}

char	**list_to_arr(t_list *node)
{
	char	**arr;
	int		i;
	int		len;
	t_list	*prev;

	i = 0;
	len = ft_lstsize(node);
	arr = ft_calloc(len + 1, sizeof(t_list));
	if (!arr)
		exit(ENOMEM);
	while (node)
	{
		prev = node;
		arr[i++] = node->content;
		node = node->next;
		free(prev);
	}
	return (arr);
}

// S_IFMT	0170000	bitmask for the file type bitfields
// S_IFDIR	0040000	directory
t_bool	can_access(char *filename, t_context *p_ctx)
{
	struct stat	buff;

	if (access(filename, F_OK) != 0)
	{
		msh_error(filename, NULL, ENOENT);
		p_ctx->exit_status = 127;
		return (FALSE);
	}
	stat(filename, &buff);
	if ((buff.st_mode & S_IFMT) == S_IFDIR)
	{
		msh_error(filename, NULL, EISDIR);
		p_ctx->exit_status = 126;
		return (FALSE);
	}
	else if (access(filename, X_OK) != 0)
	{
		msh_error(filename, NULL, EACCES);
		p_ctx->exit_status = 126;
		return (FALSE);
	}
	return (TRUE);
}

char	**make_argv(char **word_arr)
{
	int		i;
	t_list	*list;
	t_list	*argv_list;
	t_bool	glob_flag;

	i = 0;
	list = NULL;
	argv_list = NULL;
	glob_flag = FALSE;
	while (word_arr[i])
	{
		list = split_quotes(word_arr[i]);
		glob_flag = check_glob(list);
		arg_expansion(list);
		unquote(list);
		ft_lstadd_back(&argv_list, filename_expansion(list, glob_flag));
		ft_lstclear(&list, free);
		i++;
	}
	return (list_to_arr(argv_list));
}
