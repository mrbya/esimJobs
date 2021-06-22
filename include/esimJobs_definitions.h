#ifndef ESIM_JOBS_DEFINITIONS_H_
#define ESIM_JOBS_DEFINITIONS_H_

#include <stdbool.h>
#include <stdint.h>

#define ESIM_CMD_ID_BUFFER_LEN  30

#define ESIM_JOB_ID_BUFFER_LEN  40
#define ESIM_REC_ID_BUFFER_LEN  40

#define ESIM_JOB_ID_KEY     "EsimJobId"
#define ESIM_RECIPE_ID_KEY  "RecipeId"
#define ESIM_CYCLES_CNT_KEY "CyclesCount"
#define ESIM_INFINITE_KEY   "IsInfinite"
#define ESIM_SCRIPT_KEY     "script"
#define ESIM_CMD_KEY        "EsimCommandKey"
#define ESIM_ARG_KEY        "Values"
#define ESIM_ARG_TYPE_KEY   "ArgumentType"
#define ESIM_ARG_VAL_KEY    "Value"

typedef enum esim_error{
    ESIM_OK,
    ESIM_MALLOC_FAIL,
    ESIM_INVALID_ARG,
    ESIM_INVALID_ARGTYPE,
    ESIM_PARSE_FAIL,
    ESIM_ERR
}esim_err_t;

typedef enum esim_arg_type{
    ESIM_ARG_TEXT,
    ESIM_ARG_INT,
    ESIM_ARG_FLOAT,
    ESIM_ARG_BOOL,
    ESIM_ARG_TIME
}esim_arg_type_t;

typedef struct esim_cmd_argument{
    esim_arg_type_t type;
    void* value;
}esim_arg_t;

typedef struct esim_command{
    char name[ESIM_CMD_ID_BUFFER_LEN];
    esim_arg_t* args;
}esim_cmd_t;

typedef struct esim_recipe{
    char recipeId[ESIM_REC_ID_BUFFER_LEN];
    uint16_t cycles;
    uint16_t currentCycle;
    bool infinite;
    uint16_t currentCmd;
    uint16_t jobLen;
    esim_cmd_t* cmds;
}esim_recipe_t;

typedef struct esim_job{
    char jobId[ESIM_JOB_ID_BUFFER_LEN];
    esim_recipe_t recipe;
}esim_job_t;

#endif//ESIM_JOBS_DEFINITIONS_H_