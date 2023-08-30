#include <stdio.h>
#include <stdlib.h>

int wildcard(char *pattern, char *word);

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int **allocate_dp(int row, int col) {
	int **dp;
	dp = ft_calloc(row + 1, sizeof(int *));
	for (int i = 0; i <= row; i++)
	{
		dp[i] = ft_calloc(col + 1, sizeof(int));
	}
	return (dp);
}

// 1. pattern의 현재 캐릭터가 '?'이거나 word의 현재 캐릭터가 일치하면 넘어간다.
// 2. pattern을 다읽었는데 word를 덜 읽었으면 false
// 3. word를 다읽었는데 pattern을 덜 읽었으면 false
// 4. pattern의 현재 캐릭터가 '*'이면
//    return (wildcard(그 이후의 pattern, 현재부터의 word) || wildcard(현재부터의 pattern, 그 이후의 word))

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
			// 캐릭터가 일치하거나 '?'이면
			if (pattern[pattern_idx - 1] == '?' || \
					pattern[pattern_idx - 1] == word[word_idx - 1])
			{
				dp[pattern_idx][word_idx] = dp[pattern_idx - 1][word_idx - 1];
			}
			// 4. pattern의 현재 캐릭터가 '*'이면
			else if (pattern[pattern_idx - 1] == '*') {
				dp[pattern_idx][word_idx] = \
				dp[pattern_idx - 1][word_idx] || dp[pattern_idx][word_idx - 1];
//				이전부분패턴에 대한, word의 현재부분의 match결과 || 현재까지의 부분패턴에 대한, word의 이전 부분의 match결과
//				-> 현재까지의 부분패턴과 word
			}
		}
	}
	return (dp[len_p][len_w]);
}

int main()
{
	char pattern[200];
	char word[200];
	int num;

	scanf("%s", pattern);
	scanf("%d", &num);
	for (int i = 0; i < num; i++)
	{
		scanf("%s", word);
		if (wildcard(pattern, word))
			printf("%s\n", word);
	}
}

// *.*
// 4
// main.c
// a.out
// readme
// yacc