#include "dirtoname.h"

char *dirtoname(char *name) {
	/*
	* Obtiene el nombre del directorio a partir de una ruta completa.
	* Devuelve un puntero al nombre del directorio.
	*/

    // Busca la última aparición del separador de ruta en la cadena
    char *separator = strrchr(name, PATH_SEPARATOR);
    
    // Si no se encuentra el separador, devolver el nombre original
    if (!separator) 
        return name;
    
    // Devuelve un puntero al caracter siguiente al separador
    return separator + 1;
}
