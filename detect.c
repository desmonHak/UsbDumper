#include "detect.h"
#include "config.h"

char *detect()
{
    DIR *dir;
    unsigned int i;
    char *file;
    int *id, allow = 1;

    // Iterar hasta que se hayan examinado todas las carpetas o se haya encontrado una carpeta válida
    while (end < nmemb)
    {
        // Iterar sobre todas las carpetas
        for (i = 0; i < nmemb; i++)
        {
            file = folders[i][0];
            id = (int *)folders[i][1];

            // Abrir la carpeta para comprobar si es accesible
            if ((dir = opendir(file)) != NULL)
            {
                // Si la carpeta no se ha examinado todavia
                if (!id)
                {
                    // Saltar los primeros dos elementos, que son "." y ".."
                    readdir(dir);
                    readdir(dir);

                    // Comprobar si hay algún archivo o carpeta en la carpeta
                    if (readdir(dir) != NULL)
                    {
                        // Establecer el identificador de la carpeta a un valor distinto de cero para indicar que se ha examinado
                        folders[i][1] = &allow;
                        end += 1;

                        // Cerrar la carpeta y devolver su nombre
                        closedir(dir);
                        return file;
                    }
                }
                // Si la carpeta ya se ha examinado, simplemente la cerramos
                else
                {
                    closedir(dir);
                }
            }
        }
    }

    // Si no se encontró ninguna carpeta válida, devolver NULL
    return NULL;
}
