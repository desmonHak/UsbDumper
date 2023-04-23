#ifndef _CONFIG_H
#define _CONFIG_H

#include <stddef.h>

#ifdef _WIN32

// Unidades objetivo para sistemas windows:
void *folders[][2] = {
	//{ "C:", NULL },
	//{ "D:", NULL },
	//{ "E:", NULL },
	//{ "F:", NULL },
	{ "G:", NULL },
	//{ "H:", NULL },
	//{ "I:", NULL },
	//{ "J:", NULL },
	//{ "K:", NULL },
	//{ "L:", NULL },
	//{ "M:", NULL },
	//{ "N:", NULL },
	//{ "O:", NULL },
	//{ "P:", NULL },
	//{ "Q:", NULL },
	//{ "R:", NULL },
	//{ "S:", NULL },
	//{ "T:", NULL },
	//{ "U:", NULL },
	//{ "V:", NULL },
	//{ "X:", NULL },
	//{ "Y:", NULL },
	//{ "Z:", NULL }

};

#else
// unidades objetivo en sistemas linux
void *folders[][2] = {
	{ "/usr",  NULL },
	{ "/root",  NULL },
	{ "/media",  NULL },
	{ "/home",  NULL },
	{ "/etc",  NULL },
};


#endif

// cantidad de directorios:
size_t nmemb = sizeof(folders)/sizeof(folders[0]);
size_t end = 0;

#endif
