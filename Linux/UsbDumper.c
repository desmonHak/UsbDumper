#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

void Buscar( char ruta[200] ,char Ruta_Guardado[200] ,DIR *base );
void Copiar( char *File_Name, char Ruta_Pendrive[200] ,char Ruta_Guardado[200] );
void StrCat(char String_Base[200], char *String_Agregado);
void SacarEspacios(char String[200]);
void CrearCarpeta(char Ruta[200], char *NombreDeCarpeta);
void StrCpyx3 (char String1[200] ,char String1_Agregado[200] ,char String2[200] ,char String2_Agregado[200] ,char String3[200] ,char String3_Agregado[200]);

char Espaciado[50] = "  ";
char Ruta_Pendrive_Base[200];
char Ruta_Guardado_Base[200];


int main(int argc, char *argv[]){

	DIR *dir_comprobacion, *dir;
	struct dirent *ent;

	char Ruta_Guardado[200];   /* Ruta donde se guardaran los datos del pendrive, debe existir la ruta */
	char Ruta_Pendrive[200] = "/media/frijolito/";

	strcpy(Ruta_Guardado, argv[1]);

	if( ( dir_comprobacion = opendir(Ruta_Guardado )) == NULL ){
		printf("  [!!] No se encontro la ruta de guardado. \n");
		exit(-1);	/* Comprobacion si existe cierta ruta de guardado */
	}else{


		closedir( dir_comprobacion );
	}
 
	while( free ){ /* Busca un pendrive conectado, Buscar una forma mas eficiente cuando tenga tiempo */
		dir = opendir( Ruta_Pendrive );
		ent = readdir( dir );

		if( ent->d_type == DT_DIR ){

			StrCat( Ruta_Pendrive, ent->d_name );

			CrearCarpeta(Ruta_Guardado,ent->d_name);

			strcpy( Ruta_Pendrive_Base, Ruta_Pendrive );
			strcpy( Ruta_Guardado_Base, Ruta_Guardado );

			closedir( dir );
			printf("\n  [!!] Se a encontrado el pedrive. \n\n");
			break;
		}
		printf("  [!!] No se a encontrado el pendrive. \n");
		sleep( 1 );
		closedir( dir );
	}

	Buscar( Ruta_Pendrive, Ruta_Guardado ,(dir = opendir(Ruta_Pendrive)) );
	
	printf("\n  [>>] Listo. \n");
	return 0;
}

void Buscar( char Ruta_Pendrive[200] ,char Ruta_Guardado[200] ,DIR *base ){

	struct dirent *ent;
	char Ruta_Pendrive_Base2[200];
	char Ruta_Guardado_Base2[200];

	char EspaciadoBase[50];

	DIR *dir;

	StrCpyx3(Ruta_Guardado_Base2, Ruta_Guardado, Ruta_Pendrive_Base2, Ruta_Pendrive, EspaciadoBase, Espaciado);

	while( (ent = readdir( base )) != NULL ){
		if( (strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name,"..")) != 0 ){
			
			printf( "%s%s\n - ",Espaciado ,ent->d_name );
			if( ent->d_type != DT_DIR ){
				Copiar(ent->d_name, Ruta_Pendrive, Ruta_Guardado);
			
			}else{
	
				StrCat( Ruta_Pendrive, ent->d_name );
				CrearCarpeta(Ruta_Guardado, ent->d_name );
				strcat( Espaciado, "  ");
	
				Buscar( Ruta_Pendrive ,Ruta_Guardado ,dir = opendir(Ruta_Pendrive) );
	
				StrCpyx3(Ruta_Pendrive, Ruta_Pendrive_Base2, Ruta_Guardado, Ruta_Guardado_Base2, Espaciado, EspaciadoBase);	
	
				closedir( dir );
			}
		}
	}

	strcpy( Ruta_Pendrive, Ruta_Pendrive_Base );
	strcpy( Ruta_Guardado, Ruta_Guardado_Base );
	strcpy( Espaciado, "  ");

	StrCpyx3(Ruta_Pendrive, Ruta_Pendrive_Base, Ruta_Guardado, Ruta_Guardado_Base,Espaciado, "  ");
}

void Copiar(char *File_Name, char Ruta_Pendrive[200] , char Ruta_Guardado[200]){

	char Ruta_Pendrive_Copia[200];
	char Ruta_Guardado_Copia[200];

	strcpy( Ruta_Guardado_Copia, Ruta_Guardado );
	strcpy( Ruta_Pendrive_Copia, Ruta_Pendrive );

	strcat( Ruta_Guardado_Copia, "Copia-" );

	strcat( Ruta_Guardado_Copia, File_Name );
	strcat( Ruta_Pendrive_Copia, File_Name );


	FILE *file1 = fopen( Ruta_Guardado_Copia , "w" );
	if( file1 == NULL ){
		printf("  [!!] No se puedo abrir el archivo de escritura. \n" );
	}
	FILE *file2 = fopen( Ruta_Pendrive_Copia , "r" );
	if( file2 == NULL ){
		printf("  [!!] No se puedo abrir el archivo de Lectura. \n" );
	}

	int x;
	while(!feof(file2)){
		x = fgetc(file2);
		fputc(x, file1);
	}

	fclose( file1 );
	fclose( file2 );
}

/* Pequenas Funciones para que el codigo sea mas limpio */

void StrCat( char String_Base[200], char *String_Agregado ){
	strcat( String_Base, String_Agregado );
	strcat( String_Base, "/" );
}

void SacarEspacios( char String[200] ){
	int x = strlen(String);
	for(int i=0 ; i<=x ; i++){
		if(String[i] == ' '){
			String[i] = '_';
		}
	}
}

void CrearCarpeta( char Ruta[200], char *NombreDeCarpeta ){
	char Comando[200] = "mkdir ";
	SacarEspacios(NombreDeCarpeta);
	StrCat(Ruta, NombreDeCarpeta);
	strcat(Comando, Ruta);
	system( Comando );
}

void StrCpyx3 (char String1[200] ,char String1_Agregado[200] ,char String2[200] ,char String2_Agregado[200] ,char String3[200] ,char String3_Agregado[200]){
	strcpy( String1 ,String1_Agregado );
	strcpy( String2 ,String2_Agregado );
	strcpy( String3 ,String3_Agregado );
}