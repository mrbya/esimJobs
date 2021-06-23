#ifndef ESIM_JOBS_H_
#define ESIM_JOBS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "esimJobs_definitions.h"

esim_err_t parseJob(esim_job_t* job, const char* data);
void esimFree(esim_job_t* job);

#ifdef __cplusplus
}
#endif

#endif//ESIM_JOBS_H_