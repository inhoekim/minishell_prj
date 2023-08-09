// #include "../minishell.h"

#define PATH_MAX 4096
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char **argv, char **envp) 
{
  char path[PATH_MAX];
  (void)argc;
  (void)argv;

  getcwd(path, PATH_MAX);
//   printf("Current Directory: %s\n", path) ;
  int idx = 0;
  while (envp[idx])
  {
	printf("%s\n", envp[idx]);
	idx++;
  }
  return 0 ;
}