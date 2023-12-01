#include <stdlib.h>

char** read_lines(char* path, int max_line_length, int max_lines) {
	File *file = fopen(path, "r");
	if (file == NULL) return NULL;

	char **result = (char**)malloc(sizeof(char*) * max_lines);
	result[0] = (char*)malloc(sizeof(char) * max_line_length)
	for(int i = 1; fgets(result[i - 1], max_line_length, file) != NULL && i <= max_line_length; i++) {
		result[i] = (char*)malloc(sizeof(char) * max_line_length);
	} 

	fclose(file);
	return result;
}