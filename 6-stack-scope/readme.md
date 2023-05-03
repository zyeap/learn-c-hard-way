# Variable scope and storage

## Variable storage keywords
- `extern`
	- tells compiler that variable exists, but it's in an external location
	- one C file will be using another variable defined in another C file
- `static` (file) 
	- opposite of extern, variable only used in this file and should not be available to other parts of the program
- `static` (function)
	- if a variable within a function is static, that variable is only accessible from that function.
