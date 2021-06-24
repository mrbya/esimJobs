#ifndef ESIM_JOBS_DEFINITIONS_H_
#define ESIM_JOBS_DEFINITIONS_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "cJSON.h"

/**
 * @defgroup esimJobs_defs  esimJobs lib definitions
 * @ingroup esimJobs_lib
 * @brief ESIM Job public definitions
 * 
 * Definitions accessible from outside of the esimJobs library
 * @{
 */

#define ESIM_JOB_ID_KEY     "EsimJobId"

#define ESIM_CMD_ID_BUFFER_LEN  30

#define ESIM_JOB_ID_BUFFER_LEN  40
#define ESIM_REC_ID_BUFFER_LEN  40

/**
 * @brief ESIM Job return coddes
 */
typedef enum esim_error{
    ESIM_OK,                /**< ESIM operation completed successfully. */
    ESIM_MALLOC_FAIL,       /**< Failed to alocate heap space. */
    ESIM_INVALID_ARG,       /**< Invalid input argument. */
    ESIM_INVALID_ARGTYPE,   /**< Unknown command argument type. */
    ESIM_PARSE_FAIL,        /**< ESIM Job parse failure. */
    ESIM_ERR                /**< Unspecified ESIM error or feature not implemented yet. */
}esim_err_t;

/**
 * @brief ESIM Job command argument vylue types
 */
typedef enum esim_arg_type{
    ESIM_ARG_TEXT,          /**< String argument value. */
    ESIM_ARG_INT,           /**< Integet argument value. */
    ESIM_ARG_FLOAT,         /**< Float argument value. */
    ESIM_ARG_BOOL,          /**< Boolean argument value. */
    ESIM_ARG_TIME           /**< Time argument value aka timestamp i nthe form of an unsigned long. */
}esim_arg_type_t;

/**
 * @brief Structure to hold ESIM Job command argument data
 */
typedef struct esim_cmd_argument{
    esim_arg_type_t type;   /**< Argument value type. */
    void* value;            /**< Pointer to the argument value. */
}esim_arg_t;

/**
 * @brief Structure to hold ESIM Job command data
 */
typedef struct esim_command{
    char name[ESIM_CMD_ID_BUFFER_LEN];  /**< Command key. */
    uint8_t argLen;                     /**< Number of command arguments. */
    esim_arg_t* args;                   /**< Pointer to command arguments. */
}esim_cmd_t;

/**
 * @brief Structure to hold ESIM Job recipe aka a sequence of commands
 */
typedef struct esim_recipe{
    char recipeId[ESIM_REC_ID_BUFFER_LEN];  /**< Recipe ID. */
    uint16_t cycles;                        /**< Number of recipe cycles. */
    uint16_t currentCycle;                  /**< Current cycle. */
    bool infinite;                          /**< Indicator of infinite recipe loop. */
    uint16_t currentCmd;                    /**< Current recipe command being executed. */
    uint16_t jobLen;                        /**< Number of recipe commands. */
    esim_cmd_t* cmds;                       /**< Pointer to recipe commands. */
}esim_recipe_t;

/**
 * @brief ESIM Job data structure
 */
typedef struct esim_job{
    char jobId[ESIM_JOB_ID_BUFFER_LEN];     /**< ESIM Job ID. */
    esim_recipe_t recipe;                   /**< ESIM Job recipe data. */
}esim_job_t;

/** @} */

#endif//ESIM_JOBS_DEFINITIONS_H_