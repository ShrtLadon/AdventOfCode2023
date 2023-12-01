#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int numdigits = 9;
char* digits[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight" , "nine"};

int getnum(char* line);

int main() {
	FILE *file = fopen("./input.txt", "r");
	char line[100];
	int sum = 0;

	while (fgets(line, 100, file)) sum += getnum(line);

	fclose(file);
	printf("Die Summe ist: %d\n", sum);
	return 0;
}

int getnum(char* line) {
	int firstdigit = -1;
	int seconddigit;

	while(*line) {
		for (int i = 1; i <= numdigits; i++) {
			if (line == strstr(line, digits[i - 1])) {
				firstdigit = firstdigit != -1 ? firstdigit : i;
				seconddigit = i;
			}
		}

		if ('0' <= *line && *line <= '9') {
			firstdigit = firstdigit != -1 ? firstdigit : *line - '0';
			seconddigit = *line - '0';
		}

		line++;
	}

	return firstdigit * 10 + seconddigit;
}