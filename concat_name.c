#include "concat_name.h"

/*
 *	función "concat_name" concatena el nombre de un 
 *	directorio y el nombre de un archivo para formar 
 *	una ruta completa, utilizando la cadena de caracteres 
 *	definida como separador de ruta en el archivo de 
 *	encabezado correspondiente.
 */
char *concat_name(const char *dir_name, const char *filename) {
	/*
	 *	"dir_size" almacena la longitud de la cadena de 
	 *	caracteres "dir_name", "file_size" almacena la 
	 *	longitud de la cadena de caracteres "filename" y 
	 *	"size" almacena el tamaño total de la cadena 
	 *	resultante.
	 */
    unsigned int dir_size = strlen(dir_name);
    unsigned int file_size = strlen(filename);
    unsigned int size = sizeof(char) * dir_size + file_size + 2; // +2 para tener en cuenta el '/' y el '\0'
    
	/*
	 *	Se declara un puntero a una cadena de caracteres 
	 *	"name" y se reserva la memoria necesaria con la 
	 *	funcion malloc, utilizando "size" como argumento.
	 */
    char *name = (char *)malloc(size);
    if (name == NULL) {
        return NULL; // manejo de errores de malloc
    }
    
	// Se copia la cadena de caracteres "dir_name" en la cadena "name" con la funcion strcpy.
    strcpy(name, dir_name);
    
    if (dir_name[dir_size-1] != PATH_SEPARATOR_CHAR) {
		/*
		 *	Si el ultimo carácter de la cadena "dir_name" no 
		 *	es el separador de ruta, se añade el separador de 
		 *	ruta utilizando la funcion strcat.
		 */
        strcat(name, PATH_SEPARATOR_STRING);
    }
    
	// Se añade la cadena de caracteres "filename" a la cadena "name" utilizando la funcion strcat.
    strcat(name, filename);
    
    return name;
}
