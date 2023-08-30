#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/minishelllibft.h"
#include <dirent.h>
#include "../include/minishellminishell.h"

#define PATH_MAX 1024

t_list	*pathname_expansion(t_list *list, t_bool glob_flag);
char	*make_pattern(t_list *list);
t_list  *make_templist(char *dir, char *pattern);
t_bool	*wildcard(char *name, char *pattern);

t_list	*pathname_expansion(t_list *list, t_bool glob_flag)
{
	t_list		  	*temp_list;
	char			path[PATH_MAX];
	char			*dir;
	char			*pattern;

	pattern = make_pattern(list);
	dir = getcwd(path, PATH_MAX);
	if (glob_flag)
	{
		temp_list = make_templist(dir, pattern);
		free(pattern);
		return (temp_list);
	}
	return (ft_lstnew(pattern));
}

char	*make_pattern(t_list *list)
{
	char	*newstr;
	char	*aux;
	int		len;
	t_list	*temp;

	len = ft_lstsize(list);
	newstr = ft_calloc(sizeof(*newstr), len + 1);
	temp = list;
	while (list)
	{
		aux = list->content;
		ft_strlcat(newstr, aux, len + 1);
		list = list->next;
	}
	return (newstr);
}

t_list  *make_templist(char *dir, char *pattern)
{
	DIR				*dir_ptr;
	struct dirent	*file;
	t_list			**temp;

	temp = NULL;
	dir_ptr = opendir(dir);
	file = readdir(dir_ptr);
	while (file)
	{
		if (file && file->d_type == DT_REG && wildcard(file->d_name, pattern))
			ft_lstadd_back(temp, ft_lstnew(ft_strdup(file->d_name)));
		file = readdir(dir_ptr);
	}
	closedir(dir_ptr);
	return (*temp);
}

t_bool	wildcard(char *name, char *pattern)
{
	int len_n;
	int	len_p;
	int	idx;
	int	flag;

	len_n = ft_strlen(name);	
	len_p = ft_strlen(pattern);
	idx = 0;
	while (idx < len_n && idx < len_p && (pattern[idx] == "?" || pattern[idx] == name[idx]))
		idx++;
	if (len_p == idx)
		return (len_n == idx);
	if (pattern[idx] == "*")
	{
		flag = 0;
		while (flag + idx <= len_n)
		{
			if (wildcard(name + idx + 1, pattern + flag + idx))
				return (TRUE);
			flag++;
		}
	}
	return (FALSE);
}

int main(void)
{
    t_list  *test;
    t_list  *list = ft_lstnew("*.txt");

    test = pathname_expansion(list, 1);
    while (test)
    {
        printf("%s\n", test->content);
        test = test->next;
    }
    return 0;
}