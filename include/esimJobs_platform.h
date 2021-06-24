#ifndef ESIMJOBS_PLATFORM_H_
#define ESIMJOBS_PLATFORM_H_

/**
 * @defgroup esimJobs_platform  esimJobs platform modules
 * @brief Platform specific modules
 * 
 * This module includes platform specific implementations of the low-level operations such as memory allocation and debug logging.
 * Supported platforms:
 * esp-idf  - ESIM_PLATFORM_ESP_IDF
 * mbedOS   - ESIM_PLATFORM_MBED_OS
 */

#ifdef ESIM_PLATFORM_ESP_IDF
#include "esim_esp_idf_hal.h"
#elif ESIM_PLATFORM_MBED_OS
#include "esim_mbedos_hal.h"
#endif

#endif//ESIMJOBS_PLATFORM_H_