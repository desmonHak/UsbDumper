char *dirtoname(char *name) {
	int i;
	char *aux = name;

	for (i = 0; name[i] != '/' && name[i] != '\0'; i++) {
		aux += 1;

	}

	if (name[i] != '\0') {
		aux += 1;

	}

	return aux;

}
