#ifndef MS_SIGNAL_H
# define MS_SIGNAL_H

void	sigact_default_mode(void);
void	sigact_heredoc_mode(void);
void	sigact_fork_mode(void);
void	sigact_modeoff(void);
t_bool	*get_is_subshell(void);
void	set_is_subshell(t_bool flag);

// void	zobmie_handler(int signum);
// void	sigact_zobmie_setmode(void);

#endif