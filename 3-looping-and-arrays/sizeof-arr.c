#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int areas[] = {10, 20, 30, 14, 20};
	char name[] = "Bob";

	char full_name[] = {
		'B', 'o', 'b',
		' ', 'A', 'p', 'p', 'l', 'e', '\0'
	};

	// on most 32/64 bit systems, int is 4 bytes
	printf("The size of an int: %ld\n", sizeof(int)); 

	// areas will be 20 bytes, since 5 * 4 = 20
	printf("The size of areas (int[]): %ld\n", sizeof(areas));

	printf("The number of ints in areas: %ld\n", sizeof(areas) / sizeof(int));
	printf("The first area is %d, the second area is %d\n", areas[0], areas[1]);
	// if we print areas[10] (out of bounds index), program will still compile and run
	// however, areas[10] will probably result in some garbage value (aka undefined behavior)

	areas[0] = 100;
	printf("The new first area is %d\n", areas[0]);

	// char is 1 byte
	printf("The size of a char is: %ld\n", sizeof(char));
	printf("The size of a name (char[]) is: %ld\n", sizeof(name));
	printf("The number of chars: %ld\n", sizeof(name) / sizeof(char));

	printf("The size of full name (char[]) is: %ld\n", sizeof(full_name));
	printf("The number of chars in full name is %ld\n", sizeof(full_name) / sizeof(char));

	// string data is read only when executed (value needs to be known at compile time)
	// changing string literals is also undefined behavior
	// https://stackoverflow.com/questions/1011455/is-it-possible-to-modify-a-string-of-char-in-c

	// this works since name is an array of chars, not a string literal (literal = notation for representing fixed value in source code)
	// also, keep in mind " " vs ' '
	// 'a' is a single a character literal
	// "a" is a string literal containing 'a'and a null terminator (2 char array)
	name[0] = 'Z';

	printf("name=\"%s\" and full_name=\"%s\"\n", name, full_name);

	areas[2] = name[1];
	printf("New 3rd element in areas: %c\n", areas[2]);

	int i = 0;

	for (i=0; i<5; i++){
		printf("Area at index %d: %d\n", i, areas[i]);
	}

	// Good readings on UB
	// https://www.nayuki.io/page/undefined-behavior-in-c-and-cplusplus-programs
	// https://stackoverflow.com/questions/51557895/why-does-undefined-behaviour-exist
	// http://blog.llvm.org/2011/05/what-every-c-programmer-should-know.html
}
