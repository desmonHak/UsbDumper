#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

#include "listin.h"
#include "is.h"
#include "cp.h"
#include "mkdir.h"
#include "concat_name.h"
#include "dirtoname.h"

void listin(char *path, char *outdir) {
    DIR *dir;
    
	struct dirent *dirent;

    char *name = NULL,
		 *dirtocopy = NULL,
		 *aux = NULL;

	dir = opendir(path);

    if (dir != NULL){
		while((dirent = readdir(dir)) != NULL){
			if(strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0){
				name = concat_name(path,
								   dirent->d_name);

				dirtocopy = dirtoname(name);
				aux = concat_name(outdir, dirtocopy);

				if(isdir(name)){
					printf("Creando %s ...\n",
						   aux);

					mkdir_m(aux);

					printf("Listando %s ...\n",
						   name);

					listin(name, outdir);

				}

				if (isfile(name)) {
					printf("Copiando %s ...\n",
						   name);

					cp(name, aux);

				}

				free(name);
				free(aux);

			}
			
		}

        closedir(dir);

    }

}
