# Setup for C development


## Installation and running files
```
Install:
sudo apt install build-essential

Check compiler installed
cc --version

Run compiler to build c file
make <file>
```

## Using Makefiles to build
- make works by declaring dependencies, then describing how to build them
```
make ex1

1. Does ex1 exist?
2. No - is there another file that starts with ex1?
3. Yes - ex1.c
4. Run cc ex1.c -o ex1 to build this c file
5. Make one ex1 by using cc to build it from ex1.c

Alternative syntax:
CFLAGS="-Wall" make ex1

1. Create environment variable CFLAGS="-Wall"
	- Command line option to add "-Wall" to cc command that make runs
```

- Instead of running make, we can create a Makefile
	- Only enter TAB characters, improper indentation can break Makefile
- `make` will automatically run the makefile in current directory
- Can run other commands, like `make clean`

