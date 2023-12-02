#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define color_num 3

char* color[color_num] = {"red", "green", "blue"};

int get_power_of_game(char* line);

int main() {
	FILE *file = fopen("./input.txt", "r");
	if (file == NULL) {
		return -1;
	}
	char line[500];
	int sum = 0;

	while (fgets(line, 500, file)) {
		sum+= get_power_of_game(line);
	}

	fclose(file);
	printf("Die Summe der Power der sets ist: %d\n", sum);
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

int max(int a, int b) {
	return a < b ? b : a;
}

void compare_bags(int *max_bag, int *curr_bag) {
	for(int i = 0; i < color_num; i++) {
		max_bag[i] = max(max_bag[i], curr_bag[i]);
		curr_bag[i] = 0;
	}
}

int get_power_of_game(char* line) {
	//ignore Game at beginning
	line += 5;

	int taken_from_bag[color_num] = {0};
	int taken_from_bag_max[color_num] = {0};

	int lastnum = 0;
	while(*line) {
		if (*line == ';') {
			compare_bags(taken_from_bag_max, taken_from_bag);
			line++;
			continue;
		}

		for (int i = 0; i < color_num; i++) {

			if (strstr(line, color[i]) == line) {
				line += strlen(color[i]) - 1;
				taken_from_bag[i] += lastnum;
			}
		}

		lastnum = parse_int_as_long_as_possible(&line);
		line++;
	}

	compare_bags(taken_from_bag_max, taken_from_bag);

	int result = 1;
	for (int i = 0; i < color_num; i++) {
		result *= taken_from_bag_max[i];
	}

	return result;

}