# Functions, pointers, and structs
- for help with functions run `man 3 <function name>`
- `man 3` is for C library functions

## Functions
```
Syntax:

<return type> function_name(<argument(s)>) {
	do something ...
}

can initialize a function through forward declaration, then implement it later

ex: void print_letters(char arg, unsigned long slength);

```

## Pointers
- Take for example the following array of ints:
```
int ages[] = {23, 43, 12 ,89, 2};
```
- To access an element, we can use indexing: `ages[i]` (where i is the index of element)
	- `ages[0]` is 23
	- In plain English: "I want the integer in ages at address i"
- `ages` is a location in computer memory where all these integers start
	- The C compiler will replace `ages` with the address of the very first integer in `ages`

- How does C create the `ages` array and index it?
	1. Create block of memory in computer
	2. Point the name `ages` at the beginning of the block
	3. Index into the block by taking the base address of ages, then get the element thats i away from there
	4. Convert the address at `ages + i` to a valid int of the right size

- Pointers are variables that point to data's location in memory
	- `int *cur_age = ages;`
		- Create a pointer of int type called `cur_age` that refers to `ages` location in memory
		- `ages` is the memory address of the starting integer
	- `*(cur_age + i)`
		- get the starting point of `ages` in memory + i
		- dereference that location in memory and get the value stored

- A pointer is an address pointing somewhere in computer's memory with a type specifier so you get the right size of data with it.
	```
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
	```

- Purpose + usage
	- Lets you manually index data into blocks or memory when an array isn't sufficient.
		- Most cases, array is fine
		- When you have to work with raw block of memory, pointer comes in to allow raw, direct access
	- Common pointer use cases
		1. Ask OS for chunk of memory and use a pointer to work with it (structs)
		2. Pass large blocks of memory to functions with a pointer (instead of passing the entire block)
		3. Take the address of a function for dynamic callback
		4. Scan complex chunks of memory, converting bytes off a network socket into data structures or parsing files
	- In the early days of C, people used pointers to speed up programs, since compilers were bad at optimizing array usage
	- Compiler today is good, where syntax to access array vs pointer is translated and optimized same way
		- However! Pointers are not arrays
		- `sizeof(cur_age)` gets the size of the pointer, not what it points at
	- Use arrays whenever you can, only use pointers when absolutely necessary as a performance optimization

- Pointer lexicon
```
type *ptr		>> 	A pointer of type named ptr
*ptr			>>	The value of whatever ptr is pointed at	
*(ptr + i)		>> 	The value of (whatever ptr is pointed at + i)
&thing			>> 	the address of thing
type *ptr = &thing	>>	pointer of type named ptr set to address of thing
ptr++			>>	increment where ptr points
```

## Structs
- A structure (struct) is a collection of data types that are stored in one block of memory
	- we can access each variable within the struct independently by name
``` 
Syntax

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

```

## Heap vs Stack memory allocation
- Stack stores temporary variables in computer's RAM
	- By default in C, variables are on the stack
	- Argument for a function is pushed onto the stack, used inside the function, then popped off the stack
	- C compiler prevents memory leaks on stack by cleaning up usage automatically
	- Freeing a block from stack is simply adjusting pointer (since the most recently reserved block is next to be freed)
	- LIFO structure

- Heap also stores variables in RAM, but is set aside for dynamic allocation
	- No enforced allocation/deallocation
	- slower access when compared to stack
	- Use `malloc()` to allocate memory on the heap, and `free` is neede to deallocate memory

- Potential issues with memory allocation
	1. If you get a block of memory from malloc and have the pointer on the stack, when the function exits the pointer is lost
	2. Too much data on the stack (large structs, arrays) can cause a stack overflow error
	3. Passing/returning a pointer to something on the stack to another function will result in segfault, since the actual data will get popped off.

## Pointers to functions
- Useful for function callbacks or simulating classes/objects
- Syntax for function pointer
	```
	int (*some_pointer) (int a, int b)
	<return type> (*pointer_name) (arguments...)

	Same syntax even if we return a pointer from the function
	ex: int *(*some_pointer) (int a, int b)
	```
- `typedef` can be used together with function pointers to declare more complex types
	- after declaring with typedef, we can use the function pointer's name as if it is an existing type
