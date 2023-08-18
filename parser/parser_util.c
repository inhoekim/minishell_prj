/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:44:24 by naylee            #+#    #+#             */
/*   Updated: 2023/08/18 13:30:56 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// t_symbol의 개수는 12개지만, table의 일차원 배열의 길이는 9개임. (eof, '(', ')' 제외)
t_bool	check_first_set(t_nonterminal idx, t_symbol curr_token)
{
	static int	table[7][9] = {
	[PIPELINE] = {WORD, LESS, GREAT, DGREAT, DLESS, NONE, NONE, NONE, NONE}, // pipeline, command, simple_cmd
	[IO_REDIRECT] = {NONE, LESS, GREAT, DGREAT, DLESS, NONE, NONE, NONE, NONE}, // io_redirect, io_redirect_star, io_redirect_dagger, 
	[CONDITIONAL] = {NONE, NONE, NONE, NONE, NONE, AND_IF, OR_IF, NONE, NONE},
	[PIPED_COMMAND] = {NONE, NONE, NONE, NONE, NONE, NONE, NONE, PIPE, NONE}, // piped_command
	[IO_REDIRECT_DG_AFTER_SIMPLE_CMD] = {WORD, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE}, // io_redirect_dg_after_simple_cmd
	[IO_FILE] = {NONE, LESS, GREAT, DGREAT, NONE, NONE, NONE, NONE, NONE}, // io_file
	[IO_HERE] = {NONE, NONE, NONE, NONE, DLESS, NONE, NONE, NONE, NONE}, // io_here
	};
	// -1이면 firstset 실패, 0 이상이면 성공
	if (table[idx][curr_token] != NONE)
		return (TRUE);
	else
		return (FALSE);
}
