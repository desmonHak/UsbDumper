#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>

#include "config.h"

char *detect() {
	DIR *dir;

	size_t i;

	char *file;
	int *id;
	int allow = 1;

	while (end < nmemb) {
		for (i = 0; i < nmemb; i++) {
			file = folders[i][0];
			id = (int *)folders[i][1];

			if ((dir = opendir(file)) != NULL) {
				if (!id) {
					readdir(dir);
					readdir(dir);

					if (readdir(dir) != NULL) {
						folders[i][1] = &allow;
						end += 1;
						closedir(dir);

						return file;

					}

				}

				closedir(dir);

			}

		}

	}

	return NULL;

}
