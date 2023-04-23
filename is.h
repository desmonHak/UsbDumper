#ifndef _ISDIR_H
#define _ISDIR_H

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/stat.h>
#endif

#include <stdbool.h>
#include <stdbool.h>
#include <dirent.h>
#include <stdio.h>

bool isfile(const char *name);
bool isdir(const char *dir_name);

#endif
