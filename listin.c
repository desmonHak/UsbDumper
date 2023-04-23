#include "listin.h"

void listin(char *path, char *outdir)
{
    // Se declara un puntero a DIR y una estructura dirent para recorrer el directorio.
	DIR *dir;
	// Se declaran punteros para el nombre del archivo, la ruta de destino y una cadena auxiliar.
	struct dirent *dirent;
	char *name = NULL, *dirtocopy = NULL, *aux = NULL;

	dir = opendir(path);
	// Se abre el directorio y se comprueba si se abrio correctamente.
	if (dir != NULL)
	{
		// Se recorre el directorio
		while ((dirent = readdir(dir)) != NULL)
		{
			// Si el nombre del archivo no es "." o "..", se procede a trabajar con El.
			if (strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0)
			{
				// Se obtiene el nombre completo del archivo (directorio o archivo) concatenando la ruta y el nombre.
				name = concat_name(path, dirent->d_name);
				// Se obtiene el nombre del archivo sin la ruta.
				dirtocopy = dirtoname(name);
				// Se concatena el nombre del directorio de destino con el nombre del archivo sin la ruta para obtener la ruta completa de destino.
				aux = concat_name(outdir, dirtocopy);

				// Si es un directorio, se crea el directorio de destino y se procede a listar sus archivos y directorios.
				if (isdir(name))
				{
					printf("Creando %s ...\n", aux);
					mkdir_m(aux);

					printf("Listando %s ...\n", name);
					listin(name, outdir);
				}
				else  {
					// Si es un archivo, se copia al directorio de destino.
					printf("Copiando %s ...\n", name);
					int err = cp(name, aux);
					if(err != 0){
						printf("Ha ocurrido un error durante la copia de archivos. error: %d\n", err);
					}
				}

				// Se liberan los punteros utilizados y se los establece en NULL.
				free(name);
				free(aux);
				name = aux = NULL;
			}
		}
		// Se cierra el directorio.
		closedir(dir);
	}
}
