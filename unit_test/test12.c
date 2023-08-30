#include <termios.h>
#include <unistd.h>
#include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

int main(void)
{
	// char c;
	struct termios term;
    char	*input;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;    // non-canonical input 설정
	term.c_lflag &= ~ECHO;      // 입력 시 터미널에 보이지 않게
	term.c_cc[VMIN] = 1;        // 최소 입력 버퍼 크기
	term.c_cc[VTIME] = 0;       //버퍼 비우는 시간 (timeout)
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
    
	input = readline("> ");
	printf("input: %s\n", input);
	// while (read(0, &c, sizeof(c)) > 0)
	// {
	// 	printf("input: %c\n", c);
	// }
}