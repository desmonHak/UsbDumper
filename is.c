#include <stdbool.h>

#ifdef _WIN32

#include <dirent.h>

bool isdir(char *dir_name) {
	DIR *dir = opendir(dir_name);
	bool response;

	if (dir) {
		response = true;
		
	} else {
		response = false;
		
	}
	
	closedir(dir);
	
	return response;
	
}

bool isfile(char *name) {
	return !isdir(name);
	
}

#else

#include <sys/stat.h>

bool isdir(char *dir_name) {
	struct stat st;

	if (lstat(dir_name, &st) == -1) {
		return false;

	}

	return S_ISDIR(st.st_mode);

}

bool isfile(char *name) {
	struct stat st;

	if (lstat(name, &st) == -1) {
		return false;

	}

	return S_ISREG(st.st_mode);

}

#endif