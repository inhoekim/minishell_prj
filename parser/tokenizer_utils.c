#include "tokenizer.h"

void	reset_tokenizer(t_tokenizer *tokenizer)
{
	if (tokenizer->type == SUBSHELL)
		tokenizer->end++;
	if (tokenizer->start != tokenizer->end)
		tokenizer->end++;
	skip_whitespace(tokenizer);
	if (*tokenizer->end == '\0')
	{
		//종료
	}
	tokenizer->start = tokenizer->end;
}

void	skip_whitespace(t_tokenizer *tokenizer)
{
	while ((*tokenizer->end) == 32 || \
		((*tokenizer->end) >= 9 && (*tokenizer->end) <= 13))
		tokenizer->end++;
	tokenizer->start = tokenizer->end;
}

t_bool	match(t_tokenizer *tokenizer, char matchword)
{
	tokenizer->end++;
	if (tokenizer->end && *(tokenizer->end) == matchword)
		return (TRUE);
	return (FALSE);
}

t_bool	string_close(t_tokenizer *tokenizer, char c)
{
	tokenizer->end++;
	while (*tokenizer->end != '\0' && *tokenizer->end != c)
		tokenizer->end++;
	if (*tokenizer->end == '\0' || *tokenizer->end != c)
		return (FALSE);
	return (TRUE);
}

#include <stdio.h>
int main(void)
{
	char *line = "'hihihihi''hello";
	t_tokenizer token1;
	//t_tokenizer token2;

	token1.start = line;
	token1.end = line;
	token1.type = E0F;

	token1 = get_next_token(&token1);
	printf("start ptr: %s\nended ptr: %s\n", token1.start, token1.end);
	printf("%u\n", token1.type);

	token1 = get_next_token(&token1);
	printf("start ptr: %s\nended ptr: %s\n", token1.start, token1.end);
	printf("%u\n", token1.type);

	// token1 = get_next_token(&token1);
	// printf("start ptr: %s\nended ptr: %s\n", token1.start, token1.end);
	// printf("%u\n", token1.type);

	// token2 = get_next_token(token1.current_token + token1.token_size);
	// printf("token_size %d\n", token2.token_size);
	// printf("%u\n", token2.type);
}
