#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
	void *ret = malloc(-1);
	printf("res: %p[%d]\n", ret, errno);
	
    return (0);
}