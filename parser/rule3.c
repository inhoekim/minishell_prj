/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rule3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhkim <inhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 07:46:19 by inhkim            #+#    #+#             */
/*   Updated: 2023/08/14 07:46:20 by inhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/tokenizer.h"
#include "../include/rule.h"
#include "../include/parser.h"
#include "../include/filename_expansion.h"
#include "../include/here_doc.h"

//io_redirect_dg_after_simple_cmd ::= WORD io_redirect_star
//io_redirect_dg_after_simple_cmd ::= empty
t_node	*io_redirect_dg_after_simple_cmd(t_tokenizer *tokenizer)
	{
	t_node	*parent;
	t_node	*child;

	if (match_token(WORD, tokenizer, FALSE))
	{
		child = make_leaf(tokenizer);
		parent = io_redirect_star(tokenizer);
		return (merge_tree(parent, child));
	}
	return (NULL);
}

//io_redirect_star ::= io_redirect io_redirect_star
//io_redirect_star ::= empty
t_node	*io_redirect_star(t_tokenizer *tokenizer)
{
	t_node	*parent;
	t_node	*child;
	t_token	tk;

	tk = *(tokenizer->curr_token);
	if (check_first_set(IO_REDIRECT, tk.type))
	{
		parent = io_redirect(tokenizer);
		child = io_redirect_star(tokenizer);
		return (merge_tree(parent, child));
	}
	return (NULL);
}

//io_redirect ::= io_file
//io_redirect ::= io_here
t_node	*io_redirect(t_tokenizer *tokenizer)
{
	t_token	tk;

	tk = *(tokenizer->curr_token);
	if (check_first_set(IO_FILE, tk.type))
		return (io_file(tokenizer));
	else if (check_first_set(IO_HERE, tk.type))
		return (io_here(tokenizer));
	syntax_error(tokenizer);
	return (NULL);
}

//io_file ::= LESS WORD
//io_file ::= GREAT WORD
//io_file ::= DGREAT WORD
t_node	*io_file(t_tokenizer *tokenizer)
{
	if (match_token(LESS, tokenizer, TRUE) \
	&& get_curr_token(tokenizer)->type == WORD)
		return (make_tree(LESS, NULL, make_leaf(tokenizer)));
	else if (match_token(GREAT, tokenizer, TRUE) \
	&& get_curr_token(tokenizer)->type == WORD)
		return (make_tree(GREAT, NULL, make_leaf(tokenizer)));
	else if (match_token(DGREAT, tokenizer, TRUE) \
	&& get_curr_token(tokenizer)->type == WORD)
		return (make_tree(DGREAT, NULL, make_leaf(tokenizer)));
	syntax_error(tokenizer);
	return (NULL);
}

void	delete_heredoc(t_tokenizer *tokenizer);

int	*get_tmp_stdin_fd(void)
{
	static int	tmp_stdin_fd;

	return (&tmp_stdin_fd);
}

void	set_tmp_stdin_fd(int fd)
{
	*get_tmp_stdin_fd() = fd;
}

void	quit_heredoc(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("\n");
	/*
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	*/
	set_heredoc_exit_flag(1);
	set_tmp_stdin_fd(dup(STDIN));
	// @ 껏다켜는 순간, readline buffer의 입력커서포인터에 대한 stdout buffer의
	// @ 상대위치는 아래라인으로 고정됨?
	close(STDIN);
	set_heredoc_exit_flag(1);
}

void	sigact_heredoc_mode(void)
{
	struct sigaction	intsig;
	struct sigaction	quitsig;

	// rl_catch_signals = 1;
	intsig.sa_handler = quit_heredoc;
  	sigemptyset(&intsig.sa_mask);
	intsig.sa_flags = SA_RESTART;
	sigaction(SIGINT, &intsig, 0);
	quitsig.sa_handler = SIG_IGN;
	// quitsig.sa_handler = SIG_DFL;
	sigemptyset(&quitsig.sa_mask);
	quitsig.sa_flags = 0;
	sigaction(SIGQUIT, &quitsig, 0);
}

//io_here ::= DLESS WORD
t_node	*io_here(t_tokenizer *tokenizer)
{
	t_node	*node;
	char	delim[DELIMLEN];

	if (match_token(DLESS, tokenizer, TRUE) \
	&& get_curr_token(tokenizer)->type == WORD)
	{
		if (*get_heredoc_exit_flag() == 1)
			return (NULL);
		node = make_tree(DLESS, NULL, make_leaf(tokenizer));
		if (tokenizer->heredoc_file_idx == HEREDOC_MAX)
		{
			msh_error(NULL, "maximum here-document count exceeded", 1);
			delete_heredoc(tokenizer);
			set_heredoc_exit_flag(1);
			return (NULL);
		}
		set_delimiter(node, delim);
		// @ sigaction set(heredoc mode)
		// @(구현o) sigint(2) 컨트롤+ c -> 개행 하고 default mode전환
		// @(구현o) sigquit(3) 컨트롤+ \ -> 무시
		// @(구현o) eof 컨트롤+ d -> 개행 없이 종료. heredoc파일은 생성.
		sigact_heredoc_mode();
		here_doc(delim, tokenizer);
		sigact_default_mode();
		if (*get_heredoc_exit_flag() == 1)
			return (NULL);
		return (node);
	}
	syntax_error(tokenizer);
	return (NULL);
}

void	delete_heredoc(t_tokenizer *tokenizer)
{
	int	i;

	i = 0;
	while (i < tokenizer->heredoc_file_idx)
		unlink(tokenizer->heredoc_file_name[i++]);
}
