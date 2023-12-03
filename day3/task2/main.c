#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define max_line_length 200

char *filepath = "../input.txt";

int get_num_lines(char* path) {
	FILE *file = fopen(path, "r");
	if (file == NULL) return 0;

	char buffer[max_line_length];
	int lines = 0;
	while (fgets(buffer, max_line_length, file) != NULL) lines++;

	fclose(file);
	return lines; 
}

char** read_lines(char* path, int max_lines) {
	FILE *file = fopen(path, "r");
	if (file == NULL) return NULL;

	char **result = (char**)malloc(sizeof(char*) * max_lines);
	result[0] = (char*)malloc(sizeof(char) * max_line_length);
	for(int i = 1; fgets(result[i - 1], max_line_length, file) != NULL && i <= max_line_length; i++) {
		result[i] = (char*)malloc(sizeof(char) * max_line_length);
	} 

	fclose(file);
	return result;
}

int power(int base, int exponent) {
	int result = 1;
	for(int i = 0; i < exponent; i++) {
		result *= base;
	}

	return result;
}

int parse_int_as_long_as_possible(char *line, int* index) {
	int digits[3] = {0};
	int digit = 0;

	while ('0' <= line[*index] && line[*index] <= '9') {
		digits[digit] = line[*index] - '0';
		digit++;
		(*index)++;
	}

	int num = 0;
	for (int i = digit - 1; i >= 0; i--) {
		num += power(10, digit - 1 - i) * digits[i];
	}
	return num;
}

typedef struct Point{
	int x;
	int y;
} Point;

Point check_neighbours(char **lines, int line_count, int x, int y_start, int y_end) {
	int gearX = -1;
	int gearY = -1;

	for (int i = y_start; i < y_end; i++) {
		//check above
		if (x != 0 && lines[x-1][i] == '*') {
			gearX = x-1;
			gearY = i;
		}
		
		if (x != 0 && lines[x-1][i + 1] == '*') {
			gearX = x - 1;
			gearY = i + 1;
		}
		
		if (x != 0 && y_start != 0 && lines[x-1][i - 1] == '*') {
			gearX = x - 1;
			gearY = i - 1;
		}

		//check below
		if (x != line_count - 1 && lines[x+1][i] == '*') {
			gearX = x + 1;
			gearY = i;
		} 

		if (x != line_count - 1 && lines[x+1][i + 1] == '*') {
			gearX = x + 1;
			gearY = i + 1;
		}

		if (x != line_count - 1 && y_start != 0 && lines[x+1][i - 1] == '*') {
			gearX = x + 1;
			gearY = i - 1;
		}

		//check to the left and right
		if (y_start != 0 && lines[x][i - 1] == '*') {
			gearX = x;
			gearY = i - 1;		
		}

		if (lines[x][i + 1] == '*') {
			gearX = x;
			gearY = i + 1;
		}
	}

	Point gear = {gearX, gearY};
	return gear;
}

int main() {
	int line_count = get_num_lines(filepath);
	char** lines = read_lines(filepath, line_count);

	int** gear_numbers = (int**)malloc(sizeof(int*) * line_count);
	for(int i = 0; i < line_count; i++) {
		gear_numbers[i] = (int*)malloc(sizeof(int) * max_line_length);
		for (int j = 0; j < max_line_length; j++) {
			gear_numbers[i][j] = 0;
		}
	} 

	int sum = 0;
	for (int i = 0; i < line_count; i++) {
		for (int j = 0; lines[i][j]; j++) {
			int beginning_num = j;
			int number = parse_int_as_long_as_possible(lines[i], &j);

			Point gear = check_neighbours(lines, line_count, i, beginning_num, j);
			if (gear.x == -1 && gear.y == -1) {
				continue;
			}

			if (gear_numbers[gear.x][gear.y] == 0) {
				gear_numbers[gear.x][gear.y] = number;
				continue;
			}

			sum += gear_numbers[gear.x][gear.y] * number;
		}
	}

	printf("Die Summe ist: %d\n", sum);
}