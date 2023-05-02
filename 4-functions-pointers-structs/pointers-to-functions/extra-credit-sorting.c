#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void die(const char *message) {
	if (errno) {
		perror(message);
	} else {
		printf("Error: %s\n", message);
	}

	exit(1);
}

// typedef creates a fake type (in this case function pointer)
// compare_cb returns int, so we use typedef int
typedef int (*compare_cb) (int a, int b);

// sorting_algo returns a pointer to an int, so we specify with typedef int *
typedef int *(*sorting_algo) (int *numbers, int count, compare_cb cmp);

int *bubble_sort(int *numbers, int count, compare_cb cmp) {
	int temp = 0;
	int i = 0;
	int j = 0;
	int *target = malloc(count * sizeof(int));

	if (!target)
		die("Memory error");

	// memcpy(destination, source, size of memory)
	memcpy(target, numbers, count * sizeof(int));

	for (i = 0; i < count; i++) {
		for (j = 0; j < count - 1; j++) {
			// callback to cmp function (which is just a pointer to compare_cb)
			// this allows caller to pass anything as long as it matches the signature of compare_cb
			if (cmp(target[j], target[j + 1]) > 0) {
				temp = target[j + 1];
				target[j + 1] = target[j];
				target[j] = temp;
			}
		}
	}

	return target;
}

// last argument (cmp) is of arbitrary type typedef
int *insertion_sort(int *numbers, int count, compare_cb cmp) {
	int temp = 0;
	int i = 1;
	int j = 0;
	int *target = malloc(count * sizeof(int));

	if (!target)
		die("Memory error");

	// memcpy(destination, source, size of memory)
	memcpy(target, numbers, count * sizeof(int));

	while (i < count) {
		j = i;
		while (j > 0 && cmp(target[j - 1], target[j]) > 0) {
			temp = target[j - 1];
			target[j - 1] = target[j];
			target[j] = temp;
			j--;
		}
		i++;
	}

	return target;
}

int sorted_order(int a, int b) {
	return a - b;
}

int reverse_order(int a, int b) {
	return b - a;
}

// test we are sorting correctly by doing sort and printing it out
void test_sorting(int *numbers, int count, sorting_algo alg, compare_cb cmp) {
	int i = 0;
	int *sorted = alg(numbers, count, cmp);

	if (!sorted)
		die("Failed to sort as requested");

	for (i = 0; i < count; i++){
		printf("%d ", sorted[i]);
	}

	printf("\n");

	free(sorted);
}

int main (int argc, char *argv[]) {
	if (argc < 2) die("USAGE: pointers-to-functions 9 1 5 8 3 2");

	int count = argc - 1;
	int i = 0;
	char **inputs = argv + 1;

	int *numbers = malloc(count * sizeof(int));
	if (!numbers) die("Memory error");

	for (i = 0; i < count; i++){
		numbers[i] = atoi(inputs[i]);
	}

	// pass each of the compare_cb functions to test_sorting
	printf("Insertion sort (ascending): ");
	test_sorting(numbers, count, insertion_sort, sorted_order);
	printf("Bubble sort (ascending): ");
	test_sorting(numbers, count, bubble_sort, sorted_order);
	printf("Insertion sort (descending): ");
	test_sorting(numbers, count, insertion_sort, reverse_order);
	printf("Bubble sort (descending): ");
	test_sorting(numbers, count, bubble_sort, reverse_order);

	free(numbers);

	return 0;
}
