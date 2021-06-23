#ifndef ESIMJOBS_RECIPE_H_
#define ESIMJOBS_RECIPE_H_

#include "esimJobs_internal_definitions.h"

esim_err_t parseRecipe(esim_recipe_t* recipe, cJSON* data);
esim_err_t parseScript(esim_recipe_t* recipe, cJSON* script);
esim_err_t getStringArg(esim_arg_t* arg, char* buffer);
esim_err_t getIntArg(esim_arg_t* arg, char* buffer);
esim_err_t getFloatArg(esim_arg_t* arg, char* buffer);
esim_err_t getBoolArg(esim_arg_t* arg, char* buffer);
esim_err_t getTimeArg(esim_arg_t* arg, char* buffer);

#endif//ESIMJOBS_RECIPE_H_