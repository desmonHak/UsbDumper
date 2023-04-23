#ifndef _MKDIR_H
#define _MKDIR_H

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

/* Para crear un directorio independientemente
 * sea de Windows o GNU/Linux */
unsigned int mkdir_m(char *dir_name);

/* Para usar mkdir_m de forma recursiva */
unsigned int mkpath(char *path, unsigned int index, unsigned int limit);

/* Así se calcula el limite */
__attribute__((pure)) unsigned int count_slash(char *path);

#endif
