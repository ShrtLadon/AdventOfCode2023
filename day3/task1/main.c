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

bool is_symbol_char(char c) {
	return c != '.' && c != '\n' && (c > '9' ||  c < '0');
}

bool check_neighbours(char **lines, int line_count, int x, int y_start, int y_end) {
	for (int i = y_start; i < y_end; i++) {
		//check above
		if (x != 0 && is_symbol_char(lines[x-1][i])) return true;
		if (x != 0 && is_symbol_char(lines[x-1][i + 1])) return true;
		if (x != 0 && y_start != 0 && is_symbol_char(lines[x-1][i - 1])) return true;

		//check below
		if (x != line_count - 1 && is_symbol_char(lines[x+1][i])) return true;
		if (x != line_count - 1 && is_symbol_char(lines[x+1][i + 1])) return true;
		if (x != line_count - 1 && y_start != 0 && is_symbol_char(lines[x+1][i - 1])) return true;

		//check to the left and right
		if (y_start != 0 && is_symbol_char(lines[x][i - 1])) return true;
		if (is_symbol_char(lines[x][i + 1])) return true;
	}

	return false;
}

int main() {
	int line_count = get_num_lines(filepath);
	char** lines = read_lines(filepath, line_count);

	int sum = 0;
	for (int i = 0; i < line_count; i++) {
		for (int j = 0; lines[i][j]; j++) {
			int beginning_num = j;
			int number = parse_int_as_long_as_possible(lines[i], &j);

			if(number != 0 && check_neighbours(lines, line_count, i, beginning_num, j)) {
				 sum += number;
				 printf("line %d : num: %d\n", i, number);
			}
		}
	}

	printf("Die Summe ist: %d\n", sum);
}