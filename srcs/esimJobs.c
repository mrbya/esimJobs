#include "esimJobs.h"
#include "esimJobs_recipe.h"
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

void esimFree(esim_job_t* job) {
    //esim job cleanup
    platform_free(job -> recipe.cmds -> args);
    platform_free(job -> recipe.cmds);
}//esimFree