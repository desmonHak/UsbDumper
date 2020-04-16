#include <stdlib.h>
#include <string.h>

char *concat_name(char *dir_name, char *filename) {
	size_t size,
		   dir_size,
		   file_size;

	size_t i, j, k;

	char *name = NULL;
	
	dir_size = strlen(dir_name);
	file_size = strlen(filename);
	size = sizeof(char) * dir_size + file_size + 1;

	name = (char *)malloc(size+1);

	for (i = 0; i < dir_size; i++) {
		name[i] = dir_name[i];

	}

	if (strcmp(dir_name, "/") != 0) {
		name[i++] = '/';

	}

	for (j = i, k = 0; j < size; j++, k++) {
		name[j] = filename[k];

	}

	name[j] = '\0';

	return name;

}
