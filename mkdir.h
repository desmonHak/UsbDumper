#ifndef _MKDIR_H
#define _MKDIR_H

/* Para crear un directorio independientemente
 * sea de WIndows o GNU/Linux */
int mkdir_m(char *dir_name);

/* Para usar mkdir_m de forma recursiva */
int mkpath(char *path, int index,
		   int limit);

/* Así se calcula el limite */
unsigned int count_slash(char *path);

#endif
