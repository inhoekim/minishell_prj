#include "tokenizer.h"

// void	skip_whitespace(t_tokenizer *token)
// {
// 	while ((*token->current_token) == 32 || \
// 		((*token->current_token) >= 9 && (*token->current_token) <= 13))
// 		token->current_token++;
// }

char	*skip_whitespace(char *c)
{
	while (*c == 32 || (*c >= 9 && *c <= 13))
		c++;
	return (c);
}

t_bool	match(t_tokenizer *token, char matchword)
{
	if (*(token->current_token) != matchword)
		return (FALSE);
	token->current_token++;
	return (TRUE);
}

t_bool	string_close(t_tokenizer *token, char c)
{
	token->current_token++;
	while (*(token->current_token) != c && token->current_token)
		token->current_token++;
	if (*(token->current_token) != c || !token->current_token)
		return (FALSE);
	return (TRUE);
}

#include <stdio.h>
int main(void)
{
	char *line = "        (hello)    <<";
	t_tokenizer token1;
	t_tokenizer token2;
	
	line = skip_whitespace(line);

	token1 = get_next_token(line);
	printf("token_size %d\n", token1.token_size);
	printf("%u\n", token1.type);

	token2 = get_next_token(token1.current_token + token1.token_size);
	printf("token_size %d\n", token2.token_size);
	printf("%u\n", token2.type);
}
