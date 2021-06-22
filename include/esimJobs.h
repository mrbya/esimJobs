#ifndef ESIM_JOBS_H_
#define ESIM_JOBS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "esimJobs_definitions.h"
#include "cJSON.h"

esim_err_t parseJob(esim_job_t* job, char* data);
void esimFree(esim_job_t* job);
esim_err_t parseRecipe(esim_recipe_t* recipe, cJSON* data);
esim_err_t parseScript(esim_recipe_t* recipe, cJSON* script);
esim_err_t getStringArg(esim_arg_t* arg, char* buffer);
esim_err_t getIntArg(esim_arg_t* arg, char* buffer);
esim_err_t getFloatArg(esim_arg_t* arg, char* buffer);
esim_err_t getBoolArg(esim_arg_t* arg, char* buffer);
esim_err_t getTimeArg(esim_arg_t* arg, char* buffer);

#ifdef __cplusplus
}
#endif

#endif//ESIM_JOBS_H_