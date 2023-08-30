#ifndef SIGNAL_H
# define SIGNAL_H

# define STDIN 0
# define STDOUT 1

# include <stdio.h>
# include <signal.h>
# include <termios.h>

typedef enum e_bool
{
	FALSE,
	TRUE,
} t_bool;

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
