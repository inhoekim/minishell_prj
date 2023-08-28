#include	"../include/here_doc.h"

static t_bool	is_same_str(char *word1, char *word2);

void	here_doc(char *delimiter, t_tokenizer *tokenizer)
{
	char	*input;
	char	*expanded;
	int		fd;
	t_list	*list;
	t_bool	can_expansion;

	if (tokenizer->heredoc_file_idx == HEREDOC_MAX)
	{
		msh_error(NULL, "maximum here-document count exceeded", 1);
		delete_heredoc(tokenizer);
		set_heredoc_fault_flag(TRUE);
		return ;
	}
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
	set_cursor_size(tokenizer->heredoc_file_idx);
	while (TRUE)
	{
		input = readline("> ");
		if (!input || is_same_str(input, delimiter))
		{
			if (input)
				free(input);
			else if (get_heredoc_data()->heredoc_fault_flag == TRUE)
			{
				dup2(get_heredoc_data()->temp_stdin_fd, STDIN);
				close(get_heredoc_data()->temp_stdin_fd);
				delete_heredoc(tokenizer);
			}
			else
			{
				// if (tokenizer->heredoc_file_idx == 1)
				// {
				// 	ft_putstr_fd("\033[1A", STDOUT);
				// 	ft_putstr_fd("\033[2C", STDOUT);
				// }
				// else
				// {
				ft_putstr_fd("\033[1A", STDOUT);
				for (int i = 1; i <= tokenizer->heredoc_file_idx; i++)
				{
					ft_putstr_fd("\033[2C", STDOUT);
				}
				// }
			}
			if (is_same_str(input, delimiter))
				set_heredoc_visit_flag(FALSE);
			break ;
		}
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

void	delete_heredoc(t_tokenizer *tokenizer)
{
	int	i;

	i = 0;
	while (i < tokenizer->heredoc_file_idx)
		unlink(tokenizer->heredoc_file_name[i++]);
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
