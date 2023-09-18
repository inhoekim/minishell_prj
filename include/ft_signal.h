/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:29:07 by seykim            #+#    #+#             */
/*   Updated: 2023/09/18 13:29:08 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H

# define STDIN 0
# define STDOUT 1

# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include "../libft/libft.h"
# include "minishell.h"

//signal_default
void	sigact_default_mode(void);

//signal_fork
void	sigact_fork_mode(void);
void	sigact_modeoff(void);

//signal_heredoc
void	sigact_heredoc_mode(void);

//signal_util
t_bool	*get_is_subshell(void);
void	set_is_subshell(t_bool flag);

#endif
