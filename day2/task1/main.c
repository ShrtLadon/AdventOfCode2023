#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define color_num 3

char* color[color_num] = {"red", "green", "blue"};
int in_bag[color_num] = {12, 13, 14};

int get_if_valid(char* line);

int main() {
	FILE *file = fopen("./input.txt", "r");
	if (file == NULL) {
		return -1;
	}
	char line[500];
	int sum = 0;

	while (fgets(line, 500, file)) {
		sum+= get_if_valid(line);
	}

	fclose(file);
	printf("Die Summe valider ids ist: %d\n", sum);
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

void reset_bag(int* bag) {
	for(int i = 0; i < color_num; i++) {
		bag[i] = in_bag[i];
	}
}

int get_if_valid(char* line) {
	//ignore Game at beginning
	line += 5;
	int id = parse_int_as_long_as_possible(&line);

	int in_bag_currently[color_num];
	reset_bag(in_bag_currently);

	int lastnum = 0;
	while(*line) {
		if (*line == ';') {
			reset_bag(in_bag_currently);
			line++;
			continue;
		}

		for (int i = 0; i < color_num; i++) {

			if (strstr(line, color[i]) == line) {
				line += strlen(color[i]) - 1;
				in_bag_currently[i] -= lastnum;

				if (in_bag_currently[i] < 0) return 0; 
				lastnum = 0;
			}
		}

		lastnum = parse_int_as_long_as_possible(&line);
		line++;
	}

	return id;

}