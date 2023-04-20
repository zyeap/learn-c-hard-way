#include <stdio.h>

int main(int argc, char *argv[]) {
	int numbers[4] = { 0 };
	char name[4] = { 'a' };

	printf("Before setting array values\n");
	printf("numbers: %d %d %d %d\n",
			numbers[0],numbers[1],numbers[2],numbers[3]);
	printf("name each: %c %c %c %c\n",
			name[0], name[1], name[2], name[3]);

	printf("name: %s\n", name);

	numbers[0] = 1;
	numbers[1] = 2;
	numbers[2] = 3;
	numbers[3] = 4;

	name[0] = 'Z';
	name[1] = 'a';
	name[2] = 'k';
	// name[3] = '\0';

	printf("After setting array values\n");
	printf("numbers: %d %d %d %d\n",
			numbers[0],numbers[1],numbers[2],numbers[3]);
	printf("name each: %c %c %c %c\n",
			name[0], name[1], name[2], name[3]);

	printf("name: %s\n", name);

	// another way to declare and initialize a string
	// * is indirection operator
	// get the data from where the pointer "another" is pointing to
	// https://stackoverflow.com/questions/27644383/understanding-two-ways-of-declaring-a-c-string
	// https://stackoverflow.com/questions/15168771/pointer-to-a-string-in-c
	char *another = "Jack";
	printf("another name: %s\n", another);
	printf("another each: %c %c %c %c\n",
			another[0], another[1], another[2], another[3]);
}
