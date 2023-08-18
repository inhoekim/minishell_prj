// #include <stdio.h>

// typedef struct s_ctx
// {
// 	int fd[2];
// } t_ctx;

// int main(void)
// {
// 	int arr1[2] = {1,2};
// 	int arr2[2];
// 	// int arr2[2] = {3,4};

// 	arr2 = arr1;
// 	printf("%d %d\n", arr1[0], arr1[1]);
// 	printf("%d %d\n", arr2[0], arr2[1]);

// 	/*******************/
// 	t_ctx a;
// 	t_ctx b;
// 	a.fd[0] = 1; a.fd[1] = 2;
// 	// b = a;
// 	printf("%p %p\n", &a.fd[0], &b.fd[0]);

// 	printf("%d %d\n", a.fd[0], a.fd[1]);
// 	printf("%d %d\n", b.fd[0], b.fd[1]);
//     return (0);
// }

#include <stdio.h>
#include <string.h>
typedef struct student {
   int roll_num;
   char name[128];
}
student_t;
void print_struct(student_t *s) {
   printf("Roll num: %d, name: %s\n", s->roll_num, s->name);
}
int main() {
   student_t s1, s2;
   s1.roll_num = 1;
   strcpy(s1.name, "tom");
   s2.name[0] = 'T';
   s2.name[1] = 'O';
   s2.name[2] = 'M';
   s2 = s1;
   // Contents of s1 are not affected as deep copy is performed on an array
   
   print_struct(&s1);
   print_struct(&s2);
   return 0;
}