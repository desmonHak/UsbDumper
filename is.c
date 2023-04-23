#include "is.h"

/*
 *	implementacion de dos funciones en C
 *	que se utilizan para determinar si 
 *	un archivo es un directorio o un 
 *	archivo.
 *
 * 	En sistemas operativos basados en 
 * 	Unix, se utiliza la función "lstat" 
 * 	para determinar si un archivo es un 
 * 	directorio o un archivo. En sistemas 
 * 	operativos basados en Windows, se 
 * 	utiliza la función "opendir".
 */

#ifdef _WIN32

/*
 *	se define la función "isdir" que 
 *	acepta una cadena de caracteres 
 *	como argumento, que se espera que 
 *	sea una ruta a un directorio. 
 *	Devuelve un valor booleano que 
 *	indica si el directorio existe o no.
 */

bool isdir(const char* dir_name) {
    DWORD attributes = GetFileAttributes(dir_name);
    if (attributes == INVALID_FILE_ATTRIBUTES) {
        // Ocurrio un error al obtener los atributos del archivo/directorio
		
		puts("error al obtener los atributos del archivo/directorio");
        return false;
    }

    if (attributes & FILE_ATTRIBUTE_DIRECTORY) {
        // La ruta especificada es un directorio
        return true;
    }

    // La ruta especificada es un archivo
    return false;
}

bool isfile(const char *name) {
	/*
	 *	Si el archivo no es un directorio
	 *	Es un archivo
	*/
	return !isdir(name);
}

#else

#include <sys/stat.h>

bool isdir(const char *dir_name) {
	// si dir_name es nulo o el primer caracter no es una /, no es una ruta valida para sistemas unix
	/*if (dir_name == NULL || dir_name[0] != '/') 
        return false;*/

	// Se crea una estructura stat para almacenar información sobre el archivo o directorio
	struct stat st;

	// La función lstat se utiliza para obtener información del archivo o directorio
	if (lstat(dir_name, &st) == -1) {
		return false; // Si la función lstat devuelve -1, indica que se produjo un error al obtener información del archivo o directorio
	}
	// Se devuelve el resultado de la función S_ISDIR, que determina si el archivo o directorio es un directorio
	return S_ISDIR(st.st_mode);
}

bool isfile(const char *name) {
	struct stat st;

	if (lstat(name, &st) == -1) {
		return false;
	}
	// Se devuelve el resultado de la función S_ISREG, que determina si el archivo es un archivo regular
	return S_ISREG(st.st_mode);
}

#endif