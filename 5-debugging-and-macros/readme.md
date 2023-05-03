# Debugging in C

## Error handling
- In C, the global `errno` value can be checked for a error code
- Pattern for error handling
	1. Call function
	2. Check if return value is an error
	3. Clean up all resources used so far
	4. Print out an error message
- To simplify error handling, we can take these functions and place it in a header file

```
#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n",\
        __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprintf(stderr,\
        "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__,\
        clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr,\
        "[WARN] (%s:%d: errno: %s) " M "\n",\
        __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n",\
        __FILE__, __LINE__, ##__VA_ARGS__)

#define check(A, M, ...) if(!(A)) {\
    log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__);\
    errno=0; goto error; }

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__);\
    errno=0; goto error; }

#endif
```
- To compile with custom macro, use `-D` flag
	- `gcc -Wall -g -DNDEBUG test-dbg.c -o test-dbg`
- `##__VA_ARGS__` means substitute extra specified arguments here
- `...` means take additional arguments specified in function call, and use them for `##__VA_ARGS__`
	```
	Example usage with log_err

	#define log_err(M, ...) fprintf(stderr,\
		"[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__,\
		clean_errno(), ##__VA_ARGS__)

	log_err("Age: %d, name: %s", age, name)

	expands to: 
	fprintf(stderr, "[ERROR] (%s:%d: errno: %s) Age %d: name %d\n",
	__FILE__, __LINE__, clean_errno(), age, name);
	```
- The CPP (C preprocessor) replaces macros with expanded version of their definition recursively (effectively expanding all of the macros in macros)
- CPP = recursive templating system
	- Power comes from ability to generate whole blocks of parameterized code
- Other advantages:
	- able to print out file and line no.
	- clearer error checking statements
	- conditionally compile portions of code (ex: adding flags to show debug or not)
- More on standard predefined macros (__FILE__, __LINE__, etc.)
	- https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html
