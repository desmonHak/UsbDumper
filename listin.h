#ifndef _LISTIN_H
#define _LISTIN_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

#include "is.h"
#include "cp.h"
#include "mkdir.h"
#include "concat_name.h"
#include "dirtoname.h"

void listin(char *path, char *outdir);

#endif
