#include <malloc.h>
#include <string.h>
#include "Job.h"

// Jobs do not allocate space for the ArrayLists because it is assumed to be done outside then set.
Job* createJob() {
    Job *j = malloc(sizeof(Job));
    return j;
}

void deleteJob(Job *j) {
    free(j->jobTitle);
    free(j->companyName);
    free(j->city);
    free(j->state);
    free(j->industry);
    deleteStringArrayListDeep(j->requiredSkills);
    deleteStringArrayListDeep(j->desiredSkills);
    free(j->email);
    free(j);
}

/**
 * Determines what job should come before another by following the format:
 * 1. required skills
 * 2. job title
 * 3. industry
 * 4. state location
 * 5. city location
 * @return value < 0 if the first job takes precedence, value > 0 if the second job takes precedence, value = 0 if they are equal
 */
int compareJobs(Job *j1, Job *j2) {
    int arrSize;
    if (j1->requiredSkills->length < j2->requiredSkills->length) arrSize = j1->requiredSkills->length;
    else arrSize = j2->requiredSkills->length;

    // Checks individual elements
    for (int i = 0; i < arrSize; i++) {
        int compareVal = strcasecmp(getSAL(j1->requiredSkills, i), getSAL(j2->requiredSkills, i));
        if (compareVal != 0) return compareVal;
    }

    // If the ArrayLists are the same, check length of them. If equal, check the other fields
    if (j1->requiredSkills->length < j2->requiredSkills->length) return -1;
    else if (j1->requiredSkills->length < j2->requiredSkills->length) return 1;

    if (strcasecmp(j1->jobTitle, j2->jobTitle) != 0) return strcasecmp(j1->jobTitle, j2->jobTitle);

    if (strcasecmp(j1->industry, j2->industry) != 0) return strcasecmp(j1->industry, j2->industry);

    if (strcasecmp(j1->state, j2->state) != 0) return strcasecmp(j1->state, j2->state);

    if (strcasecmp(j1->city, j2->city) != 0) return strcasecmp(j1->city, j2->city);

    return 0;
}

/**
 * Determines what job should come before another by checking the state
 * @return value < 0 if the first job takes precedence, value > 0 if the second job takes precedence, value = 0 if they are equal
 */
int compareJobsByState(Job *j1, Job *j2) {
    return strcasecmp(j1->state, j2->state);
}

/**
 * Nicely prints out a job.
 */
void printJob(Job *j) {
    printf("Position        >> %s\n", j->jobTitle);
    printf("Industry        >> %s\n", j->industry);
    printf("Location        >> %s, %s\n", j->city, j->state);
    printf("Salary          >> $%d - $%d\n", j->minSalary, j->maxSalary);
    printf("Company         >> %s\n", j->companyName);
    printf("Contact         >> %s\n", j->email);

    printf("Required Skills >> ");
    for (int i = 0; i < j->requiredSkills->length - 1; i++) {
        char* str = getSAL(j->requiredSkills, i);
        printf("%s, ", str);
    }
    printf("%s\n", getSAL(j->requiredSkills, j->requiredSkills->length - 1));

    printf("Desired Skills  >> ");
    for (int i = 0; i < j->desiredSkills->length - 1; i++) {
        char* str = getSAL(j->desiredSkills, i);
        printf("%s, ", str);
    }
    printf("%s\n", getSAL(j->desiredSkills, j->desiredSkills->length - 1));
}
