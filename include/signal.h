#ifndef SIGNAL_H
# define SIGNAL_H

# include "util.h"
# include "grammar.h"

void	sigact_default_mode(void);
void	sigact_fork_mode(void);
void	sigact_modeoff(void);
void	sigact_heredoc_mode(void);
t_bool	*get_is_subshell(void);
void	set_is_subshell(t_bool flag);

#endif