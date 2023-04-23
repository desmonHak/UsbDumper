#ifndef _CP_H
#define _CP_H

#include <stdio.h>
#include <errno.h>

int cp(char *src, char *dst);

// El buffer para almacenar los datos del archivo
#define CP_BUFF_LIMIT 512

#endif
