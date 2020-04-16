#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

#include "mkdir.h"

#ifdef _WIN32

int mkdir_m(char *dir_name) {
	return mkdir(dir_name);

}

#else

int mkdir_m(char *dir_name) {
	return mkdir(dir_name, 0777);

}

#endif

char *dir_name(char *path, int limit) {
	size_t size = sizeof(char) * strlen(path) + 1;
	size_t k;
	char *aux = (char *)malloc(size);
	int i, j = 0;

	for (k = 0; k < size; k++) {
		aux[k] = path[k];

	}

	aux[k] = '\0';

	for (i = 0; (j < limit || path[i] != '/') && path[i] != '\0'; i++) {
		if (path[i] == '/') {
			j += 1;

		}

	}

	aux[i] = '\0';

	return aux;

}

unsigned int count_slash(char *path) {
	int i, j = 0;

	for (i = 0; path[i] != '\0'; i++) {
		if (path[i] == '/') {
			j += 1;

		}

	}

	return j;

}

int mkpath(char *path, int index,
		   int limit) {
	char *dir = dir_name(path, index);
	int errcod = 0;
	
	if (mkdir_m(dir) != 0) {
		errcod = errno;

		if ((errcod != 0) && (errcod != EEXIST)) {
			free(dir);

			return errcod;

		}

	}

	if (index == limit) {
		free(dir);

		return 0;

	}

	mkpath(path, index + 1, limit);

	free(dir);

	return 0;

}
