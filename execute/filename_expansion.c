#include "../include/minishell.h"
#include "../include/exec_word_util.h"
#include "../include/filename_expansion.h"

t_list	*filename_expansion(t_list *list, t_bool glob_flag)
{
	t_list	*expanded_list;
	char	*pattern;

	pattern = concatenate(list);
	if (!pattern)
        set_exit_status(ENOMEM);
	if (glob_flag)
	{
		expanded_list = globbing(pattern);
		if (expanded_list)
		{
			free(pattern);
			return (expanded_list);
		}
	}
	return (ft_lstnew(pattern));
}

char	*concatenate(t_list *list)
{
	int		str_size;
	char	*content;
	char	*pattern;
	t_list	*head;

	head = list;
	str_size = 0;
	while (list)
	{
		str_size += ft_strlen(list->content);
		list = list->next;
	}
	pattern = malloc(sizeof(char) * str_size + 1);
    if (!pattern)
        return (NULL);
	pattern[str_size] = '\0';
	list = head;
	while (list)
	{
		content = list->content;
		ft_strlcat(pattern, content, str_size + 1);
		list = list->next;
	}
	return (pattern);
}

t_list	*globbing(char *pattern)
{
	t_list			*matches;
	DIR				*dp;
	char			dirbuf[PATH_MAX];
	struct dirent	*dir;

	matches = NULL;
	getcwd(dirbuf, PATH_MAX);
	dp = opendir(dirbuf);
	dir = readdir(dp);
	while (dir != NULL)
	{
		dir = readdir(dp);
		if (dir && dir->d_type == DT_REG && is_match(dir->d_name, pattern))
			ft_lstadd_back(&matches, ft_lstnew(ft_strdup(dir->d_name)));
	}
	closedir(dp);
	return (matches);
}

int is_match(char *pattern, char *word)
{
	int len_p, len_w;
	int **dp;

	len_p = ft_strlen(pattern);
	len_w = ft_strlen(word);
	dp = allocate_dp(len_p, len_w);
	dp[0][0] = 1;
	if (pattern[0] == '*')
		dp[1][0] = 1;
	else
		dp[1][0] = 0;
	for (int pattern_idx = 1; pattern_idx <= len_p; pattern_idx++)
	{
		for (int word_idx = 1; word_idx <= len_w; word_idx++)
		{
			if (pattern[pattern_idx - 1] == '?' || \
					pattern[pattern_idx - 1] == word[word_idx - 1])
			{
				dp[pattern_idx][word_idx] = dp[pattern_idx - 1][word_idx - 1];
			}
			else if (pattern[pattern_idx - 1] == '*') {
				dp[pattern_idx][word_idx] = \
				dp[pattern_idx - 1][word_idx] || dp[pattern_idx][word_idx - 1];
			}
		}
	}
	return (dp[len_p][len_w]);
}


void	msh_error(char *name, char *msg, int error)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (msg == NULL && error == 0)
	{
		perror(name);
		return ;
	}
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	else if (error)
		ft_putendl_fd(strerror(error), STDERR_FILENO);
}

// char	*cmd_path_find(char *cmd, char **envp)
// {
// 	char	**env_pt;
// 	char	**res1;
// 	char	**res2;
// 	int		i;
// 	char	*cmd_path;

// 	env_pt = envp;
// 	while (*env_pt)
// 	{
// 		res1 = ft_split(*(env_pt++), '=');
// 		if (!ft_strncmp(res1[0], "PATH", 4))
// 		{
// 			res2 = ft_split(res1[1], ':');
// 			i = 0;
// 			while (res2[i])
// 			{
// 				cmd_path = ft_strjoin(res2[i++], cmd);
// 				if (access(cmd_path, X_OK) != -1)
// 					return (cmd_path);
// 			}
// 			free(res2);
// 			free(res1);
// 		}
// 	}
// 	return (0);
// }