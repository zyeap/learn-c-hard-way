#ifndef _stack_h
#define _ex22_h

// make THE_SIZE available to other .c files
extern int THE_SIZE;

//get and set internal static variables in stack.c
int get_age();
void set_age(int age);

//update static variable inside update_ratio
double update_ratio(double);

void print_size();

#endif
