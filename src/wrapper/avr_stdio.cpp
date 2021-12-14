#ifdef UNIT_TEST
#include "avr_stdio.hpp"
#include <string.h>
#include <stdarg.h>

int printf_P(const char *__format, ...){
    va_list args;
    va_start(args, __format);
    char buffer[256];

    if(strlen(__format) > 255){
        printf("printf_P wrapper only supports fmt < 256\n");
        return 0;
    }

    strcpy(buffer, __format);

    char *progmemIdentifier = buffer;
    while(1){
        progmemIdentifier = strstr(progmemIdentifier, "%S");

        if(progmemIdentifier == NULL){
            break;
        }

        memcpy(progmemIdentifier, "%s", 2);
        progmemIdentifier += 2;
    }

    int res = vprintf(buffer, args);

    va_end(args);

    return res;
}

#endif