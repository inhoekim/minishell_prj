char	**make_argv(char **word_arr);
void	fork_exec(char **argv, t_context *p_ctx);
char	**list_to_arr(t_list *node);
void	free_argv(char **argv);
void	set_exit_status(int exit_status);
int	*get_exit_status(void);
