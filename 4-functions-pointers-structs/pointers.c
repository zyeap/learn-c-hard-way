#include <stdio.h>

int main(int argc, char *argv[]) {
	int ages[] = {23, 43, 12 ,89, 2};

	// think of string type as an array of pointers to chars
	// array of strings is an array of an array of pointers to chars
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
	printf("cur_age is a pointer to this location in memory: %p\n", (void*)&cur_age); 
	printf("cur_age + 1 is a pointer to this location in memory: %p\n", (void*)&cur_age + 1); 
	printf("cur_age holds this value: %d\n", *cur_age); 
	printf("cur_age + 1 holds this value: %d\n", *(cur_age + 1)); 

	// cur_age is a pointer to this location in memory: 0x7ffea1e2a000
	// cur_age + 1 is a pointer to this location in memory: 0x7ffea1e2a001
	// cur_age holds this value: 23
	// cur_age + 1 holds this value: 43
	
	// ** = pointer to pointer of char
	// **cur_name -> A
	// *cur_name -> Alan
	char **cur_name = names;
	printf("The first name is %s\n", *cur_name); // 23

	// reference by pointer
	for (i = 0; i < count; i++) {
		// print out each pointer value offset by i
		printf("%s is %d years old.\n", *(cur_name + i), *(cur_age + i));
	}

	printf("---\n");

	// pointers can be indexed
	for (i = 0; i < count; i++) {
		printf("%s is %d years old.\n", cur_name[i], cur_age[i]);
	}

	printf("---\n");

	// another complex way with pointers
	for (cur_name = names, cur_age = ages; (cur_age - ages) < count; cur_name++, cur_age++){
		printf("%s lived %d years so far.\n", *cur_name, *cur_age);
	}
}

