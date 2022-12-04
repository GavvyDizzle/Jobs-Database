#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "JobManager.h"

JobArrayList *jal;
bool exactMatching = false;

/**
 * Prints all jobs to the screen after a successful job search.
 * @param ll The LinkedList of jobs.
 */
void printValidSearchMessage(LinkedList *ll) {
    printf("----------(%d Matched Job Listings)----------\n", ll->length);
    printLinkedList(ll);
    printf("----------(%d Matched Job Listings)----------\n", ll->length);
}

/**
 * Prints the message when the jobs list is empty.
 */
void printEmptySearchMessage() {
    printf("----------------------------------------\n");
    printf("Your job search returned no results!\n");
    printf("----------------------------------------\n");
}

/**
 * Handles the message to print after a valid command is completed.
 * @param ll The LinkedList of jobs
 */
void printSearchMessage(LinkedList *ll) {
    if (ll->length == 0) printEmptySearchMessage();
    else printValidSearchMessage(ll);
}

/**
 * Handles when the search command is run.
 * Asks the user for input for each of the Job criteria.
 */
void runSearch() {
    printf("Note: Leaving any input blank ignores that field\n");

    char input[256];
    LinkedList *ll = getJobLinkedList(jal);

    printf("Enter job title(s): ");
    gets(input);
    if (strlen(input) != 0) {
        matchJobTitleIndexed(ll, input, exactMatching); // Call the index function because the list still contains all elements
    }

    printf("Enter company name(s): ");
    gets(input);
    if (strlen(input) != 0) {
        matchCompanyName(ll, input, exactMatching);
    }

    printf("Enter location(s): ");
    gets(input);
    if (strlen(input) != 0) {
        matchCity(ll, input, exactMatching);
    }

    printf("Enter state(s): ");
    gets(input);
    if (strlen(input) != 0) {
        matchState(ll, input);
    }

    printf("Enter salary range (x y): ");
    gets(input);
    if (strlen(input) != 0) {
        StringArrayList *arr = getSpaceSeparatedArrayList(input);
        int a = 0;
        int b = 1000000000;

        if (getSAL(arr, 0) != NULL) {
            a = (int) strtol(getSAL(arr, 0), NULL, 0);
        }
        if (getSAL(arr, 1) != NULL) {
            b = (int) strtol(getSAL(arr, 1), NULL, 0);
        }

        matchSalary(ll, a, b);
        deleteStringArrayList(arr);
    }

    printf("Enter industry(s): ");
    gets(input);
    if (strlen(input) != 0) {
        matchIndustry(ll, input, exactMatching);
    }

    printf("Enter required skills(s): ");
    gets(input);
    if (strlen(input) != 0) {
        matchRequiredSkills(ll, input, exactMatching);
    }

    printf("Enter desired skills(s): ");
    gets(input);
    if (strlen(input) != 0) {
        matchDesiredSkills(ll, input, exactMatching);
    }

    printSearchMessage(ll);
    deleteLinkedList(ll);
}

/**
 * Handles when a command is given
 * @param cmd The first command (a single character)
 */
void runListCommand(char cmd) {
    if (cmd == 'l') {
        printf("Enter location (city,state): ");
    }
    else if (cmd == 'i') {
        printf("Enter industry(s): ");
    }
    else if (cmd == 't') {
        printf("Enter job title(s): ");
    }
    else {
        printf("No argument provided!\nl (l/i/t) = (location/industry/title) list matching jobs\n");
        return;
    }

    LinkedList *ll = getJobLinkedList(jal);
    char input[256];
    gets(input);

    if (cmd == 'l') {
        printf("Enter location (city,state): ");
        StringArrayList *arr = getCommaSeparatedArrayList(input);
        if (arr->length != 2) {
            printf("Incorrect location format. It must be formatted city,state\n");
            deleteStringArrayList(arr);
            deleteLinkedList(ll);
            return;
        }

        matchCityIndexed(ll, getSAL(arr, 0), exactMatching);
        matchState(ll, getSAL(arr, 1));
        deleteStringArrayList(arr);
    }
    else if (cmd == 'i') {
        matchIndustryIndexed(ll, input, exactMatching);
    }
    else {
        matchJobTitleIndexed(ll, input, exactMatching);
    }

    printSearchMessage(ll);
    deleteLinkedList(ll);
}

/**
 * Prints the help message.
 * This message is printed when the program starts and when an invalid command is given.
 */
void printHelpMessage() {
    printf("---(Job Search Help)---\n");
    printf("p = print out all jobs\n");
    printf("x = exit program\n");
    printf("s = enter job search\n");
    printf("t = toggle exact matching (currently ");
    if (exactMatching) printf("enabled");
    else printf("disabled");
    printf(")\n");
    printf("l (l/i/t) = (location/industry/title) list matching jobs\n");
}

/**
 * Runs the search program until the user runs the exit command.
 */
void run() {
    printHelpMessage();
    printf("\n");

    char topCommand[4];

    while (1) {
        gets(topCommand);

        if (topCommand[0] == 'p') {
            printf("-----------(All Job Listings)-----------\n");
            printJobs(jal);
            printf("-----------(All Job Listings)-----------\n");
        }
        else if (topCommand[0] == 'x') {
            printf("Exited the Job Searcher!\n");
            return;
        }
        else if (topCommand[0] == 's') {
            runSearch();
        }
        else if (topCommand[0] == 'l') {
            runListCommand(topCommand[2]);
        }
        else if (topCommand[0] == 't') {
            exactMatching = !exactMatching;
            printf("Toggled exact matching (now ");
            if (exactMatching) printf("enabled");
            else printf("disabled");
            printf(")\n");
        }
        else {
            printHelpMessage();
        }
    }

}

int main() {
    jal = createJobArrayList();
    loadJobs(jal);

    run();
    freeIndexes();
    deleteJobArrayList(jal);
}