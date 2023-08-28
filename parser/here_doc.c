#include	"../include/here_doc.h"

static t_bool	is_same_str(char *word1, char *word2);


int	nbr_length(int n)
{
	int	i = 0;

	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	terminal_init(void)
{
	struct termios attr;

	tcgetattr(STDIN, &attr);
	attr.c_lflag &= ~ICANON;		// non-canonical input 설정
	attr.c_lflag &= ~ECHO;			// 입력 시 터미널에서 보이지 않기
	attr.c_cc[VMIN] = 1;			// 최소 입력 버퍼 크기
	attr.c_cc[VTIME] = 0;			// 버퍼 비우는 시간(timeout)
	tcsetattr(STDIN, TCSANOW, &attr);
}

void	get_cursor_position(int *row, int *col)
{
	int		a = 0;
	int		i = 1;
	char	buf[255];
	int		ret;
	int		temp;

	terminal_init();
	write(0, "\033[6n", 4);  //report cursor location
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	while (buf[i])
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			if (a == 0)
				*row = ft_atoi(&buf[i]) - 1;
			else
			{
				temp = ft_atoi(&buf[i]);
				*col = temp - 1;
			}
			a++;
			i += nbr_length(temp) - 1;
		}
		i++;
	}
}

int	*get_cursor(void)
{
	static int cursor[2];

	return ((int *)cursor);
}

void	update_cursor_position()
{
	struct termios tmp_attr;
	int row;
	int col;

	tcgetattr(STDIN, &tmp_attr);
	get_cursor_position(&row, &col);
	get_cursor()[0] = row;
	get_cursor()[1] = col;
	tcsetattr(STDIN, TCSANOW, &tmp_attr);
}

int putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}
#include <term.h>

void move_cursor(int row, int col)
{
	tgetent(NULL, "xterm");
	char *cm = tgetstr("cm", NULL);
	tputs(tgoto(cm, col, row), 1, putchar_tc);
}

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
		// @ 현재커서위치(글로벌) 업데이트
		// @ SIGWINCH핸들러로 윈도우 사이즈 변경시마다,현재커서위치(글로벌) 업데이트
		update_cursor_position();
		// input = readline("> ");
		ft_putstr_fd("> ", STDOUT);
		input = get_next_line(STDIN);
		
		if (!input || is_same_str(input, delimiter))
		{
			if (input)
			{
				set_heredoc_eof_flag(FALSE);
				free(input);
			}
			else if (get_heredoc_data()->heredoc_fault_flag == TRUE)
			{
				// if (get_heredoc_data()->heredoc_eof_flag)
				// 	ft_putstr_fd("\033[1A", STDOUT);
				set_heredoc_eof_flag(TRUE);
				dup2(get_heredoc_data()->temp_stdin_fd, STDIN);
				close(get_heredoc_data()->temp_stdin_fd);
				delete_heredoc(tokenizer);
			}
			else
			{
				set_heredoc_eof_flag(TRUE);
				// ft_putstr_fd("\033[1A", STDOUT);
				// ft_putstr_fd("\033[2C", STDOUT);

				// @ 현재커서위치(글로벌)로 커서를 옮김
				// int row;
				// int col;
				// get_cursor_position(&row, &col);
				// printf("row: %d, col: %d ", row, col);
				// exit(1);
				// move_cursor(row, col);
				// ft_putstr_fd("> ", STDOUT);
				
				// for (int i = 1; i <= tokenizer->heredoc_file_idx; i++)
				// 	ft_putstr_fd("\033[2C", STDOUT);
			}
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
