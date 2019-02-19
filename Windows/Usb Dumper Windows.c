#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <windows.h>

void Buscar( char ruta[200], char Ruta_Pendrive_Base[200] ,char Ruta_Guardado[200] ,DIR *base );
void Copiar( char *File_Name, char Ruta_Pendrive[200] ,char Ruta_Guardado[200] );

int main(int argc, char *argv[]){

	DIR *dir_comprobacion, *dir;
	struct dirent *ent;

	char Ruta_Guardado[200];   /* Ruta donde se guardaran los datos del pendrive, debe existir la ruta */
	char Ruta_Pendrive[200] = "E:/";
	char Ruta_Pendrive_Base[200];

	strcpy(Ruta_Guardado, argv[1]);

	if( ( dir_comprobacion = opendir(Ruta_Guardado )) == NULL ){
		printf("  [!!] No se encontro la ruta de guardado. \n");
		exit(-1);	/* Comprobacion si existe cierta ruta de guardado */
	}else{
		strcat(Ruta_Guardado, "/Copia-");
		closedir( dir_comprobacion );
	}
 
	while( free ){ /* Busca un pendrive conectado, Buscar una forma mas eficiente cuando tenga tiempo */
		dir = opendir( Ruta_Pendrive );
		if( dir == NULL ){
			printf("  [!!] No se a encontrado el pendrive. \n");
		}else{
			closedir( dir );
			break;	
		}
		Sleep( 1000 );
		closedir( dir );
	}

	printf("  [!!] Pendrive encontrado. \n");
	Buscar( Ruta_Pendrive, Ruta_Pendrive_Base, Ruta_Guardado ,(dir = opendir(Ruta_Pendrive)) );
	
	printf("\n  [>>] Listo. \n");
	return 0;
}

char Espaciado[50] = "  ";

void Buscar( char Ruta_Pendrive[200] ,char Ruta_Pendrive_Base[200] ,char Ruta_Guardado[200] ,DIR *base ){

	struct dirent *ent;
	char Ruta_Pendrive_Base2[200];
	char EspaciadoBase[50];

	DIR *dir;

	strcpy (EspaciadoBase ,Espaciado );
	strcpy( Ruta_Pendrive_Base2 ,Ruta_Pendrive );

	while( (ent = readdir( base )) != NULL ){
		if( (strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name,"..")) != 0 ){
			if( ent->d_type != DT_DIR ){
				printf( "%s%s      ",Espaciado ,ent->d_name );
				Copiar(ent->d_name, Ruta_Pendrive, Ruta_Guardado);

			}else{
				printf( "%s%s\n",Espaciado ,ent->d_name );

				strcat( Ruta_Pendrive, ent->d_name );
				strcat( Ruta_Pendrive, "/" );
				
				strcat( Espaciado, "  ");

				Buscar( Ruta_Pendrive, Ruta_Pendrive_Base ,Ruta_Guardado ,dir = opendir(Ruta_Pendrive) );

				strcpy( Ruta_Pendrive, Ruta_Pendrive_Base2 );
				strcpy( Espaciado, EspaciadoBase);
				closedir( dir );
			}
		}
	}
	strcpy( Espaciado, "  ");
	strcpy( Ruta_Pendrive, Ruta_Pendrive_Base );

}

void Copiar(char *File_Name, char Ruta_Pendrive[200] , char Ruta_Guardado[200]){

	char Ruta_Pendrive_Copia[200];
	char Ruta_Guardado_Base[200];

	strcpy( Ruta_Guardado_Base, Ruta_Guardado );
	strcpy( Ruta_Pendrive_Copia, Ruta_Pendrive );

	strcat( Ruta_Pendrive_Copia, File_Name );
	strcat( Ruta_Guardado_Base, File_Name );

	FILE *file1 = fopen( Ruta_Guardado_Base , "wb" );
	if( file1 == NULL ){
		printf("  [!!] No se puedo abrir el archivo de escritura. \n" );
	}
	FILE *file2 = fopen( Ruta_Pendrive_Copia , "rb" );
	if( file2 == NULL ){
		printf("  [!!] No se puedo abrir el archivo de Lectura. \n" );
	}

	int x;
	while( (x = fgetc(file2)) != EOF ){
		fputc(x, file1);
	}

	printf( "Listo. \n" );

	fclose( file1 );
	fclose( file2 );
}
