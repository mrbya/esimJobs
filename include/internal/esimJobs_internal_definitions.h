#ifndef ESIMJOBS_INTERNAL_DEFINITIONS_H_
#define ESIMJOBS_INTERNAL_DEFINITIONS_H_

#include "esimJobs_definitions.h"

/**
 * @defgroup esimJobs_internal
 * @brief Internal esimJobs functions and definitions
 * 
 * This module includes includes internal definitions and functions of the esimJobs library
 */

/**
 * @defgroup esimJobs_int_defs  ESIM Job internal libraries
 * @ingroup esimJobs_internal
 * @brief ESIM Job internal definitions
 * 
 * Definitions accessible only from inside of the esimJobs library
 * @{
 */

/**
 * @brief ESIM IoT request DTO keys
 */
#define ESIM_RECIPE_ID_KEY  "RecipeId"
#define ESIM_CYCLES_CNT_KEY "CyclesCount"
#define ESIM_INFINITE_KEY   "IsInfinite"
#define ESIM_SCRIPT_KEY     "script"
#define ESIM_CMD_KEY        "EsimCommandKey"
#define ESIM_ARG_KEY        "Values"
#define ESIM_ARG_TYPE_KEY   "ArgumentType"
#define ESIM_ARG_VAL_KEY    "Value"

/** @} */

#endif//ESIMJOBS_INTERNAL_DEFINITIONS_H_