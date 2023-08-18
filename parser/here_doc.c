#include "../include/here_doc.h"

static t_bool	is_same_str(char *word1, char *word2);

void	set_delimiter(t_node *node, char buf[])
{
	char	*word;

	word = node->right->word[0];
	word = quote_removal(word);
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
	static int heredoc_exit_flag;
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

	fd = open(tokenizer->heredoc_file_name[tokenizer->heredoc_file_idx++], \
	O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// @ excute전에 모든 fd close해야 함 
	while (TRUE)
	{
		input = readline("> ");
		// @ delimeter에 quotation이 포함된 경우, 파일내용은 expansion되지 않음
		// if(strch(,"'" or '"'))
		//   unquote();
		//   can_expansion = FALSE;
		if (!input || is_same_str(input, delimiter))
		{
			if (input)
				free(input);
			break ;
		}
		// heredoc에서는 parameter가 '`안에 있어도 expasion가능
		// if (can_expansion)
		expanded = parameter_expansion(input);
		ft_putendl_fd(expanded, fd);
		// else
		// ft_putendl_fd(input, fd);
		free(expanded);
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

