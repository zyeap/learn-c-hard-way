#include <stdio.h>
#include <ctype.h>
#include <string.h>

// forward declarations
int can_print_it(char ch);
void print_letters(char arg[], unsigned long slength);

// void function returns nothing
void print_arguments(int argc, char *argv[]) {
	int i = 0;

	for (i = 0; i < argc; i++) {
		printf("Length of string %s : %lu\n", argv[i], strlen(argv[i]));
		print_letters(argv[i], strlen(argv[i]));
	}
}

void print_letters(char arg[], unsigned long slength) {
	int i = 0;
	for (i = 0; i < slength; i++) {
		char ch = arg[i];
		if (isdigit(ch) || isalpha(ch) || isblank(ch)) {
			// print character and ASCII value
			printf("'%c' == %d ", ch, ch);
		} 
	}

	printf("\n");
}

// int can_print_it(char ch) {
// 	return isalpha(ch) || isblank(ch);
// }

int main(int argc, char *argv[]) {
	print_arguments(argc, argv);
	return 0;
}
