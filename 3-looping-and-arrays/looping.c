#include <stdio.h>

int main(int argc, char *argv[])
{
	// while loop
	int i = 0;
	while (i < 5) {
		printf("%d\n", i);
		i++;
	}

	// array of strings
	// 2D array 
	// combining char *str = "blah" with char str[] = {'b', 'l', 'a', 'h'} syntax
	/* 
	  0 1 2 3 4 5 6 7 8 9
	0 C a l i f o r n i a
	1 T e x a s 
	2 O r e g o n
	*/
	char *states[] = {
		"California", "Texas", "Oregon",
		"Washington", NULL, argv[1]
	};

	argv[1] = states[0];

	// for loop
	int j = 1;
	for (j = 1; j < argc; j++) {
		printf("arg %d: %s\n", j, argv[j]);
	}

	int num_states = 6;

	for (i = 0; i < num_states; i++) {
		printf("state %d: %s\n", i, states[i]);
	}

	return 0;
}
