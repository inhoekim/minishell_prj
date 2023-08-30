#include "../include/grammar.h"

// static char	*quote_removal(char *word);

void	delete_heredoc(t_tokenizer *tokenizer)
{
	int	i;

	i = 0;
	while (i < tokenizer->heredoc_file_idx)
		unlink(tokenizer->heredoc_file_name[i++]);
}

void	set_delimiter(t_node *node, char buf[])
{
	char	*word;

	word = node->right->word[0];
	ft_strlcpy(buf, word, DELIMLEN);
	free(node->right->word);
	free(word);
	free(node->right);
	node->right = NULL;
}

// static char	*quote_removal(char *word)
// {
// 	t_list	*list;
// 	char	*chunk;

// 	list = split_quotes(word);
// 	unquote(list);
// 	chunk = concatenate(list);
// 	ft_lstclear(&list, free);
// 	return (chunk);
// }

t_bool	is_same_str(char *word1, char *word2)
{
	int	word1_len;
	int	word2_len;

	word1_len = ft_strlen(word1);
	word2_len = ft_strlen(word2);
	if (ft_strncmp(word1, word2, word1_len) == 0 && \
		word2_len == word1_len)
		return (TRUE);
	return (FALSE);
}
