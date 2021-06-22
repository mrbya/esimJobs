#ifndef ESIMJOBS_PLATFORM_H_
#define ESIMJOBS_PLATFORM_H_

#ifdef ESIM_PLATFORM_ESP_IDF
#include "esim_esp_idf_hal.h"
#elif ESIM_PLATFORM_MBED_OS
#include "esim_mbedos_hal.h"
#endif

#endif//ESIMJOBS_PLATFORM_H_