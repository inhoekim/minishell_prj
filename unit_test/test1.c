#include "../minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
    (void)argv;
    (void)envp;
	
	t_symbol val;
	val= DLESS;
	printf("%d\n", val);
	
}
