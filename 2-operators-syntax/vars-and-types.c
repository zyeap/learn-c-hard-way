#include <stdio.h>

int main(int argc, char*argv[])
{
	int distance = 100;
	float power = 2.345f;
	double super_power = 56789.4532;
	char initial = 'C';
	char first_name[] = "Zach";
	char last_name[] = "Yeap";

	printf("You are %d miles away.\n", distance);
	printf("You have %f levels of power.\n", power);
	printf("You have %f awesome super powers.\n", super_power);
	printf("I have an initial %c.\n", initial);
	printf("My first name is %s.\n", first_name);
	printf("My last name is %s.\n", last_name);
	printf("My whole name is %s %c. %s.\n", first_name, initial, last_name);

	int bugs = 100;
	double bug_rate = 1.2;

	printf("You have %d bugs at the imaginary rate of %f.\n", bugs, bug_rate);

	// difference between long and unsigned long is lower to upper bound
	// long: -2,147,483,648 to 2,147,483,647
	// unsigned long: 0 to 4,294,967,295
	unsigned long universe_of_defects = 1L * 1024L * 1024L * 1024L * 9999999L * 234L;
	printf("The entire universe has %ld bugs.\n", universe_of_defects);

	double expected_bugs = bugs * bug_rate;
	printf("You are expected to have %f bugs.\n", expected_bugs);

	double part_of_universe = expected_bugs / universe_of_defects;
	printf("This is only a %e portion of the universe.\n", part_of_universe);

	char nul_byte = '\0';
	printf("This is a null byte %c.\n", nul_byte);

	// char is a numeric type (same as int but smaller)
	// numeric representation of symbol (ASCII code)
	// hence, why it can be multiplied by integer
	int care_percentage = bugs * nul_byte;
	printf("Which means you should care %d%%.\n", care_percentage);

	return 0;
		
}
