#include <stdio.h>

int main()
{
	int age = 10;
	double height = 9072.543456;
	// why does running ./ex3 print 9072.542969 and not 9072.543456?
	// A: float has 7 digits of precision, double has 15

	printf("I am %d years old.\n", age);
	printf("I am %f inches tall.\n", height);
	printf("I am %e inches tall.\n", height);
	printf("I am %g inches tall.\n", height);

	// different formats:
	// %f - fixed point >  9072.543456
	// %e - force exponent > 9.072543e+03 
	// %g - best fit > 9072.54 

	return 0;
}
