#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main() {
	FILE *file = fopen("./input.txt", "r");
	char c;
	int firstdigit = -1;
	int second_digit;
	int sum = 0;
	while ((c = fgetc(file)) != EOF) {
		if ('0' <= c && c <='9') {
			if (firstdigit == -1) {
				firstdigit = c - '0';
				second_digit = c - '0';
			} else {
				second_digit = c - '0';
			}
			continue;
		}

		if (c == '\n') {
			sum += 10*firstdigit + second_digit;
			firstdigit = -1;
			second_digit = 0;
		}
	}

	sum += 10*firstdigit + second_digit;

	fclose(file);
	printf("Die Summe ist: %d\n", sum);
	return 0;
}