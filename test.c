#include "test.h"
#include <stdio.h>
#include "libft.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init_tokenizer();
	init_paser();
	minishell_loop();
	free_parser();
	free_tree();
	set_exit_status();

}

void	init_tokenizer()
{
	t_tokenizer		self;

	self.
}

void	init_parser()
{

}

t_bool  execute(t_node *ret)
{
		
	return FASLE;
}

t_tokenizer	*get_token()
{
	t_tokenizer *temp_token;


	return (temp_token);
}


void	minishell_loop() 
{
	t_node *ret;
	char	*line;
	t_bool check_exit;
	t_tokenizer *token;

	check_exit = TRUE;
	line = ft_strdup("");
	while (line)
	{
		line = readline("dasong >");
		// 히스토리 기록 -> readline의 함수
		if (line)
			add_history();
		// get_token을 통해 토큰 생성
		token = get_token();
		// parse를 통해 트리생성
		ret = parse(token);
		// 생성된 트리를 재귀를 통해서 execve함수 호출 && type bool로 exit의 입력여부 판단
		check_exit = execute(ret);
		// exit입력 시 종료, 아니면 while문을 통해 입력 대기상태 돌입
		if (check_exit)
			line = NULL;	
	}
}
