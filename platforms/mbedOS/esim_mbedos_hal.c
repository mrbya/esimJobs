#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "esim_mbedos_hal.h"

void* platform_malloc(size_t size){
    return malloc(size);
}

void platform_free(void* pointer){
    free(pointer);
}

void platform_log_info(char* format, ...){
    #ifdef ESIM_LOGGING
    va_list args;

    printf("ESIM INFO: ");

    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    printf("\r\n");
    #endif
}

void platform_log_error(char* format, ...){
    #ifdef ESIM_LOGGING
    va_list args;

    printf("ESIM ERROR: ");
    
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    printf("\r\n");
    #endif
}