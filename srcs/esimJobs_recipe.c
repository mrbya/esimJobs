#include "esimJobs_recipe.h"
#include "esimJobs_platform.h"

esim_err_t parseRecipe(esim_recipe_t* recipe, cJSON* data) {
    //check input arg
    if (data == NULL) {
        return ESIM_INVALID_ARG;
    }//if (data == NULL)

    //get recipe id
    char* recipeId = cJSON_GetObjectItem(data, ESIM_RECIPE_ID_KEY) -> valuestring;
    if (recipeId != NULL) {
        memcpy(recipe -> recipeId, recipeId, strlen(recipeId) & ESIM_REC_ID_BUFFLEN_MASK);

        //recipeId key buffer cleanup
        free(recipeId);
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
    }//if (script == NULL)

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

        if (cmdName == NULL) return ESIM_PARSE_FAIL;

        memset(command.name, 0, ESIM_CMD_ID_BUFFER_LEN);
        memcpy(command.name, cmdName, strlen(cmdName) & ESIM_CMD_ID_BUFFLEN_MASK);

        //cmd key buffer cleanup
        free(cmdName);

        //get command arguments
        cJSON* args = cJSON_GetObjectItem(cmd, ESIM_ARG_KEY);

        //check args JSON
        if (args == NULL) {
            return ESIM_PARSE_FAIL;
        }//if (args == NULL)

        //allocate space for arguments
        command.argLen = cJSON_GetArraySize(args);
        if ((command.args = (esim_arg_t*)platform_malloc(command.argLen * sizeof(esim_arg_t))) == NULL) {
            return ESIM_MALLOC_FAIL;
        }//if ((command.args = (esim_arg_t))...

        //parase arguments
        for (uint8_t j = 0; j < command.argLen; j++) {
            esim_arg_t argument;
            cJSON* arg = cJSON_GetArrayItem(args, j);

            //check arg JSON
            if (arg == NULL) {
                return ESIM_PARSE_FAIL;
            }//if (arg == NULL)

            //get argument type
            argument.type = (esim_arg_type_t)cJSON_GetObjectItem(arg, ESIM_ARG_TYPE_KEY) -> valueint;

            //get argument value
            char* valBuffer = cJSON_GetObjectItem(arg, ESIM_ARG_VAL_KEY) -> valuestring;

            if (valBuffer == NULL) {
                return ESIM_PARSE_FAIL;
            }//if (valBuffer == NULL)

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

            //value buffer cleanup
            free(valBuffer);

            //save parsed argument
            command.args[j] = argument;

            //arg JSON cleanup
            cJSON_delete(arg);
        }//for (uint8_t j = 0; j < alen; j++)

        //save parsed command
        recipe -> cmds[i] = command;
    }//for (int i = 0; i < recipe->jobLen; i++)

    //args JSON cleanup
    cJSON_delete(args);

    return ret;
}//parseScript

esim_err_t getStringArg(esim_arg_t* arg, char* buffer) {
    //check input arg
    if (buffer == NULL) return ESIM_INVALID_ARG;
    
    if ((arg -> value = platform_malloc(sizeof(char) * strlen(buffer))) == NULL) {
        return ESIM_MALLOC_FAIL;
    }//if (arg -> value...

    //save arg value
    memcpy(arg -> value, buffer, strlen(buffer));

    return ESIM_OK;
}//getStringArg

esim_err_t getIntArg(esim_arg_t* arg, char* buffer) {
    //check input arg
    if (buffer == NULL) return ESIM_INVALID_ARG;

    //allocate space for arg value
    if ((arg -> value = platform_malloc(sizeof(int))) == NULL) {
        return ESIM_MALLOC_FAIL;
    }//if (arg -> value...

    //get int value
    int intbuffer;
    sscanf(buffer, "%d", &intbuffer);

    //save arg value
    memcpy(arg -> value, &intbuffer, sizeof(int));

    return ESIM_OK;
}//getIntArg

esim_err_t getFloatArg(esim_arg_t* arg, char* buffer) {
    //check input arg
    if (buffer == NULL) return ESIM_INVALID_ARG;

    //allocate space for arg value
    if ((arg -> value = platform_malloc(sizeof(float))) == NULL) {
        return ESIM_MALLOC_FAIL;
    }//if (arg -> value...

    //get float value
    float floatbuffer;
    sscanf(buffer, "%f", &floatbuffer);

    //save arg value
    memcpy(arg -> value, &floatbuffer, sizeof(float));

    return ESIM_OK;
}//getFloatArg

esim_err_t getBoolArg(esim_arg_t* arg, char* buffer) {
    //check input arg
    if (buffer == NULL) return ESIM_INVALID_ARG;

    if ((arg -> value = platform_malloc(sizeof(bool))) == NULL) {
        return ESIM_MALLOC_FAIL;
    }//if (arg -> value...

    //get bool value
    bool boolBuffer = false;
    if (strcmp("true", buffer) == 0) boolBuffer = true;
    
    //save arg value
    memcpy(arg -> value, &boolBuffer, sizeof(bool));

    return ESIM_OK;
}//getBoolArg

esim_err_t getTimeArg(esim_arg_t* arg, char* buffer) {
    //check input arg
    if (buffer == NULL) return ESIM_INVALID_ARG;

    if ((arg -> value = platform_malloc(sizeof(unsigned long))) == NULL) {
        return ESIM_MALLOC_FAIL;
    }//if (arg -> value..

    //get time value aka unsigned long timestamp
    unsigned long timeBuffer;
    sscanf(buffer, "%ld", &timeBuffer);
    
    //save arg value
    memcpy(arg -> value, &timeBuffer, sizeof(unsigned long));

    return ESIM_OK;
}//getTimeArg

void freeCmdArgs(esim_cmd_t* cmd) {
    //cleanup command argument values
    for (int i = 0; i < cmd -> argLen; i++) {
        freeArg(&cmd -> args[i]);
    }//for(uint8_t i...
}//freeCmd

void freeArg(esim_arg_t* arg) {
    //cleanup argument value
    if (arg -> value != NULL) {
        free(arg -> value);
    }//if (arg -> value != NULL)
}//freeArg