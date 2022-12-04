#ifndef CS203_PROJECT1_JOBMANAGER_H
#define CS203_PROJECT1_JOBMANAGER_H

#include <stdbool.h>
#include "JobArrayList.h"
#include "StringArrayList.h"
#include "Job.h"
#include "LinkedList.h"

/**
 * Creates all LinkedList indexes.
 * @param jm The list of jobs to index.
 */
void loadJobIndexes(JobArrayList *jm);

/**
 * Frees all LinkedList indexes.
 */
void freeIndexes();

/**
 * Copies all jobs to a LinkedList
 * @param jm The list to copy
 * @return A LinkedList of jobs
 */
LinkedList* getJobLinkedList(JobArrayList *jm);

/**
 * Loads all jobs from the text file
 * @param jm The list to save the jobs to
 */
void loadJobs(JobArrayList *jm);

/**
 * Loads all job indexes
 * @param jm The list of jobs to index
 */
void loadJobIndexes(JobArrayList *jm);

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
 * @param arr The list of jobs
 */
void printJobs(JobArrayList *arr);

/**
 * Works just like C's strstr() but ignores case.
 * @param haystack The string to parse
 * @param needle The string to look for
 * @return A pointer to the first occurrence in haystack of any of the entire sequence of characters specified in needle, or a null pointer if the sequence is not present in haystack.
 */
char* stristr(const char *haystack, const char *needle);

#endif //CS203_PROJECT1_JOBMANAGER_H
