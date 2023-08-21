#include <stdio.h>
#include "../include/libft.h"

int main() {

	char *str;

	str = "'asd'\" ";
	printf("%s: %p %p\n", str, ft_strchr(str, '"'), ft_strchr(str, '\''));
	return 0;
}