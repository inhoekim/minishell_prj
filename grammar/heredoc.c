/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:12:25 by seykim            #+#    #+#             */
/*   Updated: 2023/08/30 19:12:26 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/grammar.h"

static void		read_heredoc(int fd, char *delimiter, \
t_tokenizer *tokenizer, t_bool can_expansion);
static t_bool	check_eof_heredoc(char *input, \
char *delimiter, t_tokenizer *tokenizer);

void	heredoc(char *delimiter, t_tokenizer *tokenizer)
{
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
	if (ft_strchr(delimiter, '"') || ft_strchr(delimiter, '\''))
	{
		list = split_quotes(delimiter);
		unquote(list);
		delimiter = concatenate(list);
		can_expansion = FALSE;
	}
	fd = open(tokenizer->heredoc_file_name[tokenizer->heredoc_file_idx++], \
	O_WRONLY | O_CREAT | O_TRUNC, 0644);
	read_heredoc(fd, delimiter, tokenizer, can_expansion);
	close(fd);
}

static void	read_heredoc(int fd, char *delimiter, \
t_tokenizer *tokenizer, t_bool can_expansion)
{
	char	*input;
	char	*expanded;

	while (TRUE)
	{
		input = readline("> ");
		if (check_eof_heredoc(input, delimiter, tokenizer))
			break ;
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
}

static t_bool	check_eof_heredoc(char *input, \
char *delimiter, t_tokenizer *tokenizer)
{
	if (!input || is_same_str(input, delimiter))
	{
		if (input)
		{
			set_heredoc_eof_flag(FALSE);
			free(input);
		}
		else if (get_heredoc_data()->heredoc_fault_flag == TRUE)
		{
			if (get_heredoc_data()->heredoc_eof_flag)
				ft_putstr_fd("\033[1A", STDOUT);
			set_heredoc_eof_flag(TRUE);
			dup2(get_heredoc_data()->temp_stdin_fd, STDIN);
			close(get_heredoc_data()->temp_stdin_fd);
			delete_heredoc(tokenizer);
		}
		else
			set_heredoc_eof_flag(TRUE);
		return (TRUE);
	}
	return (FALSE);
}
