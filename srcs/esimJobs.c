#include <stdio.h>
#include <string.h>

#include "esimJobs.h"
#include "esimJobs_platform.h"

esim_err_t parseJob(esim_job_t* job, char* data) {
    //check input arg
    if (data == NULL) {
        return ESIM_INVALID_ARG;
    }//if (data == NULL)

    //convert input string into a JSON object
    cJSON* cData = cJSON_Parse(data);

    //check conversion result
    if (cData == NULL) return ESIM_PARSE_FAIL;

    //get jobId
    char* jobId = cJSON_GetObjectItem(cData, ESIM_JOB_ID_KEY) -> valuestring;
    if (jobId != NULL) {
        memcpy(job -> jobId, jobId, strlen(jobId));
        //cJSON_free(jobId);
    }//if (jobId != NULL)

    //parse recipe
    esim_err_t ret = parseRecipe(&job -> recipe, cData);

    //cleanup
    if (cData == NULL) {
        return ESIM_PARSE_FAIL;
    } else {
        //cJSON_Delete(cData);
    }//if (cData == NULL)

    return ret;
}//parseJob

esim_err_t parseRecipe(esim_recipe_t* recipe, cJSON* data) {
    //check input arg
    if (data == NULL) {
        return ESIM_INVALID_ARG;
    }//if (data == NULL)

    //get recipe id
    char* recipeId = cJSON_GetObjectItem(data, ESIM_RECIPE_ID_KEY) -> valuestring;
    if (recipeId != NULL) {
        memcpy(recipe -> recipeId, recipeId, strlen(recipeId));
        //cJSON_free(recipeId);
    }//if (recipeId != NULL)

    //get cycles count
    recipe -> cycles = (uint16_t)cJSON_GetObjectItem(data, ESIM_CYCLES_CNT_KEY) -> valueint;
    
    //get infinite loop switch
    recipe -> infinite = (bool)cJSON_GetObjectItem(data, ESIM_INFINITE_KEY) -> valueint;

    //get script data
    char* sstr = cJSON_GetObjectItem(data, ESIM_SCRIPT_KEY) -> valuestring;
    cJSON* script = cJSON_Parse(sstr);
    return parseScript(recipe, script);
}//parseRecipe

esim_err_t parseScript(esim_recipe_t* recipe, cJSON* script) {
    esim_err_t ret = ESIM_OK;

    //check input arg
    if (script == NULL) {
        return ESIM_INVALID_ARG;
    }//if (data == NULL)

    //get recipe length and allocate space for commands
    recipe -> jobLen = cJSON_GetArraySize(script);
    if ((recipe -> cmds = (esim_cmd_t*)platform_malloc(recipe->jobLen * sizeof(esim_cmd_t))) == NULL) {
        return ESIM_MALLOC_FAIL;
    }//if ((recipe -> cmds...

    //parse commands
    for (int i = 0; i < recipe->jobLen; i++) {
        //get command
        esim_cmd_t command;
        cJSON* cmd = cJSON_GetArrayItem(script, i);

        //get command key
        char* cmdName = cJSON_GetObjectItem(cmd, ESIM_CMD_KEY) -> valuestring;
        memcpy(command.name, cmdName, strlen(cmdName));
        //if (cmdName != NULL) cJSON_free(cmdName);

        //get command arguments
        cJSON* args = cJSON_GetObjectItem(cmd, ESIM_ARG_KEY);

        //allocate space for arguments
        size_t alen = cJSON_GetArraySize(args);
        if ((command.args = (esim_arg_t*)platform_malloc(alen * sizeof(esim_arg_t))) == NULL) {
            return ESIM_MALLOC_FAIL;
        }//if ((command.args = (esim_arg_t))...

        //parase arguments
        for (uint8_t j = 0; j < alen; j++) {
            esim_arg_t argument;
            cJSON* arg = cJSON_GetArrayItem(args, j);

            //get argument type
            argument.type = (esim_arg_type_t)cJSON_GetObjectItem(arg, ESIM_ARG_TYPE_KEY) -> valueint;

            //get argument value
            char* valBuffer = cJSON_GetObjectItem(arg, ESIM_ARG_VAL_KEY) -> valuestring;

            //parse argument value
            switch (argument.type) {
                case ESIM_ARG_TEXT:
                    ret |= getStringArg(&argument, valBuffer);
                    break;

                case ESIM_ARG_INT:
                    ret |= getIntArg(&argument, valBuffer);
                    break;

                case ESIM_ARG_FLOAT:
                    ret |= getFloatArg(&argument, valBuffer);
                    break;

                case ESIM_ARG_BOOL:
                    ret |= getBoolArg(&argument, valBuffer);
                    break;
                
                case ESIM_ARG_TIME:
                    ret |= getTimeArg(&argument, valBuffer);
                    break;

                default:
                    ret |= ESIM_INVALID_ARGTYPE;
                    break;
            }//switch (argument.type)

            //cleanup
            //if (valBuffer != NULL) cJSON_free(valBuffer);

            //save parsed argument
            command.args[j] = argument;
        }//for (uint8_t j = 0; j < alen; j++)

        //save parsed command
        recipe -> cmds[i] = command;
    }//for (int i = 0; i < recipe->jobLen; i++)

    return ret;
}//parseScript

esim_err_t getStringArg(esim_arg_t* arg, char* buffer) {
    //check input arg
    if (buffer == NULL) return ESIM_INVALID_ARG;
    
    //get string value
    char stringBuffer[30];
    memcpy(stringBuffer, buffer, strlen(buffer));
    arg -> value = &stringBuffer;

    return ESIM_OK;
}//getStringArg

esim_err_t getIntArg(esim_arg_t* arg, char* buffer) {
    //check input arg
    if (buffer == NULL) return ESIM_INVALID_ARG;

    //get int value
    int intbuffer;
    sscanf(buffer, "%d", &intbuffer);
    arg -> value = &intbuffer;

    return ESIM_OK;
}//getIntArg

esim_err_t getFloatArg(esim_arg_t* arg, char* buffer) {
    //check input arg
    if (buffer == NULL) return ESIM_INVALID_ARG;

    //get float value
    float floatbuffer;
    sscanf(buffer, "%f", &floatbuffer);
    arg -> value = &floatbuffer;

    return ESIM_OK;
}//getFloatArg

esim_err_t getBoolArg(esim_arg_t* arg, char* buffer) {
    //check input arg
    if (buffer == NULL) return ESIM_INVALID_ARG;

    //get bool value
    bool boolBuffer = false;
    if (strcmp("true", buffer) == 0) boolBuffer = true;
    arg -> value = &boolBuffer;

    return ESIM_OK;
}//getBoolArg

esim_err_t getTimeArg(esim_arg_t* arg, char* buffer) {
    //check input arg
    if (buffer == NULL) return ESIM_INVALID_ARG;

    //get time value aka unsigned long timestamp
    unsigned long timeBuffer;
    sscanf(buffer, "%ld", &timeBuffer);
    arg -> value = &timeBuffer;

    return ESIM_OK;
}//getTimeArg

void esimFree(esim_job_t* job) {
    //esim job cleanup
    platform_free(job -> recipe.cmds -> args);
    platform_free(job -> recipe.cmds);
}//esimFree