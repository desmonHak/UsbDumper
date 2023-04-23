#include "main.h"

void usage()
{
	fprintf(stderr, "UsbDumper [-h] [-o] OUTDIR\n");
}


int main(int argc, char *argv[])
{
	int index = 0, do_help = 0, opt;
	char *target = NULL, *outdir = NULL, *concat = NULL, *shortopts = ":ht:o:";
	/*
	 *
	 *	- "index":
	 *		se utiliza para llevar la cuenta de la posicion actual en la lista de argumentos.
	 *
	 *	- "do_help":
	 *		es una bandera que indica si se debe mostrar la ayuda.
	 *
	 *	- "opt":
	 *		se utiliza para almacenar el resultado de la funcion getopt_long.
	 *
	 *	- "target":
	 *		es un puntero a una cadena que se utilizara para almacenar el dispositivo USB detectado.
	 *
	 *	- "outdir":
	 *		es un puntero a una cadena que se utilizara para almacenar el directorio de salida.
	 *
	 * 	- "concat":
	 * 		es un puntero a una cadena que se utilizara para concatenar cadenas de caracteres
	 * 
	 *	- "shortopts": 
	 *		es una cadena de caracteres que especifica las opciones cortas que se esperan, 
	 *		y si alguna de ellas requiere un argumento.
	 *
	 */

	struct option options[] = {
		/*
		 *	crea una estructura de opciones que se utilizara para parsear los argumentos de la linea 
		 *	de comandos. Esta estructura contiene dos miembros, "name" y "has_arg". 
		 *	El miembro "name" es un puntero a una cadena que contiene el nombre de 
		 *	la opcion, mientras que el miembro "has_arg" especifica si la opcion requiere un argumento. 
		 *	
		 *	no_argument: quiere decir que no recibe argumentos el parametro.
		 *	required_argument: dice que requiere un argumento obligatoriamente para el parametro.
		 *	optional_argument: dice que el argumento es opcional
		 */
		{"help", no_argument, &do_help, 1},
		{"outdir", required_argument, NULL, 'o'}

	};

	/*
	 *
	 *	opterr se utiliza para desactivar el comportamiento predeterminado
	 *	de getopt_long que es imprimir un mensaje de error en caso de que 
	 *	se utilice una opcion desconocida. 
	 *	En su lugar, el programa manejara los errores por el mismo.
	 * 
	 */
	opterr = 0;

	/* Cambiamos la codificacion local a Español de españa */
	setlocaleU();

	while ((opt =  getopt_long(argc, argv, shortopts, options, NULL)) != -1)
	{
		/*
		 *	
		 *	Se recorren los argumentos de la línea de comandos. En cada iteracion se 
		 *	obtiene el siguiente parametro y se realiza un switch en funcion de su valor:
		 *


		 *
		 */
		index += 1;

		switch (opt)
		{
		case 'h':
			/*
			 *	Si el parametro es h, se activa la variable do_help, 
			 *	que mostrara la ayuda.
			 */
			do_help = 1;
			break;

		case 'o':
			/*
			 *	Si el parametro es o, se almacena en la variable outdir el siguiente argumento 
		     *	(el directorio donde se volcaran los datos obtenidos).
			 */
			outdir = optarg;
			break;

		case ':':
			/* Si el parametro requiere argumento, pero no se le ha dado, se muestra un mensaje de error */
			fprintf(stderr, "Error: El par" A_ACENT "metro \"-" CHAR_FORMAT "/--" STRING_FORMAT "\" requiere un argumento\n", optopt, options[index].name);
			return EXIT_FAILURE;
		case '?':
		default:
			/* Si el parametro es desconocido, se muestra un mensaje de error indicando la opción de ayuda */
			fprintf(stderr, "Error: El par" A_ACENT "metro propuesto es incorrecto. Use \"-h/--help\" para requerir la ayuda\n");
			return ESRCH;
		}
	}

	if ((index == 0) && (opt == -1))
	{
		/*
		 *	Si no se ha proporcionado ningun parametro o se ha proporcionado uno incorrecto, 
		 *	se muestra un mensaje de error indicando la opción de ayuda.
		 */
		fprintf(stderr, "Error: Usa el par" A_ACENT "metro \"-h/--help\" para mostrar la ayuda\n");
		return EXIT_FAILURE;
	}

	if (do_help)
	{
		/*
		 *	Si se ha activado la variable do_help (por ejemplo, si se ha especificado 
		 *	el parametro -h), se muestra la ayuda y se devuelve el código de exito.
		 */
		usage();
		return EXIT_SUCCESS;
	}

	printf("Esperando dispositivos...\n\n");

	while ((target = detect()) != NULL)
	{
		/*
		 *	Se comienza un bucle donde se espera a que se detecte un dispositivo. 
		 *	Una vez detectado, se muestra el nombre del dispositivo.
		*/
		printf("Dispositivo objetivo: %s\n\n", target);

		if (isdir(target))
		{
			// Si el dispositivo detectado es un directorio valido, se concatena su nombre con el directorio de salida.
			concat = concat_name(outdir, target);
			if (concat == NULL){
				perror("malloc");
			}

			// Se verifica que la ruta de salida exista, y se crea en caso contrario.
			if (mkpath(concat, (outdir[0] == PATH_SEPARATOR_CHAR ? 1 : 0), count_slash(concat)) != 0)
			{
				perror("mkpath");
				free(concat);
				return errno;
			}

			// Se llama a la función "listin" para listar el contenido del directorio detectado y copiarlo a la ruta de salida.
			listin(target, outdir);

			free(concat);

			printf("\nTerminado: \"%s\"\n\n",target);
		}
		else
		{
			// Si el dispositivo detectado no es un directorio valido, se muestra un mensaje de error y se sale de la función con el código de error correspondiente.
			fprintf(stderr, STRING_FORMAT " no es un directorio v" A_ACENT "lido.\n", target);
			return errno;
		}
	}

	printf("Terminado.\n");

	return EXIT_SUCCESS;
}