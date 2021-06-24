#ifndef ESIM_MBEDOS_HAL_H_
#define ESIM_MBEDOS_HAL_H_

#include <stdlib.h>


/**
 * @defgroup platform_mbed_os   mbedOS platform HAL
 * @ingroup esimJobs_platform
 * @{
 */

/**
 * @brief Heap memory block allocation
 * 
 * @param size memory block size to be allocated
 * 
 * @return pointer to the allocated memory block
 */
void* platform_malloc(size_t size);

/**
 * @brief Free allocated heap memory block
 * 
 * @param pointer pointer to the allocated memory block to be freed
 */
void platform_free(void* pointer);

/**
 * @brief Info message logging
 * 
 * @param format message format
 * @param .. message arguments
 */
void platform_log_info(char* format, ...);

/**
 * @brief Error message logging
 * 
 * @param format message format
 * @param ... message arguments
 */
void platform_log_error(char* format, ...);

/** @} */

#endif//ESIM_MBEDOS_HAL_H_