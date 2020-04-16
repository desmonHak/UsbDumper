#include <sys/stat.h>
#include <stdbool.h>

bool isdir(char *dir_name) {
	struct stat st;

	if (lstat(dir_name, &st) == -1) {
		return false;

	}

	return S_ISDIR(st.st_mode);

}

bool isfile(char *dir_name) {
	struct stat st;

	if (lstat(dir_name, &st) == -1) {
		return false;

	}

	return S_ISREG(st.st_mode);

}
