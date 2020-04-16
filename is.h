#ifndef _ISDIR_H
#define _ISDIR_H

#include <sys/stat.h>
#include <stdbool.h>

bool isfile(char *name);
bool isdir(char *dir_name);

#endif
