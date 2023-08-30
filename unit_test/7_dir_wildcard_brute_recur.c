#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/minishelllibft.h"
#include <dirent.h>
#include "../include/minishellminishell.h"

#define PATH_MAX 1024

t_list	*pathname_expansion(t_list *list, t_bool glob_sliding);
char	*make_pattern(t_list *list);
t_list  *make_templist(char *dir, char *pattern);
t_bool	wildcard(char *name, char *pattern);
static int	fft_strlen(const char *s);
int wildcard2(char *pattern, char *word);


int **allocate_dp(int row, int col) {
	int **dp;
	dp = ft_calloc(row + 1, sizeof(int *));
	for (int i = 0; i <= row; i++)
	{
		dp[i] = ft_calloc(col + 1, sizeof(int));
	}
	return (dp);
}

t_list	*pathname_expansion(t_list *list, t_bool glob_sliding)
{
	t_list		  	*temp_list;
	char			path[PATH_MAX];
	char			*dir;
	char			*pattern;

	pattern = make_pattern(list);
	dir = getcwd(path, PATH_MAX);
	if (glob_sliding)
	{
		temp_list = make_templist(dir, pattern);
		free(pattern);
		return (temp_list);
	}
	return (ft_lstnew(pattern));
}

char	*make_pattern(t_list *list)
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
	pattern = ft_calloc(str_size + 1, sizeof(*pattern));
	list = head;
	while (list)
	{
		content = list->content;
		ft_strlcat(pattern, content, str_size + 1);
		list = list->next;
	}
	return (pattern);
}

t_list  *make_templist(char *dir, char *pattern)
{
	DIR				*dir_ptr;
	struct dirent	*file;
	t_list			*temp;

	temp = NULL;

	dir_ptr = opendir(dir);
	file = readdir(dir_ptr);
	while (file)
	{
		file = readdir(dir_ptr);
		if (file && file->d_type == DT_REG && wildcard2(pattern, file->d_name))
			ft_lstadd_back(&temp, ft_lstnew(ft_strdup(file->d_name)));
	}
	closedir(dir_ptr);
	return (temp);
}

static int	fft_strlen(const char *s)
{
	int	i;

	i = 0;
	if(s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}


t_bool	wildcard(char *name, char *pattern)
{
	int len_n;
	int	len_p;
	int	idx;
	int	sliding;

	len_n = fft_strlen(name);	
	len_p = fft_strlen(pattern);
	idx = 0;
	while (idx < len_n && idx < len_p && (pattern[idx] == '?' || pattern[idx] == name[idx]))
		idx++;
	if (len_p == idx)
		return (len_n == idx);
	if (pattern[idx] == '*')
	{
		sliding = 0;
		while (sliding + idx <= len_n)
		{
			if (wildcard(pattern + idx + 1,  name + sliding + idx))
				return (TRUE);
			sliding++;
		}
	}
	return (FALSE);
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
	(void)envp;
    t_list  *test;
    t_list  *list = ft_lstnew("*.a");
	char *str;
    test = pathname_expansion(list, 1);
    while (test)
    {
		str = test->content;
        printf("%s\n", str);
        test = test->next;
    }
    return 0;
}

int wildcard2(char *pattern, char *word) 
{
	int	len_p;
	int	len_w;
	int	**dp;
	int	p_idx;
	int	w_idx;

	len_p = ft_strlen(pattern);
	len_w = ft_strlen(word);
	dp = allocate_dp(len_p, len_w);
	dp[0][0] = 1;
	if (pattern[0] == '*')
		dp[1][0] = 1;
	p_idx = 0;
	while (++p_idx <= len_p)
	{
		w_idx = 0;
		while (++w_idx <= len_w)
		{
			if (pattern[p_idx - 1] == '?' || (pattern[p_idx - 1] == word[w_idx - 1]))
				dp[p_idx][w_idx] = dp[p_idx - 1][w_idx - 1];
			else if (pattern[p_idx - 1] == '*')
				dp[p_idx][w_idx] = (dp[p_idx - 1][w_idx] || dp[p_idx][w_idx - 1]);
		}
		if (dp[1][1] == 0)
			return (FALSE);
	}
	return (dp[len_p][len_w]);
}
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #define FALSE 0
// char	*ppp(char *pattern);
// int **allocate_dp(int row, int col) 
// {
// 	int **dp;
// 	dp = ft_calloc(row + 1, sizeof(int *));
// 	for (int i = 0; i <= row; i++)
// 	{
// 		dp[i] = ft_calloc(col + 1, sizeof(int));
// 	}
// 	return (dp);
// }

// int wildcard2(char *pattern, char *word) 
// {
// 	int	len_p;
// 	int	len_w;
// 	int	**dp;
// 	int	p_idx;
// 	int	w_idx;

// 	pattern = ppp(pattern);
// 	len_p = strlen(pattern);
// 	len_w = strlen(word);
// 	dp = allocate_dp(len_p, len_w);
// 	dp[0][0] = 1;
// 	p_idx = 0;
// 	if (pattern[0] =='*')
// 		dp[1][0] = 1;
// 	p_idx = 0;
// 	while (++p_idx <= len_p)
// 	{
// 		w_idx = 0;
// 		while (++w_idx <= len_w)
// 		{
// 			if (pattern[p_idx - 1] == word[w_idx - 1])
// 				dp[p_idx][w_idx] = dp[p_idx - 1][w_idx - 1];
// 			else if (pattern[p_idx - 1] == '*')
// 				dp[p_idx][w_idx] = (dp[p_idx - 1][w_idx] || dp[p_idx][w_idx - 1]);
// 		}
// 		// if (dp[1][1] == 0)
// 		// 	return (FALSE);
// 	}
// 	return (dp[len_p][len_w]);
// }

// char	*ppp(char *pattern)
// {
// 	char	*new_pattern;
// 	int		new_len;
// 	int		idx;
// 	int		flag;
// 	int		new_idx;

// 	new_len = 0;
// 	idx = 0;
// 	flag = 0;
// 	while (pattern[idx])
// 	{
// 		while (pattern[idx] == '*')
// 		{
// 			if (flag == 0)
// 			{
// 				flag = 1;
// 				new_len++;
// 			}
// 			idx++;
// 		}
// 		flag = 0;
// 		new_len++;
// 		idx++;
// 	}
// 	idx = -1;
// 	new_pattern = ft_calloc(new_len + 1, sizeof(char *));
// 	new_idx = 0;
// 	flag = 0;
// 	while (pattern[++idx] && new_idx <= new_len)
// 	{
// 		if (pattern[idx] == '*' && flag == 0)
// 		{
// 			flag = 1;
// 			new_pattern[new_idx] = '*';
// 			new_idx++;
// 		}
// 		while (pattern[idx] == '*' && flag == 1)
// 			idx++;
// 		if (pattern[idx] != '*')
// 			flag = 0;
// 		new_pattern[new_idx] = pattern[idx];
// 		new_idx++;
// 	}
// 	new_pattern[new_idx] = 0;
// 	// free(pattern);
// 	return (new_pattern);
// }

// int main()
// {
// 	char pattern[200];
// 	char word[200];
// 	int num;

// 	scanf("%s", pattern);
// 	scanf("%d", &num);
// 	for (int i = 0; i < num; i++)
// 	{
// 		scanf("%s", word);
// 		if (wildcard2(pattern, word))
// 			printf("%s\n", word);
// 	}
// }