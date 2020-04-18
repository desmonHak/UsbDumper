#ifndef _CHARS_H
#define _CHARS_H

#ifdef _WIN32

/* Unicode */

#define setlocaleU() setlocale(LC_ALL, "spanish")
#define printfU(format, ...) wprintf(L""format, ##__VA_ARGS__)
#define fprintfU(stream, format, ...) fwprintf(stream, L""format, ##__VA_ARGS__)

#else

#define setlocaleU()
#define printfU(format, ...) printf(format, ##__VA_ARGS__)
#define fprintfU(stream, format, ...) fprintf(stream, format, ##__VA_ARGS__);

#endif

#endif
