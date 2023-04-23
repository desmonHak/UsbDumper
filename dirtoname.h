#ifndef _DIRTONAME_H
#define _DIRTONAME_H

#include <string.h>

    #ifdef _WIN32 // Si el sistema es Windows, se utiliza el separador de ruta adecuado
        #define PATH_SEPARATOR '\\'
    #else // Si el sistema es Unix, se utiliza el separador de ruta adecuado
        #define PATH_SEPARATOR '/'
    #endif

char *dirtoname(char *name);

#endif
