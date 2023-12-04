#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define WINNING_NUMBERS 10

int get_points(char* line);
bool contains(int* array, int length, int value);

int main() {
	FILE *file = fopen("../input.txt", "r");
	if (file == NULL) {
		return -1;
	}
	char line[500];
	int sum = 0;

	while (fgets(line, 500, file)) {
		sum+= get_points(line);
	}

	fclose(file);
	printf("Die Summe der Punkte ist: %d\n", sum);
	return 0;
}

int power(int base, int exponent) {
	int result = 1;
	for(int i = 0; i < exponent; i++) {
		result *= base;
	}

	return result;
}

int parse_int_as_long_as_possible(char **line) {
	int digits[3] = {0};
	int digit = 0;

	while (**line && '0' <= **line && **line <= '9') {
		digits[digit] = **line - '0';
		digit++;
		(*line)++;
	}

	int num = 0;
	for (int i = digit - 1; i >= 0; i--) {
		num += power(10, digit - 1 - i) * digits[i];
	}
	return num;
}

bool contains(int* array, int length, int value) {
	for (int i = 0; i < length; i++) {
		if (array[i] == value) return true;
	}

	return false;
}

int get_points(char* line) {
	//ignore Card n: at beginning
	line += 8;

	int winning_numbers[WINNING_NUMBERS] = {0};
	int i = 0;
	while (*line && *line != '|') {
		int num = parse_int_as_long_as_possible(&line);

		if (num != 0) {
			winning_numbers[i] = num;
			i++;
		}

		line++;
	}

	int counter = 0;

	while (*line) {
		int num = parse_int_as_long_as_possible(&line);

		if (num != 0 & contains(winning_numbers, WINNING_NUMBERS, num)) {
			counter++;
		}

		line++;
	}

	return counter == 0 ? 0 : power(2, counter - 1);

}