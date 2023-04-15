#include <stdio.h>

int main(int argc, char*argv[]){
	// no real Boolean type in C
	// 0 is false, anything else is true
	int i = 0;

	// argc (argument count) is an int with # of arguments supplied (first arg is calling the file)
	// argv (argument vector) is an array of null terminated strings containing the argument values
	printf("%d arguments given.\n", argc);
	if (argc == 1) {
		printf("Only file name given.\n");
	} else if (argc > 1 && argc < 4) {
		printf("Here's the argument values:\n");
		for (i = 0; i < argc; i++) {
			printf("%s ", argv[i]);
		}
		printf("\n");
	} else if (argc >= 4 && argc < 8){
		printf("You gave a lot of arguments.\n");
		for (i = 0; i < argc; i++) {
			printf("%s ", argv[i]);
		}
		printf("\n");
	} else {
		printf("Too many arguments.\n");
	}
	return 0;
}
