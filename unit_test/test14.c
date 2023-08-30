#include <unistd.h>
#include <termcap.h>

int putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

int main(void)
{
	tgetent(NULL, "xterm");
	char *cm = tgetstr("cm", NULL);
	tputs(tgoto(cm, 7, 0), 1, putchar_tc);
}