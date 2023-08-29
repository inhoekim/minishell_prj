#include <stdio.h>
#include "../include/minishelllibft.h"

int main() {

	char *str;
	
	str = "<< <<ads<<asdqw << '<<";
	int i = 0;
	int cnt = 0;
	printf("%p %p\n", &str[0], &str[1]);
	while(str[i]) {
		printf("match_token: %p\n", ft_strnstr(&str[i], "<<", 2));
		if(ft_strnstr(&str[i], "<<", 2)) {
			cnt++;
		}
		i++;
	}
	printf("<< cnt: %d\n", cnt);
	return 0;
}