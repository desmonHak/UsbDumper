#include "mkdir.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

unsigned int mkdir_m(char *dir_name)
{
	return mkdir(dir_name);
}

#elif __linux__

unsigned int mkdir_m(char *dir_name)
{
	return mkdir(dir_name, 0777);
}
#else
#error "No se pudo identificar el sistema operativo en el que se trabaja"
#endif

char *dir_name(char *path, unsigned int limit)
{
	size_t size = sizeof(char) * strlen(path) + 1;
	size_t k;
	char *aux = (char *)malloc(size);
	unsigned int i, j = 0;

	for (k = 0; k < size; k++)
	{
		aux[k] = path[k];
	}

	aux[k] = 0x0;

	for (i = 0; (j < limit || path[i] != '/') && path[i] != 0x0; i++)
	{
		if (path[i] == '/')
		{
			j += 1;
		}
	}

	aux[i] = 0x0;

	return aux;
}

unsigned int count_slash(char * path)
{
	/*
	 *	La funcion count_slash cuenta el numero
	 *	de barras diagonales ("/") en una cadena
	 *	de caracteres path y devuelve este
	 *	valor como un entero sin signo.
	 *
	 *	La funcion utiliza un bucle for que
	 *	itera sobre cada caracter de la
	 *	cadena path. Si el caracter actual
	 *	es una barra diagonal, incrementa
	 *	un contador j. Al final, la funcion
	 *	devuelve el valor de j, que
	 *	corresponde al numero total de
	 *	barras diagonales en la cadena path.
	 */
	unsigned int j = 0;

	for (unsigned int i = 0; path[i] != 0x0; i++)
		if (path[i] == '/')
			j++;

	return j;
}

unsigned int mkpath(char *path, unsigned int index, unsigned int limit)
{
	/*
	 *	Toma tres argumentos:
	 *	-	path:  ruta completa del directorio a crear.
	 *	-	index: profundidad actual en la ruta.
	 *	-	limit. profundidad maxima permitida.
	 *
	 *	La recursividad es una forma eficiente de
	 *	implementar la funcion mkpath que crea un
	 *	directorio y su ruta completa.
	 *	La recursividad es util en este caso ya que
	 *	la creacion de un directorio puede depender
	 *	de la creacion de su directorio padre.
	 *	Por lo tanto, al usar la recursion,
	 *	creamos primero los directorios padres
	 *	y luego el directorio hijo.
	 *	La funcion mkpath se llama a si misma
	 *	con un indice aumentado en 1 en cada
	 *	llamada, que permite rastrear la
	 *	profundidad de la ruta y asegurarse
	 *	de que no se exceda el limite de profundidad
	 *	establecido.
	 */

	/*
	 *	la funcion llama a dir_name para obtener
	 *	el nombre del directorio padre en la ruta y
	 *	lo almacena en la variable dir.
	 */
	char *dir = dir_name(path, index);
	unsigned int errcod = 0;

	/*
	 *	llama a mkdir_m para crear el directorio.
	 *	Si mkdir_m devuelve un codigo de error
	 *	diferente de 0 y EEXIST (indicando que el
	 *	directorio ya existe), la funcion devuelve
	 *	el codigo de error y libera la memoria
	 *	asignada a dir.
	 */
	if (mkdir_m(dir) != 0)
	{
		errcod = errno;
		if ((errcod != 0) && (errcod != EEXIST))
		{
			free(dir);
			return errcod;
		}
	}

	/*
	 *	Si el indice es igual al limite,
	 *	significa que se a alcanzado la profundidad
	 *	maxima permitida, la funcion devuelve 0
	 *	y libera la memoria asignada a dir.
	 */
	if (index == limit)
	{
		free(dir);
		return 0;
	}

	/*
	 *	De lo contrario, la funcion se llama a
	 *	si misma con un indice aumentado en 1 en
	 *	cada llamada, lo que permite rastrear
	 *	la profundidad de la ruta y asegurarse
	 *	de que no se exceda el limite de
	 *	profundidad establecido.
	 */
	mkpath(path, index + 1, limit);
	free(dir);
	return 0;
}
