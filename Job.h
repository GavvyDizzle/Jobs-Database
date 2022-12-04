#ifndef CS203_PROJECT1_JOB_H
#define CS203_PROJECT1_JOB_H

#include "StringArrayList.h"

typedef struct Job_struct {
    char* jobTitle;
    char* companyName;
    char* city;
    char* state;
    int minSalary, maxSalary;
    char* industry;
    StringArrayList *requiredSkills;
    StringArrayList *desiredSkills;
    char* email;
} Job;

/**
 * Creates a new Job
 * @return A pointer to the new Job
 */
Job* createJob();

/**
 * Deletes a job
 * @param j The job
 */
void deleteJob(Job *j);

/**
 * Compares two jobs to determine the order when sorting
 * @param j1 The first job
 * @param j2 The second job
 * @return value < 0 if the first job takes precedence, value > 0 if the second job takes precedence, value = 0 if they are equal
 */
int compareJobs(Job *j1, Job *j2);

/**
 * Prints out the job
 * @param j The job
 */
void printJob(Job *j);

#endif //CS203_PROJECT1_JOB_H
