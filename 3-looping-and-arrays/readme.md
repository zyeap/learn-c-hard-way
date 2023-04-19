# Arrays, strings, and looping

## Arrays
- syntax is `<type> <name>[size] = { elements }`
- size is optional
- ex: `int numbers[] = {1, 2, 3, 4}`
- 0 based indexing for arrays

- Another way to declare and initialize a string is through "*" (indirection operator)
- ex: `char *another_string = "ABC"`
	- get data from another_string pointer

- Strings are just an array of bytes terminated with the '\0' (nul) byte
- Possible to change letter in string, since it is just an element in an array
	- `first_letter[0] = 'Z'`
- An array of strings is a 2D array (outer array or words, inner array of letters for each word)
	```
	// combining char *str = "blah" with char str[] = {'b', 'l', 'a', 'h'} syntax
	/* 
	  0 1 2 3 4 5 6 7 8 9
	0 C a l i f o r n i a
	1 T e x a s 
	2 O r e g o n
	*/
	```

- `sizeof()` is a useful function  for determining byte size
- `sizeof(type)` will indicate the size of a certain data type, like int or char, on your system
	- to use sizeof() in printf(), %ld or %u may be needed

## Looping
- while/for loops most common
	- don't forget increment/decrement counter in while loop, or else could be infinite
- syntax
	```
	while (condition) { do something ... }

	for (initial value; test condition; incrementer) { do something ... }
	```
