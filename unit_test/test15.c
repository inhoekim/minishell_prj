#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termcap.h>

# define BACKSPACE 127
# define LEFT_ARROW 4479771
# define RIGHT_ARROW 4414235

int	nbr_length(int n)
{
	int	i = 0;

	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	get_cursor_position(int *col, int *rows)
{
	int		a = 0;
	int		i = 1;
	char	buf[255];
	int		ret;
	int		temp;

	write(0, "\033[6n", 4);  //report cursor location
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	while (buf[i])
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			if (a == 0)
				*rows = atoi(&buf[i]) - 1;
			else
			{
				temp = atoi(&buf[i]);
				*col = temp - 1;
			}
			a++;
			i += nbr_length(temp) - 1;
		}
		i++;
	}
}

int		putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

void	move_cursor_left(int *col, int *row, char *cm)
{
	if (*col == 0)
		return ;
	--(*col);
	tputs(tgoto(cm, *col, *row), 1, putchar_tc);

}

void	move_cursor_right(int *col, int *row, char *cm)
{
	++(*col);
	tputs(tgoto(cm, *col, *row), 1, putchar_tc);

}

void	delete_end(int *col, int *row, char *cm, char *ce)
{
	if (*col != 0)
		--(*col);
	tputs(tgoto(cm, *col, *row), 1, putchar_tc);
	tputs(ce, 1, putchar_tc);
}

int		main(void)
{
	/* change term settings */
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	/* init termcap */
	tgetent(NULL, "xterm");
	char *cm = tgetstr("cm", NULL); //cursor motion
	char *ce = tgetstr("ce", NULL); //clear line from cursor
	
	int c = 0;
	int row;
	int col;
	
	while (read(0, &c, sizeof(c)) > 0)
	{
		get_cursor_position(&col, &row);
		if (c == LEFT_ARROW)
			move_cursor_left(&col, &row, cm);
		else if (c == RIGHT_ARROW)
			move_cursor_right(&col, &row, cm);
		else if (c == BACKSPACE)
			delete_end(&col, &row, cm, ce);
		else
		{
			col++;
			write(0, &c, 1);
		}
		c = 0; //flush buffer
	}
}