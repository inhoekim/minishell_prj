#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int ft_slen(char *str);
static void ft_puts(char *str);

void __leak() {
	system("leaks rl_clear_history");
}
int main()
{
	char *str;
	
	atexit(__leak);
	while(1) {
		str = readline("prompt:");
		if(str)
			printf("%s\n", str);
		else
			break;
		add_history(str);
		if(strcmp(str,"clr") == 0) {
			ft_puts("end\n");
			free(str);
			// rl_clear_history();
			break;
		}
		free(str);
	}
	return (0);
}

static int ft_slen(char *str)
{
	int len;

	len = 0;
	while(str[len]) {
		len++;
	}
	return (len);
}

static void ft_puts(char *str)
{
	
	write(1, str, ft_slen(str));
}