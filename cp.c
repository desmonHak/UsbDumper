#include <stdio.h>
#include <errno.h>

#include "cp.h"

int cp(char *src, char *dst) {
	FILE *src_ptr, *dst_ptr;
	
	char buff[CP_BUFF_LIMIT];
	
	size_t readed = 0;

	if (((src_ptr = fopen(src, "rb")) == NULL) || \
		((dst_ptr = fopen(dst, "wb")) == NULL)) {
		return errno;

	}

	while ((readed = fread(buff,
						   sizeof(char),
						   sizeof(buff),
						   src_ptr)) > 0) {
		if (fwrite(buff, sizeof(char),
				   readed,
				   dst_ptr) == 0) {
			break;

		}

	}

	if (readed > 0) {
		buff[readed] = '\0';

	}

	fclose(src_ptr);
	fclose(dst_ptr);

	return errno;

}
