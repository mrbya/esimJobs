# esimJobs

Library to handle ESIM JOB scripts to control ESIM compatible IOT devices

## Build

EsimJobs library uses pure C and can be built using CMake and a cmd line build tool (GNU Make or Ninja build). However, a platform definition needs to be provided to the library in order to build sucessfully.

Supported platforms:

* ESP-IDF
* mbedOS (soon)

example build for esp-idf

```
mkdir build
cd build
cmake -DESIM_PLATDORM:STRING=ESIM_PLATFORM_ESP_IDF .. -G Ninja
ninja
```
