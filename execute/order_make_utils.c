#include "../include/minishell.h"
#include "../include/execute.h"
#include "../include/exec_node_util.h"
#include "../include/exec_word_util.h"
#include "../include/make_argv_util.h"
#include "../include/execute_util.h"

static char		*abc_1(int start, int end, char *str);
static int		find_cs_1(char c, char charset);
static int		size_count_1(char *str, char c);
static char		**ft_free2_1(char **newstr, int idx);

char	**ft_split2(char const *s, char c)
{
	char	**newstr;
	int		idx;
	int		num;
	int		start;

	idx = 0;
	newstr = (char **)malloc(sizeof(char *) * (size_count_1((char *)s, c) + 1));
	if (!newstr)
		return (NULL);
	num = 0;
	while (s[num] && idx < (size_count_1((char *)s, c)))
	{
		while (s[num] && find_cs_1(s[num], c))
			num++;
		if (s[num] != 0)
			start = num;
		while (s[num] && (!(find_cs_1(s[num], c))))
			num++;
		newstr[idx] = abc_1(start, num, (char *)s);
		if (!newstr[idx])
			return (ft_free2_1(newstr, idx));
		idx++;
	}
	newstr[idx] = 0;
	return (newstr);
}

static char	**ft_free2_1(char **newstr, int idx)
{
	while (idx--)
	{
		free(newstr[idx]);
	}
	free(newstr);
	return (NULL);
}

static int	size_count_1(char *str, char c)
{
	int	num;
	int	count;

	num = 0;
	count = 0;
	while (str[num])
	{
		while (str[num] && (find_cs_1(str[num], c)))
			num++;
		if (str[num] != 0)
			count++;
		while (str[num] && (!find_cs_1(str[num], c)))
			num++;
	}
	return (count);
}

static char	*abc_1(int start, int end, char *str)
{
	int		size;
	int		idx;
	char	*arr;

	size = end - start;
	idx = 0;
	arr = (char *)malloc(sizeof(char) * (size + 2));
	if (arr == NULL)
		return (NULL);
	while (start < end)
	{
		arr[idx] = str[start];
		start++;
		idx++;
	}
	arr[idx++] = '/';
	arr[idx] = 0;
	return (arr);
}

static int	find_cs_1(char c, char charset)
{

	if (c == charset)
		return (1);	
	return (0);
}