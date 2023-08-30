#include <stdio.h>
#include <unistd.h>
#include <termcap.h>
# include "../libft/libft.h"


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
				*rows = ft_atoi(&buf[i]) - 1;
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

int row;
int col;

int main(void)
{
	// ;1R
	// write(0, "\033[6n", 4);
	get_cursor_position(&col, &row);
	printf("row: %d, col: %d\n", row, col);
}

// #include <signal.h>
// #include <sys/ioctl.h>
// #include <stdio.h>

// // 윈도우 사이즈를 얻어온다.
// struct winsize get_winsize(int fd)
// {
//     int i;
//     struct winsize size;
//     if (ioctl(fd, TIOCGWINSZ, (char *)&size) < 0)
//     {
//         perror("size get error\n");
//     }
//     return size;
// }
// void sig_handler(int);

// struct winsize c_winsize;
// int main()
// {

//     // 표준입력이 장치에 연결되어 있는지 확인한다.
//     if (!isatty(0))
//         exit(0);

//     // 시그널 핸들러를 등록한다.
//     if(signal(SIGWINCH, sig_handler) == SIG_ERR)
//     {
//         perror("error : ");
//         exit(0);
//     }
//     c_winsize = get_winsize(0);
//     printf("%d %d %d %d\n", c_winsize.ws_row, c_winsize.ws_col,
//                             c_winsize.ws_xpixel, c_winsize.ws_ypixel);

//     // 창이 일정 사이즈이상이 되지 않을경우 종료시킨다.
//     if (c_winsize.ws_col < 80 || c_winsize.ws_row < 20)
//     {
//         printf("윈도우 사이즈는 80, 20이상이 되어야 합니다\n");
//         exit(0);
//     }
//     while(1)
//     {
//         sleep(10);
//     }
// }

// void sig_handler(int signo)
// {
//     printf("WINSIZE CHANGE\n");
//     c_winsize = get_winsize(0);
//     printf("%d %d %d %d\n", c_winsize.ws_row, c_winsize.ws_col,
//                             c_winsize.ws_xpixel, c_winsize.ws_ypixel);
// }