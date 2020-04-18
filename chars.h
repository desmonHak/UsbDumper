#ifndef _CHARS_H
#define _CHARS_H

#ifdef _WIN32

/* Unicode */

#define setlocaleU() setlocale(LC_ALL, "spanish")
#define fprintf(stream, format, ...) fprintf(stream, L""format, ##__VA_ARGS__)

/* Unicode formats */

#define STRING_FORMAT "%S"
#define CHAR_FORMAT "%lc"

#else

#define setlocaleU()

#define STRING_FORMAT "%s"
#define CHAR_FORMAT "%lc"

#endif

/* Unicode codes */

#define A_ACENT "\u00E1"

#endif
