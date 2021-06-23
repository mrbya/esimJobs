#ifndef ESIM_MBEDOS_HAL_H_
#define ESIM_MBEDOS_HAL_H_

#include <stdlib.h>

void* platform_malloc(size_t size);
void platform_free(void* pointer);
void platform_log_info(char* format, ...);
void platform_log_error(char* format, ...);

#endif//ESIM_MBEDOS_HAL_H_