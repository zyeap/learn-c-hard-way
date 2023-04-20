#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
	char *name;
	int age;
	int height;
	int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight) {
	// get the size in bytes of the Person struct and allocate it to the who pointer
	// who is a pointer of type (struct Person) that holds the starting memory address
	struct Person *who = malloc(sizeof(struct Person));
	assert(who != NULL);

	// initialize each field 
	who->name = strdup(name); // strdup duplicates the string for the name (ensures the structure owns it), aka copying original string into newly created memory
	who->age = age;
	who->height = height;
	who->weight = weight;

	return who;
}

void Person_destroy(struct Person *who) {
	assert(who != NULL);
	// if free is not done, program may run into memory leak
	// free(who->name);
	free(who);
}

void Person_print(struct Person *who) {
	// who -> name is equivalent to (*who).name
	// get the member name from struct that "who" points to
	printf("name: %s\n", who->name);
	printf("\tage: %d\n", who->age);
	printf("\theight: %d\n", who->height);
	printf("\tweight: %d\n", who->weight);
}

int main(int argc, char *argv[]) {
	struct Person *joe = Person_create("Joe Alex", 32, 64, 140);
	struct Person *frank = Person_create("Frank Blank", 20, 72, 180);

	printf("Joe is at memory location %p: \n", joe);
	Person_print(joe);
	printf("Frank is at memory location %p: \n", frank);
	Person_print(frank);

	(*joe).age += 20;
	joe->height -= 2;
	joe->weight += 40;
	Person_print(joe);

	frank->age += 10;
	frank->weight += 20;
	Person_print(frank);

	Person_destroy(joe);
	Person_destroy(frank);
}
