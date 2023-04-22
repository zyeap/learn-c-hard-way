#include <stdio.h>

struct Person {
	char *name;
	int age;
	int height;
	int weight;
};

struct Person Person_create(char *name, int age, int height, int weight) {
	struct Person who;

	// since we are not creating a pointer, we can use . syntax to directly assign values
	who.name = name;
	who.age = age;
	who.height = height;
	who.weight = weight;

	return who;
}

void Person_print(struct Person who) {
	printf("Name: %s\n", who.name);
	printf("\tAge: %d\n", who.age);
	printf("\tHeight: %d\n", who.height);
	printf("\tWeight: %d\n", who.weight);
}

int main(int argc, char *argv[]) {
	// creating structs, not a struct pointer
	struct Person joe = Person_create("Joe Alex", 32, 64, 140);
	struct Person frank = Person_create("Frank Blank", 20, 72, 180);

	// passing a copy of structs created to Person_print() function
	// struct copied into function stack (pass by copy is often expensive/unnecessary)
	// using a pointer allows pass by reference (any changes affect original object, but also more efficient)
	// https://stackoverflow.com/questions/65588231/using-a-struct-vs-a-pointer-to-a-struct
	Person_print(joe);
	Person_print(frank);

	printf("---\n");

	joe.age += 5;
	joe.height += 10;
	joe.weight -= 25;

	frank.age += 10;
	frank.height += 8;
	frank.weight += 20;

	Person_print(joe);
	Person_print(frank);
}
