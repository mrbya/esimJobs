#ifndef ESIMJOBS_RECIPE_H_
#define ESIMJOBS_RECIPE_H_

#include "esimJobs_internal_definitions.h"

/**
 * @defgroup esimJobs_recipe ESIM Job recipe functions
 * @ingroup esimJobs_internal
 * @brief ESIM Job recipe functions
 * 
 * EsimJobs internal functions handling ESIM Job recipes.
 * @{
 */

/**
 * @brief Parse ESIM Job recipe
 * 
 * @param recipe ESIM Job recipe struct to hold recipe data
 * @param data recipe JSON data
 * 
 * @return ESIM_OK on success, ESIM_ERR otherwise
 */
esim_err_t parseRecipe(esim_recipe_t* recipe, cJSON* data);

/**
 * @brief Parse ESIM Job recipe script
 * 
 * @param recipe ESIM Job recipe struct to hold script data
 * @param script script JSON data
 * 
 * @return  ESIM_OK on success, ESIM_ERR otherwise
 */
esim_err_t parseScript(esim_recipe_t* recipe, cJSON* script);

/**
 * @brief Get string argument value
 * 
 * @param arg ESIM Job command argument structure to hold argument data
 * @param buffer extracted string argument value
 *  
 * @return ESIM_OK on success, ESIM_ERR otherwise
 */
esim_err_t getStringArg(esim_arg_t* arg, char* buffer);

/**
 * @brief Get integer argument value
 * 
 * @param arg ESIM Job command argument structure to hold argument data
 * @param buffer extracted string argument value
 *  
 * @return ESIM_OK on success, ESIM_ERR otherwise
 */
esim_err_t getIntArg(esim_arg_t* arg, char* buffer);

/**
 * @brief Get float argument value
 * 
 * @param arg ESIM Job command argument structure to hold argument data
 * @param buffer extracted string argument value
 *  
 * @return ESIM_OK on success, ESIM_ERR otherwise
 */
esim_err_t getFloatArg(esim_arg_t* arg, char* buffer);

/**
 * @brief Get boolean argument value
 * 
 * @param arg ESIM Job command argument structure to hold argument data
 * @param buffer extracted string argument value
 *  
 * @return ESIM_OK on success, ESIM_ERR otherwise
 */
esim_err_t getBoolArg(esim_arg_t* arg, char* buffer);

/**
 * @brief Get time argument value
 * 
 * @param arg ESIM Job command argument structure to hold argument data
 * @param buffer extracted string argument value
 *  
 * @return ESIM_OK on success, ESIM_ERR otherwise
 */
esim_err_t getTimeArg(esim_arg_t* arg, char* buffer);

/**
 * @brief ESIM Job command argument cleanup
 */
void freeCmdArgs(esim_cmd_t* cmd);

/**
 * @brief ESIM Job command argument value cleanup
 */
void freeArg(esim_arg_t* arg);

/** @} */

#endif//ESIMJOBS_RECIPE_H_