#include <stdlib.h>
#include <stdarg.h>

#include "esim_esp_idf_hal.h"

#include "esp_system.h"
#include "esp_log.h"

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