#ifndef CS203_PROJECT1_JOBMANAGER_H
#define CS203_PROJECT1_JOBMANAGER_H

#include <stdbool.h>
#include "JobArrayList.h"
#include "StringArrayList.h"
#include "Job.h"
#include "LinkedList.h"
#include "bt.h"

/**
 * Creates all LinkedList indexes.
 * @param bt The tree of jobs to index.
 */
void loadJobIndexes(BinaryTree *bt);

/**
 * Frees all LinkedList indexes.
 */
void freeIndexes();

/**
 * Copies all jobs to a LinkedList
 * @param bt The tree to copy
 * @return A LinkedList of jobs
 */
LinkedList* getJobLinkedList(BinaryTree *bt);

/**
 * Loads all jobs from the text file
 * @param bt The tree to save the jobs to
 */
void loadJobs(BinaryTree *bt);

/**
 * Adds a new job to all indexing structures
 * @param bt The tree to add to
 * @param j The job to add
 */
void addNewJob(BinaryTree* bt, Job* j);

/**
 * Updates all indexing structures ordering
 * @param bt The tree to modify
 * @param j The already modified job
 */
void modifyJob(BinaryTree* bt, Job* j);

/**
 * Removes a job from all indexing structures
 * @param bt The tree to remove from
 * @param j The job to remove
 */
void removeJob(BinaryTree* bt, Job* j);

/**
 * Creates an ArrayList from a char* of comma separated values
 * @param str The string to read
 * @return An ArrayList
 */
StringArrayList* getCommaSeparatedArrayList(char* str);

/**
 * Creates an ArrayList from a char* of space separated values
 * @param str The string to read
 * @return An ArrayList
 */
StringArrayList* getSpaceSeparatedArrayList(char* str);

/**
 * Removes all Job entries from the list who's jobTitle doesn't match the input
 * @param ll The LinkedList of Jobs
 * @param str The string to check for
 * @param exactMatch True for exact string matching, false for close string matching
 */
void matchJobTitle(LinkedList *ll, char *str, bool exactMatch);

/**
 * Removes all Job entries from the list who's jobTitle doesn't match the input while checking indexes for faster matching
 * @param ll The LinkedList of Jobs
 * @param str The string to check for
 * @param exactMatch True for exact string matching, false for close string matching
 */
void matchJobTitleIndexed(LinkedList *ll, char *str, bool exactMatch);

/**
 * Removes all Job entries from the list who's companyName doesn't match the input
 * @param ll The LinkedList of Jobs
 * @param str The string to check for
 * @param exactMatch True for exact string matching, false for close string matching
 */
void matchCompanyName(LinkedList *ll, char *str, bool exactMatch);

/**
 * Removes all Job entries from the list who's location doesn't match the input
 * @param ll The LinkedList of Jobs
 * @param str The string to check for
 * @param exactMatch True for exact string matching, false for close string matching
 */
void matchCity(LinkedList *ll, char *str, bool exactMatch);

/**
 * Removes all Job entries from the list who's location doesn't match the input while checking indexes for faster matching
 * @param ll The LinkedList of Jobs
 * @param str The string to check for
 * @param exactMatch True for exact string matching, false for close string matching
 */
void matchCityIndexed(LinkedList *ll, char *str, bool exactMatch);

/**
 * Removes all Job entries from the list who's state doesn't match the input
 * @param ll The LinkedList of Jobs
 * @param str The string to check for
 */
void matchState(LinkedList *ll, char *str);

/**
 * Removes all Job entries from the list who's salary does not fall within the given range
 * @param ll The LinkedList of Jobs
 * @param min The lower salary value
 * @param max The upper salary value
 */
void matchSalary(LinkedList *ll, int min, int max);

/**
 * Removes all Job entries from the list who's industry doesn't match the input
 * @param ll The LinkedList of Jobs
 * @param str The string to check for
 * @param exactMatch True for exact string matching, false for close string matching
 */
void matchIndustry(LinkedList *ll, char *str, bool exactMatch);

/**
 * Removes all Job entries from the list who's industry doesn't match the input while checking indexes for faster matching
 * @param ll The LinkedList of Jobs
 * @param str The string to check for
 * @param exactMatch True for exact string matching, false for close string matching
 */
void matchIndustryIndexed(LinkedList *ll, char *str, bool exactMatch);

/**
 * Removes all Job entries from the list who's required skills don't match the input
 * @param ll The LinkedList of Jobs
 * @param str The string to check for
 * @param exactMatch True for exact string matching, false for close string matching
 */
void matchRequiredSkills(LinkedList *ll, char *str, bool exactMatch);

/**
 * Removes all Job entries from the list who's desired skills don't match the input
 * @param ll The LinkedList of Jobs
 * @param str The string to check for
 * @param exactMatch True for exact string matching, false for close string matching
 */
void matchDesiredSkills(LinkedList *ll, char *str, bool exactMatch);

/**
 * Prints all jobs
 * @param bt The BinaryTree
 */
void printJobs(BinaryTree *bt);

/**
 * Prints all jobs to a file
 * @param bt The BinaryTree
 * @param fp The file
 */
void outputJobs(BinaryTree *bt, FILE* fp);

/**
 * Works just like C's strstr() but ignores case.
 * @param haystack The string to parse
 * @param needle The string to look for
 * @return A pointer to the first occurrence in haystack of any of the entire sequence of characters specified in needle, or a null pointer if the sequence is not present in haystack.
 */
char* stristr(const char *haystack, const char *needle);

#endif //CS203_PROJECT1_JOBMANAGER_H
