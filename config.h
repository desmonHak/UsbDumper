#ifndef _CONFIG_H
#define _CONFIG_H

#ifdef _WIN32

void *folders[][2] = {
	//{ "D:", NULL },
	//{ "E:", NULL },
	//{ "F:", NULL },
	{ "G:", NULL }
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

void *folders[][2] = {
	{ "/media/root",  NULL },
	{ "/media/dtxdf", NULL }

};


#endif

size_t nmemb = sizeof(folders)/16;
size_t end = 0;

#endif
