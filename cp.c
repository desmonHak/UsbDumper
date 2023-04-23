#include "cp.h"

int cp(char *src, char *dst)
{
	FILE *src_ptr, *dst_ptr;

	char buff[CP_BUFF_LIMIT];

	size_t readed = 0;

	if (((src_ptr = fopen(src, "rb")) == NULL) ||
		((dst_ptr = fopen(dst, "wb")) == NULL))
	{
		return errno;
		/*
		 *	Si se causa un error de apertura
		 *	en alguna de las funciones de fopen
		 *	se retorna el error
		 */
	}

	while ((readed = fread(buff,
						   sizeof(char),
						   sizeof(buff),
						   src_ptr)) > 0)
	{
		/*
		Lee de un fichero apuntado por src_ptr y escribe en un 
		fichero apuntado por dst_ptr en trozos de tamaño 
		sizeof(buff) bytes. 

		La funcion fread lee sizeof(buff) bytes en la matriz 
		buff y devuelve el numero de bytes leidos. El bucle 
		while continua mientras fread devuelva un valor positivo
		(indicando que ha leído algunos bytes). La sentencia 
		if dentro del bucle comprueba si los bytes se han escrito 
		correctamente en el fichero de destino utilizando fwrite. 
		Si la funcion fwrite devuelve 0 (indicando que fallo al escribir 
		los bytes), el bucle se termina usando la sentencia break.

		En resumen, este codigo copia el contenido de un archivo 
		a otro archivo en trozos de un tamaño fijo, y termina 
		la operacion de copia si se produce un error durante 
		la escritura en el archivo de destino.

		*/
		if (fwrite(buff, sizeof(char),
				   readed,
				   dst_ptr) == 0)
		{
			break;
		}
	}

	if (readed > 0)
	{
		buff[readed] = '\0';
	}

	fclose(src_ptr);
	fclose(dst_ptr);

	return errno;
}
