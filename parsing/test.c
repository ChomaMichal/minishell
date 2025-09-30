#include <stdio.h>
#include <string.h>

void test_func(char *ptr2, char **ptr_to_ptr1)
{
	*ptr_to_ptr1 = strdup("changed\n");
	printf("ptr2 from test_func is %p -- %s\n", ptr2, ptr2);
}

int main()
{
	char *ptr1 = strdup("hello\n");
	char *ptr2 = ptr1;
	for (int i = 0; i < 3; i++)
	{
		printf("before ptr1: %p -- %s\n", ptr1, ptr1);
		printf("before ptr2: %p -- %s\n", ptr2, ptr2);
		if (i == 1)
			test_func(ptr2, &ptr1);
		printf("after ptr1: %p -- %s\n", ptr1, ptr1);
		printf("after ptr2: %p -- %s\n", ptr2, ptr2);		
	}
	return (0);
}