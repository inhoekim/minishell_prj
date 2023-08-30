#include <stdio.h>
#include <unistd.h>
#include <termcap.h>
#include <termios.h>

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

void	terminal_init(struct termios *term)
{
	tcgetattr(STDIN_FILENO, term);
	term->c_lflag &= ~ICANON;		// non-canonical input 설정
	term->c_lflag &= ~ECHO;			// 입력 시 터미널에서 보이지 않기
	term->c_cc[VMIN] = 1;			// 최소 입력 버퍼 크기
	term->c_cc[VTIME] = 0;			// 버퍼 비우는 시간(timeout)
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}

void	get_cursor_position(int *row, int *col)
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
				*row = ft_atoi(&buf[i]) - 1;
			else
			{
				temp = ft_atoi(&buf[i]);
				*col = temp - 1;
			}
			a++;
			i += nbr_length(temp) - 1;
		}
		i++;
	}
}


int main(void)
{
	struct termios term;
	int row;
	int col;

	terminal_init(&term);
	get_cursor_position(&row, &col);
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