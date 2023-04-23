#ifndef _CONCAT_NAME_H
#define _CONCAT_NAME_H

#include <stdlib.h>
#include <string.h>


#ifdef _WIN32 // Si el sistema es Windows, se utiliza el separador de ruta adecuado
    #define PATH_SEPARATOR_CHAR '\\'
    #define PATH_SEPARATOR_STRING "\\"
#else // Si el sistema es Unix, se utiliza el separador de ruta adecuado
    #define PATH_SEPARATOR_CHAR '/'
    #define PATH_SEPARATOR_STRING "/"
#endif

char *concat_name(const char *dir_name, const char *filename);

#endif
