#include <stdio.h>
#include <stdlib.h>

int wildcard(char *pattern, char *word);


int main(void)
{
	int ret = wildcard("*.txt*", "abc.txt");
	printf("ret: %d\n", ret);
	return (0);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int **allocate_dp(int row, int col)
{
	int **dp;
	dp = ft_calloc(row + 1, sizeof(int *));
	if (!dp)
		exit(ENOMEM);
	for (int i = 0; i <= row; i++)
	{
		dp[i] = ft_calloc(col + 1, sizeof(int));
	}
	return (dp);
}

int wildcard(char *pattern, char *word) {
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
