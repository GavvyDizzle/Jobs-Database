#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "JobManager.h"
#include "bt.h"

BinaryTree* bt;
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

bool isValidYesNoInput(char* input) {
    if (strlen(input) != 1) return false;

    return input[0] == 'y' ||
            input[0] == 'Y' ||
            input[0] == 'n' ||
            input[0] == 'N';
}

/**
 * Handles when the search command is run.
 * Asks the user for input for each of the Job criteria.
 */
void runSearch() {
    printf("Note: Leaving any input blank ignores that field\n");

    char input[256];
    LinkedList *ll = getJobLinkedList(bt);

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

    LinkedList *ll = getJobLinkedList(bt);
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
 * Adds a job to the database given user input
 */
void runAddCommand() {
    char* input = malloc(sizeof(char) * 256);
    Job *job = createJob();

    printf("Enter job title: ");
    gets(input);
    while (strlen(input) == 0) {
        printf("Invalid job title. Enter another: ");
        gets(input);
    }
    job->jobTitle = input;

    printf("Enter company name: ");
    input = malloc(sizeof(char) * 256);
    gets(input);
    while (strlen(input) == 0) {
        printf("Invalid company name. Enter another: ");
        gets(input);
    }
    job->companyName = input;

    printf("Enter contact email: ");
    input = malloc(sizeof(char) * 256);
    gets(input);
    while (strlen(input) == 0) {
        printf("Invalid email. Enter another: ");
        gets(input);
    }
    job->email = input;

    printf("Enter location: ");
    input = malloc(sizeof(char) * 256);
    gets(input);
    while (strlen(input) == 0) {
        printf("Invalid location. Enter another: ");
        gets(input);
    }
    job->city = input;

    printf("Enter state abbreviation: ");
    input = malloc(sizeof(char) * 16);
    gets(input);
    while (strlen(input) != 2) {
        printf("Invalid state abbreviation. Enter another: ");
        gets(input);
    }
    job->state = input;

    // There is no error catching for the salary range. Instead, default values will be put int the case of invalid input(s)
    printf("Enter salary range (x y): ");
    input = malloc(sizeof(char) * 256);
    gets(input);
    StringArrayList *arr = getSpaceSeparatedArrayList(input);
    int a = 0;
    int b = 1000000000;

    if (getSAL(arr, 0) != NULL) {
        a = (int) strtol(getSAL(arr, 0), NULL, 0);
    }
    if (getSAL(arr, 1) != NULL) {
        b = (int) strtol(getSAL(arr, 1), NULL, 0);
    }
    job->minSalary = a;
    job->maxSalary = b;
    deleteStringArrayListDeep(arr);

    printf("Enter industry: ");
    input = malloc(sizeof(char) * 256);
    gets(input);
    while (strlen(input) == 0) {
        printf("Invalid industry. Enter another: ");
        gets(input);
    }
    job->industry = input;

    printf("Enter required skills(s): ");
    input = malloc(sizeof(char) * 256);
    gets(input);
    while (strlen(input) == 0) {
        printf("Invalid required skills. You must list one. Enter again: ");
        gets(input);
    }
    job->requiredSkills = getCommaSeparatedArrayList(input);;

    printf("Enter desired skills(s): ");
    input = malloc(sizeof(char) * 256);
    gets(input);
    while (strlen(input) == 0) {
        printf("Invalid desired skills. You must list one. Enter again: ");
        gets(input);
    }
    job->desiredSkills = getCommaSeparatedArrayList(input);;

    printf("\n----------(Add your job? (y/n) )----------\n");
    printJob(job);
    printf("--------------------------------------------\n");

    gets(input);
    while(!isValidYesNoInput(input)) {
        printf("Invalid response (y/n): ");
        gets(input);
    }

    if (input[0] == 'y' || input[0] == 'Y') {
        printf("Your job has been successfully added to the database\n");
        addNewJob(bt, job);
    }
    else {
        printf("Job not added\n");
        deleteJob(job);
    }
}

/**
 * Modifies a job in the database given user input
 */
void runModifyCommand() {
    printf("Note: Leaving any input blank ignores that field\n");

    char input[256];
    LinkedList *ll = getJobLinkedList(bt);

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

    printf("Enter industry(s): ");
    gets(input);
    if (strlen(input) != 0) {
        matchIndustry(ll, input, exactMatching);
    }

    if (ll->length == 0) {
        printf("----------------------------------------\n");
        printf("Your job search returned no results!\n");
        printf("A job must be found in order to modify it.");
        printf("----------------------------------------\n");
        deleteLinkedList(ll);
        return;
    }
    else if (ll->length != 1) {
        printf("----------------------------------------\n");
        printf("Your job search returned %d results!\n", ll->length);
        printf("Only a single job can be modified at a time.\n");
        printf("----------------------------------------\n");
        deleteLinkedList(ll);
        return;
    }

    // Only one job found
    Job *mod = ll->head->data;

    printf("\n----------(Modify current job? (y/n) )----------\n");
    printJob(mod);
    printf("------------------------------------------------\n");

    gets(input);
    while(!isValidYesNoInput(input)) {
        printf("Invalid response (y/n): ");
        gets(input);
    }

    if (input[0] == 'n' || input[0] == 'N') {
        printf("Modification cancelled\n");
        return;
    }

    // Ask for modifications to make
    Job* copy = createJob();
    copy->jobTitle = mod->jobTitle;
    copy->companyName = mod->companyName;
    copy->industry = mod->industry;
    copy->email = mod->email;

    printf("Leaving a line blank will not modify that field of the job\n");
    char* input2 = malloc(sizeof(char) * 256);

    printf("Enter location: ");
    gets(input2);
    if (strlen(input2) == 0) {
        free(input2);
        copy->city = mod->city;
    }
    else {
        copy->city = input2;
    }

    printf("Enter state abbreviation: ");
    input2 = malloc(sizeof(char) * 16);
    gets(input2);
    while (strlen(input2) != 2 && strlen(input2) != 0) {
        printf("Invalid state abbreviation. Enter another: ");
        gets(input2);
    }
    if (strlen(input2) == 0) {
        free(input2);
        copy->state = mod->state;
    }
    else {
        copy->state = input2;
    }

    // There is no error catching for the salary range. Instead, default values will be put int the case of invalid input(s)
    printf("Enter salary range (x y): ");
    input2 = malloc(sizeof(char) * 256);
    gets(input2);

    if (strlen(input2) == 0) {
        free(input2);
        copy->minSalary = mod->minSalary;
        copy->maxSalary = mod->maxSalary;
    }
    else {
        StringArrayList *arr = getSpaceSeparatedArrayList(input2);
        int a = 0;
        int b = 1000000000;

        if (getSAL(arr, 0) != NULL) {
            a = (int) strtol(getSAL(arr, 0), NULL, 0);
        }
        if (getSAL(arr, 1) != NULL) {
            b = (int) strtol(getSAL(arr, 1), NULL, 0);
        }
        copy->minSalary = a;
        copy->maxSalary = b;
        deleteStringArrayListDeep(arr);
    }

    printf("Enter required skills(s): ");
    input2 = malloc(sizeof(char) * 256);
    gets(input2);
    if (strlen(input2) == 0) {
        copy->requiredSkills = mod->requiredSkills;
        free(input2);
    }
    else {
        copy->requiredSkills = getCommaSeparatedArrayList(input2);
    }

    printf("Enter desired skills(s): ");
    input2 = malloc(sizeof(char) * 256);
    gets(input2);
    if (strlen(input2) == 0) {
        copy->desiredSkills = mod->desiredSkills;
        free(input2);
    }
    else {
        copy->desiredSkills = getCommaSeparatedArrayList(input2);
    }

    printf("\n----------(Modify your job? (y/n) )----------\n");
    printJob(copy);
    printf("--------------------------------------------\n");

    gets(input);
    while(!isValidYesNoInput(input)) {
        printf("Invalid response (y/n): ");
        gets(input);
    }

    if (input[0] == 'y' || input[0] == 'Y') {
        printf("Your job has been successfully modified in the database\n");
        if (mod->city != copy->city) free(mod->city);
        mod->city = copy->city;
        if (mod->state != copy->state) free(mod->state);
        mod->state = copy->state;
        mod->minSalary = copy->minSalary;
        mod->maxSalary = copy->maxSalary;
        if (mod->requiredSkills != copy->requiredSkills) deleteStringArrayListDeep(mod->requiredSkills);
        mod->requiredSkills = copy->requiredSkills;
        if (mod->desiredSkills != copy->desiredSkills) deleteStringArrayListDeep(mod->desiredSkills);
        mod->desiredSkills = copy->desiredSkills;

        modifyJob(bt, mod);
    }
    else {
        printf("Job modification cancelled\n");
        if (mod->city != copy->city) free(copy->city);
        if (mod->state != copy->state) free(copy->state);
        if (mod->requiredSkills != copy->requiredSkills) deleteStringArrayListDeep(copy->requiredSkills);
        if (mod->desiredSkills != copy->desiredSkills) deleteStringArrayListDeep(copy->desiredSkills);
    }

    deleteLinkedList(ll);
    free(copy);
}

/**
 * Removes a job from the database given user input
 */
void runRemoveCommand() {
    printf("Note: Leaving any input blank ignores that field\n");

    char input[256];
    LinkedList *ll = getJobLinkedList(bt);

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

    printf("Enter industry(s): ");
    gets(input);
    if (strlen(input) != 0) {
        matchIndustry(ll, input, exactMatching);
    }

    if (ll->length == 0) {
        printf("----------------------------------------\n");
        printf("Your job search returned no results!\n");
        printf("A job must be found in order to remove it.");
        printf("----------------------------------------\n");
        deleteLinkedList(ll);
        return;
    }
    else if (ll->length != 1) {
        printf("----------------------------------------\n");
        printf("Your job search returned %d results!\n", ll->length);
        printf("Only a single job can be removed at a time.\n");
        printf("----------------------------------------\n");
        deleteLinkedList(ll);
        return;
    }

    // Only one job found
    Job *rem = ll->head->data;

    printf("\n----------(Delete current job? (y/n) )----------\n");
    printJob(rem);
    printf("------------------------------------------------\n");

    gets(input);
    while(!isValidYesNoInput(input)) {
        printf("Invalid response (y/n): ");
        gets(input);
    }

    if (input[0] == 'y' || input[0] == 'Y') {
        printf("Job successfully deleted\n");
        removeJob(bt, rem);
    }
    else {
        printf("Deletion cancelled\n");
    }

    deleteLinkedList(ll);
}

/**
 * Writes the database to the file provided by the user
 */
void runWriteCommand() {
    char input[256];
    printf("Enter output file name: ");

    gets(input);
    while (strlen(input) == 0 || strcasecmp("jobs.txt", input) == 0) {
        printf("Invalid name provided. Enter another: ");
        gets(input);
    }

    FILE *fp = fopen(input, "w+");
    outputJobs(bt, fp);
    fclose(fp);
    printf("All jobs successfully written to %s\n", input);
}

/**
 * Prints the help message.
 * This message is printed when the program starts and when an invalid command is given.
 */
void printHelpMessage() {
    printf("---(Job Search Help)---\n");
    printf("a = add a job\n");
    printf("l (l/i/t) = (location/industry/title) list matching jobs\n");
    printf("m = modify a job\n");
    printf("p = print out all jobs\n");
    printf("r = remove a job\n");
    printf("s = enter job search\n");
    printf("t = toggle exact matching (currently ");
    if (exactMatching) printf("enabled");
    else printf("disabled");
    printf(")\n");
    printf("w = export jobs to file\n");
    printf("x = exit program\n");
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

        if (topCommand[0] == 'a') {
            runAddCommand();
        }
        else if (topCommand[0] == 'l') {
            runListCommand(topCommand[2]);
        }
        else if (topCommand[0] == 'm') {
            runModifyCommand();
        }
        else if (topCommand[0] == 'p') {
            printf("-----------(All Job Listings)-----------\n");
            printJobs(bt);
            printf("-----------(All Job Listings)-----------\n");
        }
        else if (topCommand[0] == 'r') {
            runRemoveCommand();
        }
        else if (topCommand[0] == 's') {
            runSearch();
        }
        else if (topCommand[0] == 't') {
            exactMatching = !exactMatching;
            printf("Toggled exact matching (now ");
            if (exactMatching) printf("enabled");
            else printf("disabled");
            printf(")\n");
        }
        else if (topCommand[0] == 'w') {
            runWriteCommand();
        }
        else if (topCommand[0] == 'x') {
            printf("Exited the Job Searcher!\n");
            return;
        }
        else {
            printHelpMessage();
        }
    }

}

int main() {
    bt = createBinaryTree();
    loadJobs(bt);

    run();
    freeIndexes();
    deleteBinaryTree(bt);
}