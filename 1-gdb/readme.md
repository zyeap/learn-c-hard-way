# Using a debugger
- debugger allows pausing/continuing execution
	- break points
	- see changes in variables
	- step through line by line
- GDB (GNU Debugger)
- Compile using `-g` flag to allow for debugging
	- preserves identifiers and symbols
	- `cc -Wall -g program.c`

## Resources used for learning
- https://github.com/cbourke/ComputerScienceI/tree/master/hacks/hack-debugging
- https://www.youtube.com/watch?v=bWH-nL7v5F4

## Starting GDB
- `gdb a.out`
- Optionally start with arguments passed to program
	- `gdb --args a.out arg1 arg2`
- Using the example buggy-primes file, we can run this command to compile
	- `gcc -g -std=c99 -w buggy-primes.c -lm`
- Start using `gdb a.out`

### Within GDB
- `layout next`  or `layout src` to see code
- `run` to run code
- `n` / `next` to go through line by line
- `print <var>`
	- `print var@10` prints variable of size 10
		- may just print out a bunch of memory addresses
	- `print *var@10`  to dereference and print values

- `s` / `step` to go into function
- `quit` to exit

- `break <function name>` to set breakpoint
	- `clear <func name>` to delete breakpoint
- `refresh` if TUI display looks weird
- `watch <variable>` to update anytime it changes
- `set args <val>` to set cla in gdb

- `backtrace full` / `bt` tells us what functions have been called and prints out everything
	- `thread apply all bt`: dump bt for all threads

