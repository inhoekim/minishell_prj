/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhkim <inhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:44:24 by naylee            #+#    #+#             */
/*   Updated: 2023/08/18 12:32:02 by inhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


/*
	first_set() Details
	It checks which terminal character the first letter of the nonterminal function results in)
	set = {WORD, LESS, GREAT, DGREAT, DLESS, AND_IF, OR_IF, PIPE, SUBSHELL_LEFT, E0F}
*/
t_bool	check_first_set(t_nonterminal idx, t_symbol curr_token)
{
	static int	table[8][10] = {
	[PIPELINE] = {WORD, LESS, GREAT, DGREAT, DLESS,\
	 NONE, NONE, NONE, SUBSHELL_LEFT, NONE},
	[SIMPLE_CMD] = {WORD, LESS, GREAT, DGREAT, DLESS,\
	 NONE, NONE, NONE, NONE, NONE},
	[IO_REDIRECT] = {NONE, LESS, GREAT, DGREAT, DLESS,\
	 NONE, NONE, NONE, NONE, NONE},
	[CONDITIONAL] = {NONE, NONE, NONE, NONE, NONE,\
	 AND_IF, OR_IF, NONE, NONE, NONE},
	[PIPED_COMMAND] = {NONE, NONE, NONE, NONE, NONE,\
	 NONE, NONE, PIPE, NONE, NONE},
	[IO_REDIRECT_DG_AFTER_SIMPLE_CMD] = {WORD, NONE, NONE,\
	 NONE, NONE, NONE, NONE, NONE, NONE, NONE},
	[IO_FILE] = {NONE, LESS, GREAT, DGREAT, NONE, NONE, NONE, NONE, NONE, NONE},
	[IO_HERE] = {NONE, NONE, NONE, NONE, DLESS, NONE, NONE, NONE, NONE, NONE},
	};

	if (table[idx][curr_token] != NONE)
		return (TRUE);
	else
		return (FALSE);
}
