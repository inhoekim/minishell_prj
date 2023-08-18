#include "../include/here_doc.h"

static t_bool	is_same_str(char *word1, char *word2);

void	set_delimiter(t_node *node, char buf[])
{
	char	*word;

	word = node->right->word[0];
	ft_strlcpy(buf, word, DELIMLEN);
	free(word);
}

char	*quote_removal(char *word)
{
	t_list	*list;
	char	*chunk;

	list = split_quotes(word);
	unquote(list);
	chunk = concatenate(list);
	ft_lstclear(&list, free);
	return (chunk);
}

int	*get_heredoc_exit_flag(void)
{
	static int	heredoc_exit_flag;
	return (&heredoc_exit_flag);
}

// @ heredoc 작성중 sigterm(ctrl+c)종료된 경우 flag를 1로 set
void set_heredoc_exit_flag(int flag)
{
	*get_heredoc_exit_flag() = flag;
}

void	here_doc(char *delimiter, t_tokenizer *tokenizer)
{
	char	*input;
	char	*expanded;
	int		fd;
	t_list	*list;
	t_bool	can_expansion;

	can_expansion = TRUE;
	// delimeter에 quotation이 포함된 경우, 파일내용은 expansion되지 않는다.
	if (ft_strchr(delimiter, '"') || ft_strchr(delimiter, '\''))
	{
		list = split_quotes(delimiter);
		unquote(list);
		delimiter = concatenate(list);
		can_expansion = FALSE;
	}
	fd = open(tokenizer->heredoc_file_name[tokenizer->heredoc_file_idx++], \
	O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (TRUE)
	{
		input = readline("> ");
		if (!input || is_same_str(input, delimiter))
		{
			if (input)
				free(input);
			break ;
		}
		// heredoc에서는 parameter가 '안에 있어도 expasion 가능하다.
		if (can_expansion)
		{
			expanded = parameter_expansion(input);
			ft_putendl_fd(expanded, fd);
			free(expanded);
		}
		else
			ft_putendl_fd(input, fd);
		free(input);
	}
	close(fd);
}

static t_bool	is_same_str(char *word1, char *word2)
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

