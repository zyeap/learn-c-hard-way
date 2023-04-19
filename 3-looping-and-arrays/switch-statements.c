#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Error: You need 1 argument.\n");
		// Abort program by returning 1
		return 1;
	}

	int i = 0;
	for (i = 0; argv[1][i] != '\0'; i++) {
		char letter = argv[1][i];

		if (letter >= 65 && letter <= 90){
			letter += 32;
		}

		switch (letter) {
			case 'a':
				printf("%d: 'a'\n", i);
				break;
			case 'e':
				printf("%d: 'e'\n", i);
				break;
			case 'i':
				printf("%d: 'i'\n", i);
				break;
			case 'o':
				printf("%d: 'o'\n", i);
				break;
			case 'u':
				printf("%d: 'u'\n", i);
				break;
			case 'y':
				if (i > 2) {
					printf("%d: 'y'\n", i);
				}
				else {
					goto NOTVOWEL;
				}
				break;
		NOTVOWEL:
			default:
				printf("%d: %c is not a vowel\n", i, letter);
		}
	}

	return 0;
}
