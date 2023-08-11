#include "../include/minishell.h"
#include <fcntl.h>

#define STDIN 0
#define STDOUT 1

typedef struct s_context
{
	int	exit_status;
	int	fd[2];
	int	fd_close;
	int	exit_status;
}	t_context;


t_bool	execute(t_node *root)
{
	t_bool		check_exit;
	t_node		*node;
	t_context	ctx;

	ctx.fd_close = -1;
	check_exit = FALSE;
	node = exec_node(root, &ctx);
	if (node->type != E0F)
	{
		syntax_error();
	}
	return (check_exit);
}

t_node *exec_node(t_node *node, t_context *p_ctx)
{
	if (node == NULL)
		return ;
	else if(node->type == WORD) {
		exec_word(node, p_ctx);
	}
	else if(node->type == LESS) {
		exec_input(node, p_ctx);
	}
	else if(node->type == GREAT) {
		exec_output(node, p_ctx);
	}
	else if(node->type == DGREAT) {
		exec_append(node, p_ctx);
	}
	else if(node->type == DLESS) {
		exec_heredoc(node, p_ctx);
	}
	else if(node->type == AND_IF) {
		exec_and(node, p_ctx);
	}
	else if(node->type == OR_IF) {
		exec_or(node, p_ctx);
	}
	else if(node->type == PIPE) {
		exec_pipe(node, p_ctx);
	}
	else if(node->type == SUBSHELL) {
		exec_subshell(node, p_ctx);
	}
}

// void	exec_subshell(t_node *node, t_ctx *p_ctx)
// {
// 	int		pid;
// 	t_node	*lhs;

// 	lhs = node->left;
// 	pid = fork();
// 	if (pid)
// 	{
// 		exec_word(lhs, p_ctx);
// 		wait_queue();
// 	}
// 	enqueue(pid);
// 	wait_queue();
// }

// void	exec_or(t_node *node, t_ctx *p_ctx)
// {
// 	int		pid;
// 	t_node	*lhs;
// 	t_node	*rhs;

// 	lhs = node->left;
// 	rhs = node->right;
// 	exec_word(lhs, p_ctx);
// 	if (p_ctx->exit_status != 0)
// 	{
// 		exec_word(rhs, p_ctx);
// 	}
// }

// void	exec_and(t_node *node, t_ctx *p_ctx)
// {
// 	int		pid;
// 	t_node	*lhs;
// 	t_node	*rhs;

// 	lhs = node->left;
// 	rhs = node->right;
// 	exec_word(lhs, p_ctx);
// 	if (p_ctx->exit_status == 0)
// 	{
// 		exec_word(rhs, p_ctx);
// 	}
// }

// void exec_pipe(t_node *node, t_ctx *p_ctx)
// {
// 	t_node	*lhs;
// 	t_node	*rhs;
// 	int		pipe_fd[2];
// 	t_ctx	*aux;

// 	lhs = node->left;
// 	rhs = node->right;
// 	pipe(pipe_fd);
// 	*aux = *p_ctx;
// 	aux->fd_close = pipe_fd[STDIN];
// 	aux->fd[STDOUT] = pipe_fd[STDOUT];
// 	exec_word(lhs, aux);

// 	*aux = *p_ctx;
// 	aux->fd[STDIN] = pipe_fd[STDIN];
// 	aux->fd_close = pipe_fd[STDOUT];
// 	exec_word(rhs, aux);
// }

// void	exec_input(t_node *node, t_ctx *p_ctx)
// {
// 	t_node	*lhs;
// 	t_node	*rhs;

// 	lhs = node->left;
// 	rhs = node->right;

// 	p_ctx->fd[STDIN] = open(rhs->word.buf, O_RDONLY, 0644);
// 	exec_word(lhs, p_ctx);
// }

// void exec_heredoc(t_node *node, t_ctx *p_ctx)
// {
// 	t_node	*lhs;
// 	t_node	*rhs;

// 	lhs = node->left;
// 	rhs = node->right;

// 	p_ctx->fd[STDIN] = open(rhs->word.buf, O_RDONLY, 0644);
// 	exec_word(lhs, p_ctx);
// }

// void exec_output(t_node *node, t_ctx *p_ctx)
// {
// 	t_node	*lhs;
// 	t_node	*rhs;

// 	lhs = node->left;
// 	rhs = node->right;

// 	p_ctx->fd[STDOUT] = open(rhs->word.buf, O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 	exec_word(lhs, p_ctx);
// }

// void exec_append(t_node *node, t_ctx *p_ctx)
// {
// 	t_node	*lhs;
// 	t_node	*rhs;

// 	lhs = node->left;
// 	rhs = node->right;

// 	p_ctx->fd[STDOUT] = open(rhs->word.buf, O_CREAT | O_APPEND| O_WRONLY, 0644);
// 	exec_word(lhs, p_ctx);
// }

void	exec_word(t_node *node, t_context *p_ctx)
{
	char	**argv;

	argv = make_argv(node->word);
	if (ft_strchr(argv, '/') == NULL)
	{
		if (exec_builtin() == NULL) {
			search_and_fork_exec();
		}
	}
	else if (can_access(argv[0], p_ctx))
		fork_exec(argv, p_ctx);
	set_exit_status(p_ctx->exit_status);
	free_argv(argv);
}

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	if (argv == NULL)
		return ;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

void	set_exit_status(int exit_status)
{
	int	*p_exit_status;

	p_exit_status = get_exit_status();
	*p_exit_status = exit_status;
}

int	*get_exit_status(void)
{
	static int	exit_status;

	return (&exit_status);
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
	while (word_arr[i])
	{
		//ex. echo "123""456";
		list = split_quotes(word_arr[i]);
		glob_flag = check_glob(list);
		// heredoc delimeter에 (',"")가 있었다면 그 내용은 효력상실.
		// heredoc delimeter에 (',"")가 없었다면 그 내용은 expansion.
		// heredoc delimeter는 효력상실.
		// ex. echo '$USER', echo "$USER"
		// arg_expansion내부에서 cmd가 heredoc인지 판단해야함.
		arg_expansion(list);
		unquote(list);
		ft_lstadd_back(&argv_list, filename_expansion(list, glob_flag));
		ft_lstclear(&list, free);
		i++;
	}
	return (list_to_arr(argv_list));
}

// globbing character(*, ?)를 expansion해야 함.
t_list	*filename_expansion(t_list *chunks, t_bool glob_flag)
{
	t_list	*list;
	char	*pattern;

	pattern = concatenate(chunks);
	if(!pattern)
		// exit_status = ENOMEM로 set하고 에러리턴.
	if (glob_flag)
	{
		list = list_matches(pattern);
		if (list)
		{
			free(pattern);
			return (list);
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

#include <dirent.h>

t_list	*list_matches(char *pattern)
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

void	unquote(t_list *list)
{
	char	*content;

	while (list)
	{
		content = list->content;
		if (content[0] == '"')
		{
			content = ft_strtrim(content, "\"");
			free(list->content);
			list->content = content;
		}
		else if (content[0] == '\'')
		{
			content = ft_strtrim(content, "'");
			free(list->content);
			list->content = content;
		}
		list = list->next;
	}
}

void	arg_expansion(t_list *list)
{
	char	*content;

	while (list)
	{
		content = list->content;
		// parameter가 quotation(')안에 있으면 효력상실.
		if (content[0] != '\'')
		{
			content = parameter_expansion(list->content);
			free(list->content);
			list->content = content;
		}
		list = list->next;
	}
}

char	*parameter_expansion(char *str)
{
	char	*key;
	char	*value;
	char	*n_str;
	t_list	*list;
	t_list	*head;

	str = ft_strdup(str);
	n_str = str;
	head = search_key(str);
	list = head;
	while (list)
	{
		key = list->content;
		value = get_value(key);
		n_str = str_replace(str, key, value);
		free(str);
		str = n_str;
		list = list->next;
	}
	ft_lstclear(&head, free);
	return (n_str);
}

char	*str_replace(char *str, char *old, char *new)
{
	int		i;
	int		new_len;
	int		old_len;
	char	*res;

	old_len = ft_strlen(old);
	new_len = ft_strlen(new);
	res = malloc(ft_strlen(str) + \
			word_cnt(str, old) * (new_len - old_len) + 1);
	i = 0;
	while (*str)
	{
		if (ft_strnstr(str, old, ft_strlen(str)) == str)
		{
			ft_strlcpy(&res[i], new, new_len + 1);
			i += new_len;
			str += old_len;
		}
		else
			res[i++] = *str++;
	}
	res[i] = '\0';
	return (res);
}

int	word_cnt(char *str, char *word)
{
	int	i;
	int	cnt;
	int	len;

	i = 0;
	cnt = 0;
	len = ft_strlen(word);
	while (str[i])
	{
		if (ft_strnstr(&str[i], word, ft_strlen(&str[i])) == &str[i])
		{
			cnt++;
			i += len;
		}
		else
			i++;
	}
	return (cnt);
}

char	*get_value(char *key)
{
	// static char	status[4];
	char	*status;
	char		*value;

	if (key[1] == '?')
	{
		value = ft_itoa(*get_exit_status());
		ft_strlcpy(status, value, ft_strlen(value) + 1);
		free(value);
		return (status);
	}
	value = getenv(&key[1]);
	if (!value)
		value = ft_strdup("");
	return (value);
}

t_list	*search_key(char *str)
{
	int		base;
	int		i;
	t_list	*head;

	base = 0;
	i = 0;
	head = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			base = i++;
			if (str[i] == '?')
				ft_lstadd_back(&head, ft_lstnew(ft_strdup("$?")));
			else if (ft_isalpha(str[i]) || str[i] == '_')
			{
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
					i++;
				ft_lstadd_back(&head, ft_lstnew(ft_substr(str, base, i - base)));
			}
		}
		else
			i++;
	}
	return (head);
}


t_list	*split_quotes(char *str)
{
	int		i;
	int		base;
	char	*not_quote_str;
	t_list	*head;

	i = 0;
	head = NULL;
	while (str[i])
	{
		if (str[i] == '"')
			ft_lstadd_back(&head, include_slice(str, &i, '"'));
		else if (str[i] == '\'')
			ft_lstadd_back(&head, include_slice(str, &i, '\''));
		else
		{
			base = i;
			while (str[i] && str[i] != '\'' && str[i] != '"')
				i++;
			not_quote_str = ft_substr(&str[base], 0, i - base);
			ft_lstadd_back(&head, ft_lstnew(not_quote_str));
			i--;
		}
		i++;
	}
	return (head);
}

t_list	*include_slice(char *str, int *i, char end)
{
	int	base;

	base = (*i)++;
	while (str[*i] != end)
		(*i)++;
	return (ft_lstnew(ft_substr(&str[base], 0, *i - base + 1)));
}

t_bool	check_glob(t_list *list)
{
	return (list_search(list, '*') || list_search(list, '?'));
}

t_bool	list_search(t_list *list, char ch)
{
	char	*content;
	t_bool	pattern;

	pattern = FALSE;
	while (list)
	{
		content = list->content;
		// globbing character가 quotation(', "")안에 있으면 효력상실.
		if (ft_strchr(content, ch))
		{
			if (!ft_strchr(content, '"') && !ft_strchr(content, '\''))
				pattern = TRUE;
		}
		list = list->next;
	}
	return (pattern);
}

void	fork_exec(char **argv, t_context *p_ctx)
{
	int		pid;
	t_list	*envl;
	char	**envp;
	char	*cmd_path;

	envl = *get_envp();

	pid = fork();
	if (pid)
	{
		dup2(p_ctx->fd[STDIN], STDIN);
		dup2(p_ctx->fd[STDOUT], STDOUT);
		envp = list_to_arr(envl);
		if (p_ctx->fd_close >= 0) {
			close(p_ctx->fd_close);
			p_ctx->fd_close = -1;
		}
		execve(argv[0], argv, envp);
		exit(1);
	}
}

char	**list_to_arr(t_list *node)
{
	char	**arr;
	int		i;
	int		len;

	i = 0;
	len = ft_lstsize(node);
	arr = malloc(sizeof(t_list) * (len + 1));
	arr[len] = NULL;
	while (node)
	{
		arr[i++] = node->content;
		node = node->next;
	}
	return (arr);
}

# include <sys/stat.h>
# include <errno.h>

// S_IFMT	0170000	bitmask for the file type bitfields
// S_IFDIR	0040000	directory
static t_bool	can_access(char *filename, t_context *p_ctx)
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