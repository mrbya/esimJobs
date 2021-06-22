cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project(esimJobs VERSION 0.8.0)

#####################################################################################
# COMPILATION OPTIONS
#####################################################################################

option(ESIM_LOGGING "Compile esim platform logging" ON)

#####################################################################################
# DO NOT EDIT - COMMON SOURCE FILES
#####################################################################################

set(commonSources 
srcs/esimJobs.c 
submodule/cJSON/cJSON.c)

#####################################################################################
# PLATFORM SPECIFIC SOURCES AND DEFINITIONS
#####################################################################################

if(ESIM_PLATFORM)
    if(${ESIM_PLATFORM} MATCHES "ESIM_PLATFORM_ESP_IDF")
        set(fullSources ${commonSources} platforms/esp-idf/esim_esp_idf_hal.c)
        add_compile_definitions(ESIM_PLATFORM_ESP_IDF)
    elseif(${ESIM_PLATFORM} MATCHES "ESIM_PLATFORM_MBED_OS")
        set(fullSources ${commonSources} platforms/mbedOS/esim_mbedos_hal.c)
        add_compile_definitions(ESIM_PLATFORM_MBED_OS)
        add_compile_definitions(__MBED__)
    endif()
endif()

#####################################################################################
# LIBRARY
#####################################################################################
add_library(esimJobs ${fullSources})

set_target_properties(esimJobs PROPERTIES C_STANDARD 11)
set(CMAKE_C_STANDARD 11)

target_include_directories(esimJobs PUBLIC .)
target_include_directories(esimJobs PRIVATE ./include)
target_include_directories(esimJobs PRIVATE ./platforms/esp-idf)
target_include_directories(esimJobs PRIVATE ./platforms/mbedos)
target_include_directories(esimJobs PRIVATE ./submodule/cJSON)

#####################################################################################
# PLATFORM SPECIFIC LINKING INSTRUCTIONS
#####################################################################################
if(${ESIM_PLATFORM} MATCHES "CFFS_PLATFORM_ESP32")
    target_link_libraries(cffs idf::log)
    target_link_libraries(cffs idf::spi_flash)
    target_link_libraries(cffs idf::wear_levelling)
endif()

##MBED OS##

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

#####################################################################################
# COMPILE DEFINITIONS
#####################################################################################
add_compile_definitions(${CFFS_PLATFORM})

if(ESIM_LOGGING)
message(STATUS "ESIM logging is ON")
add_compile_definitions(ESIM_LOGGING)
endif()