#include "log.h"
#include <stdarg.h>
#include <time.h>

FILE* logOut = NULL;

void logOpen(char* file) {
    logOut = fopen(file, "w");
}

void logClose(char* file) {
    file = fclose(file);
}

void messageLog(char* format, char* message) {
    FILE* out = logOut;

    time_t now = time(NULL);

    struct tm timeInfo;
    localtime_s(&timeInfo, &now);

    if (!out) {
        out = stderr;
        fprintf(out, "%d:%d:%d|Log file is not opened!\n", timeInfo.tm_hour,timeInfo.tm_min,timeInfo.tm_sec);
    }

    fprintf(out, "%d:%d:%d|", timeInfo.tm_hour,timeInfo.tm_min,timeInfo.tm_sec);

    fprintf(out, format, message);
    
    fputc('\n', out);
}