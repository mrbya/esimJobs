#ifndef ESIM_JOBS_H_
#define ESIM_JOBS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "esimJobs_definitions.h"

/**
 * @defgroup esimJobs_lib   ESIM Job handling lib
 * @brief Pubicli visible ESIM Job functions
 * 
 * This module includes functions and definitions of the esimJobs lib accessible from the app/FW of embeded SoC os platforms
 */

/**
 * @defgroup esimJobs_func  ESIM Job functions
 * @ingroup esimJobs_lib
 * @brief ESIM Job public functions
 * 
 * @{
 */

/**
 * @brief Parse ESIM Job
 * 
 * @param job ESIM Job struct to hold parsed data
 * @param data ESIM BE GET recipe response body
 * 
 * @return  ESIM_OK on success, ESIM_ERR otherwise
 */
esim_err_t parseJob(esim_job_t* job, const char* data);

/**
 * @brief ESIM Job struct cleanup
 * 
 * @param job ESIM Job struct to be cleaned up
 */
void esimFree(esim_job_t* job);

/** @} */

#ifdef __cplusplus
}
#endif

#endif//ESIM_JOBS_H_