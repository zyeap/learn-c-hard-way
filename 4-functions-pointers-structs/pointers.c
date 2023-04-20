#include <stdio.h>

int main(int argc, char *argv[]) {
	int ages[] = {23, 43, 12 ,89, 2};

	// think of string type as an array of pointers to chars
	// array of strings is an array of an array of pointers to chars
	// char *name is an address that points to a char/char array
	// char *name[] is an array of addresses that point to char/char arrays
	char *names[] = {"Alan", "Frank", "Mary", "John", "Lisa"};

	int count = sizeof(ages) / sizeof(int);
	int i = 0;

	// referencing data values by indexing
	for (i = 0; i < count; i++) {
		printf("%s is %d yrs old.\n", names[i], ages[i]);
	}

	printf("---\n");

	// set up pointers to start of arrays
	// create pointer (cur_age) that points to an integer type
	int *cur_age = ages;
	printf("The first age is %d\n", *cur_age); // 23
	printf("cur_age is a pointer to this location in memory: %p\n", cur_age); 
	printf("cur_age + 1 is a pointer to this location in memory: %p\n", cur_age + 1); 
	printf("cur_age holds this value: %d\n", *cur_age); 
	printf("cur_age + 1 holds this value: %d\n", *(cur_age + 1)); 

	// The first age is 23
	// cur_age is a pointer to this location in memory: 0x16eeaee90
	// cur_age + 1 is a pointer to this location in memory: 0x16eeaee94
	// cur_age holds this value: 23
	// cur_age + 1 holds this value: 43
	// The first name is Alan

	
	// ** = pointer to pointer of char
	// **cur_name -> A
	// *cur_name -> Alan
	char **cur_name = names;
	printf("The first name is %s\n", *cur_name); // 23

	printf("---\n");

	// reference by pointer
	int j = 0;
	while (j < count) {
		// print out each pointer value offset by j
		printf("%s has %d bananas.\n", *(cur_name + j), *(cur_age + j));
		printf("%s is at %p location in memory.\n", *(cur_name + j), cur_name + j);
		printf("%d is at %p location in memory.\n", *(cur_age + j), cur_age + j);
		j++;
	}

	printf("---\n");

	// pointers can be indexed
	// reverse loop from end to beginning
	for (i = count - 1; i >= 0; i--) {
		printf("%s is %d years old.\n", cur_name[i], cur_age[i]);
	}

	printf("---\n");

	// another complex way with pointers
	// difference between cur_age and ages (starting point) will be the index of value
	for (cur_name = names, cur_age = ages; (cur_age - ages) < count; cur_name++, cur_age++){
		printf("%s lived %d years so far.\n", *cur_name, *cur_age);
	}

	printf("---\n");

	// process command line args using pointers
	char **cur_arg = argv;
	for (i = 0; i < argc; i++) {
		printf("Argument at position %d: %s\n", i, *(cur_arg + i));
	}
}

