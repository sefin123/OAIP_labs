#include "log.h"
#include <stdarg.h>
#include <time.h>

FILE* logOut = NULL;

void logOpen(char* file)
{
    logOut = fopen(file, "w");
}

void mlog(char* format, ...) {
    FILE* out = logOut;

    time_t now = time(NULL);

    if (!out) {
        out = stderr;
        fprintf(out, "%lld|Log file is not installed!\n", now);
    }

    fprintf(out, "%lld|", now);

    va_list args;
    va_start(args, format);
    vfprintf(out, format, args);
    
    fputc('\n', out);
}