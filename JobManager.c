#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "JobManager.h"

// Industry indexing lists
LinkedList *educationIndustryIndex, *softwareIndustryIndex, *servicesIndustryIndex, *informationIndustryIndex, *technologyIndustryIndex, *healthcareIndustryIndex;

// City indexing lists
LinkedList *newYorkCityIndex, *eastonCityIndex, *bostonCityIndex, *seattleCityIndex, *philadelphiaCityIndex;

// Job Title indexing lists
LinkedList *engineerJobTitleIndex, *softwareJobTitleIndex, *developerJobTitleIndex, *analystJobTitleIndex, *seniorJobTitleIndex, *dataJobTitleIndex;

/**
 * Creates indexes for industry, city, and job title.
 * @param jm
 */
void loadJobIndexes(BinaryTree *bt) {
    educationIndustryIndex = createLinkedList();
    softwareIndustryIndex = createLinkedList();
    servicesIndustryIndex = createLinkedList();
    informationIndustryIndex = createLinkedList();
    technologyIndustryIndex = createLinkedList();
    healthcareIndustryIndex = createLinkedList();

    newYorkCityIndex = createLinkedList();
    eastonCityIndex = createLinkedList();
    bostonCityIndex = createLinkedList();
    seattleCityIndex = createLinkedList();
    philadelphiaCityIndex = createLinkedList();

    engineerJobTitleIndex = createLinkedList();
    softwareJobTitleIndex = createLinkedList();
    developerJobTitleIndex = createLinkedList();
    analystJobTitleIndex = createLinkedList();
    seniorJobTitleIndex = createLinkedList();
    dataJobTitleIndex = createLinkedList();

    JobArrayList* jal = getSortedListFromTree(bt);

    for (int i = 0; i < jal->length; i++) {
        Job *j = getJAL(jal, i);
        if (stristr(j->industry, "education") != NULL) insertLinkedList(educationIndustryIndex,j);
        if (stristr(j->industry, "software") != NULL) insertLinkedList(softwareIndustryIndex,j);
        if (stristr(j->industry, "services") != NULL) insertLinkedList(servicesIndustryIndex,j);
        if (stristr(j->industry, "information") != NULL) insertLinkedList(informationIndustryIndex,j);
        if (stristr(j->industry, "technology") != NULL) insertLinkedList(technologyIndustryIndex,j);
        if (stristr(j->industry, "healthcare") != NULL) insertLinkedList(healthcareIndustryIndex,j);

        if (stristr(j->city, "new york") != NULL) insertLinkedList(newYorkCityIndex,j);
        if (stristr(j->city, "easton") != NULL) insertLinkedList(eastonCityIndex,j);
        if (stristr(j->city, "boston") != NULL) insertLinkedList(bostonCityIndex,j);
        if (stristr(j->city, "seattle") != NULL) insertLinkedList(seattleCityIndex,j);
        if (stristr(j->city, "philadelphia") != NULL) insertLinkedList(philadelphiaCityIndex,j);

        if (stristr(j->jobTitle, "engineer") != NULL) insertLinkedList(engineerJobTitleIndex,j);
        if (stristr(j->jobTitle, "software") != NULL) insertLinkedList(softwareJobTitleIndex,j);
        if (stristr(j->jobTitle, "developer") != NULL) insertLinkedList(developerJobTitleIndex,j);
        if (stristr(j->jobTitle, "analyst") != NULL) insertLinkedList(analystJobTitleIndex,j);
        if (stristr(j->jobTitle, "senior") != NULL) insertLinkedList(seniorJobTitleIndex,j);
        if (stristr(j->jobTitle, "data") != NULL) insertLinkedList(dataJobTitleIndex,j);
    }
    deleteJobArrayListShallow(jal);
}

void freeIndexes() {
    deleteLinkedList(educationIndustryIndex);
    deleteLinkedList(softwareIndustryIndex);
    deleteLinkedList(servicesIndustryIndex);
    deleteLinkedList(informationIndustryIndex);
    deleteLinkedList(technologyIndustryIndex);
    deleteLinkedList(healthcareIndustryIndex);

    deleteLinkedList(newYorkCityIndex);
    deleteLinkedList(eastonCityIndex);
    deleteLinkedList(bostonCityIndex);
    deleteLinkedList(seattleCityIndex);
    deleteLinkedList(philadelphiaCityIndex);

    deleteLinkedList(engineerJobTitleIndex);
    deleteLinkedList(softwareJobTitleIndex);
    deleteLinkedList(developerJobTitleIndex);
    deleteLinkedList(analystJobTitleIndex);
    deleteLinkedList(seniorJobTitleIndex);
    deleteLinkedList(dataJobTitleIndex);
}

/**
 * Removes the '\n' character from the end of a string if present
 * @param str The string to edit
 * @return The string without a trailing '\n'
 */
char* removeEnterChar(char* str) {
    if (str[strlen(str)-1] == '\n') {
        str[strlen(str)-1] = '\0';
    }
    return str;
}

/**
 * Copies all jobs to a LinkedList, keeping their order intact.
 */
LinkedList* getJobLinkedList(BinaryTree *bt) {
    LinkedList *ll = createLinkedList();

    JobArrayList* jal = getSortedListFromTree(bt);
    for (int i = 0; i < jal->length; i++) {
        insertLinkedList(ll, getJAL(jal, i));
    }

    deleteJobArrayListShallow(jal);
    return ll;
}

/**
 * Loads all jobs from the text file jobs.txt.
 * After loading the file, it loads all jobs in the file until the end of the file is reached.
 * After loading all jobs, the jobs are sorted.
 */
void loadJobs(BinaryTree *bt) {
    FILE *f = fopen("jobs.txt", "r");
    char* input = malloc(sizeof(char) * 256);

    while (fgets(input, sizeof(char) * 256, f)) {
        Job *j = createJob();

        j->jobTitle = removeEnterChar(input);

        input = malloc(sizeof(char) * 256);
        fgets(input, sizeof(char) * 256, f);
        j->companyName = removeEnterChar(input);

        input = malloc(sizeof(char) * 256);
        fgets(input, sizeof(char) * 256, f);
        j->city = removeEnterChar(input);

        input = malloc(sizeof(char) * 256);
        fgets(input, sizeof(char) * 256, f);
        j->state = removeEnterChar(input);

        input = malloc(sizeof(char) * 256);
        fgets(input, sizeof(char) * 256, f);
        StringArrayList *arr = getSpaceSeparatedArrayList(input);
        int a = 0;
        int b = 1000000000;
        if (getSAL(arr, 0) != NULL) {
            a = (int) strtol(getSAL(arr, 0), NULL, 0);
        }
        if (getSAL(arr, 1) != NULL) {
            b = (int) strtol(getSAL(arr, 1), NULL, 0);
        }
        j->minSalary = a;
        j->maxSalary = b;
        deleteStringArrayListDeep(arr);

        input = malloc(sizeof(char) * 256);
        fgets(input, sizeof(char) * 256, f);
        j->industry = removeEnterChar(input);

        input = malloc(sizeof(char) * 256);
        j->requiredSkills = getCommaSeparatedArrayList(fgets(input, sizeof(char) * 256, f));

        input = malloc(sizeof(char) * 256);
        j->desiredSkills = getCommaSeparatedArrayList(fgets(input, sizeof(char) * 256, f));

        input = malloc(sizeof(char) * 256);
        fgets(input, sizeof(char) * 256, f);
        j->email = removeEnterChar(input);

        insertInBinaryTree(bt, j);

        input = malloc(sizeof(char) * 256);
        fgets(input, sizeof(char) * 2, f); // blank lines between job listings
    }

    free(input);
    fclose(f);

    loadJobIndexes(bt);
}

// Finds indexing lists to add to then places the new job in order
void addNewJob(BinaryTree* bt, Job* j) {
    insertInBinaryTree(bt, j);

    if (stristr(j->industry, "education") != NULL) insertInOrderLinkedList(educationIndustryIndex,j);
    if (stristr(j->industry, "software") != NULL) insertInOrderLinkedList(softwareIndustryIndex,j);
    if (stristr(j->industry, "services") != NULL) insertInOrderLinkedList(servicesIndustryIndex,j);
    if (stristr(j->industry, "information") != NULL) insertInOrderLinkedList(informationIndustryIndex,j);
    if (stristr(j->industry, "technology") != NULL) insertInOrderLinkedList(technologyIndustryIndex,j);
    if (stristr(j->industry, "healthcare") != NULL) insertInOrderLinkedList(healthcareIndustryIndex,j);

    if (stristr(j->city, "new york") != NULL) insertInOrderLinkedList(newYorkCityIndex,j);
    if (stristr(j->city, "easton") != NULL) insertInOrderLinkedList(eastonCityIndex,j);
    if (stristr(j->city, "boston") != NULL) insertInOrderLinkedList(bostonCityIndex,j);
    if (stristr(j->city, "seattle") != NULL) insertInOrderLinkedList(seattleCityIndex,j);
    if (stristr(j->city, "philadelphia") != NULL) insertInOrderLinkedList(philadelphiaCityIndex,j);

    if (stristr(j->jobTitle, "engineer") != NULL) insertInOrderLinkedList(engineerJobTitleIndex,j);
    if (stristr(j->jobTitle, "software") != NULL) insertInOrderLinkedList(softwareJobTitleIndex,j);
    if (stristr(j->jobTitle, "developer") != NULL) insertInOrderLinkedList(developerJobTitleIndex,j);
    if (stristr(j->jobTitle, "analyst") != NULL) insertInOrderLinkedList(analystJobTitleIndex,j);
    if (stristr(j->jobTitle, "senior") != NULL) insertInOrderLinkedList(seniorJobTitleIndex,j);
    if (stristr(j->jobTitle, "data") != NULL) insertInOrderLinkedList(dataJobTitleIndex,j);
}

// Finds indexing lists to modify then handles modification
void modifyJob(BinaryTree* bt, Job* j) {
    modifyElementBinaryTree(bt, j);

    if (stristr(j->industry, "education") != NULL) modifyElementLinkedList(educationIndustryIndex,j);
    if (stristr(j->industry, "software") != NULL) modifyElementLinkedList(softwareIndustryIndex,j);
    if (stristr(j->industry, "services") != NULL) modifyElementLinkedList(servicesIndustryIndex,j);
    if (stristr(j->industry, "information") != NULL) modifyElementLinkedList(informationIndustryIndex,j);
    if (stristr(j->industry, "technology") != NULL) modifyElementLinkedList(technologyIndustryIndex,j);
    if (stristr(j->industry, "healthcare") != NULL) modifyElementLinkedList(healthcareIndustryIndex,j);

    if (stristr(j->city, "new york") != NULL) modifyElementLinkedList(newYorkCityIndex,j);
    if (stristr(j->city, "easton") != NULL) modifyElementLinkedList(eastonCityIndex,j);
    if (stristr(j->city, "boston") != NULL) modifyElementLinkedList(bostonCityIndex,j);
    if (stristr(j->city, "seattle") != NULL) modifyElementLinkedList(seattleCityIndex,j);
    if (stristr(j->city, "philadelphia") != NULL) modifyElementLinkedList(philadelphiaCityIndex,j);

    if (stristr(j->jobTitle, "engineer") != NULL) modifyElementLinkedList(engineerJobTitleIndex,j);
    if (stristr(j->jobTitle, "software") != NULL) modifyElementLinkedList(softwareJobTitleIndex,j);
    if (stristr(j->jobTitle, "developer") != NULL) modifyElementLinkedList(developerJobTitleIndex,j);
    if (stristr(j->jobTitle, "analyst") != NULL) modifyElementLinkedList(analystJobTitleIndex,j);
    if (stristr(j->jobTitle, "senior") != NULL) modifyElementLinkedList(seniorJobTitleIndex,j);
    if (stristr(j->jobTitle, "data") != NULL) modifyElementLinkedList(dataJobTitleIndex,j);
}

// Only need to remove the job because order will be preserved
void removeJob(BinaryTree* bt, Job* j) {
    removeBinaryTree(bt, j);

    if (stristr(j->industry, "education") != NULL) removeDataFromLinkedList(educationIndustryIndex,j);
    if (stristr(j->industry, "software") != NULL) removeDataFromLinkedList(softwareIndustryIndex,j);
    if (stristr(j->industry, "services") != NULL) removeDataFromLinkedList(servicesIndustryIndex,j);
    if (stristr(j->industry, "information") != NULL) removeDataFromLinkedList(informationIndustryIndex,j);
    if (stristr(j->industry, "technology") != NULL) removeDataFromLinkedList(technologyIndustryIndex,j);
    if (stristr(j->industry, "healthcare") != NULL) removeDataFromLinkedList(healthcareIndustryIndex,j);

    if (stristr(j->city, "new york") != NULL) removeDataFromLinkedList(newYorkCityIndex,j);
    if (stristr(j->city, "easton") != NULL) removeDataFromLinkedList(eastonCityIndex,j);
    if (stristr(j->city, "boston") != NULL) removeDataFromLinkedList(bostonCityIndex,j);
    if (stristr(j->city, "seattle") != NULL) removeDataFromLinkedList(seattleCityIndex,j);
    if (stristr(j->city, "philadelphia") != NULL) removeDataFromLinkedList(philadelphiaCityIndex,j);

    if (stristr(j->jobTitle, "engineer") != NULL) removeDataFromLinkedList(engineerJobTitleIndex,j);
    if (stristr(j->jobTitle, "software") != NULL) removeDataFromLinkedList(softwareJobTitleIndex,j);
    if (stristr(j->jobTitle, "developer") != NULL) removeDataFromLinkedList(developerJobTitleIndex,j);
    if (stristr(j->jobTitle, "analyst") != NULL) removeDataFromLinkedList(analystJobTitleIndex,j);
    if (stristr(j->jobTitle, "senior") != NULL) removeDataFromLinkedList(seniorJobTitleIndex,j);
    if (stristr(j->jobTitle, "data") != NULL) removeDataFromLinkedList(dataJobTitleIndex,j);

    deleteJob(j);
}


/**
 * Creates an StringArrayList based on comma separated values.
 * If no comma exists, the list will contain a single element.
 */
StringArrayList* getCommaSeparatedArrayList(char* str) {
    StringArrayList *arr = createStringArrayList();

    char* savePtr;
    char* token = strtok_r(str, ",", &savePtr);

    // Return ArrayList with single value if strtok return null (no , in string)
    if (token == NULL) {
        removeEnterChar(str);
        insertSAL(arr, str);
        return arr;
    }

    // loop through the string to extract all other tokens
    while(token != NULL) {
        removeEnterChar(token);
        insertSAL(arr, token);
        token = strtok_r(NULL, ",", &savePtr);
    }
    return arr;
}

/**
 * Creates an StringArrayList based on space separated values.
 * If no comma exists, the list will contain a single element.
 */
StringArrayList* getSpaceSeparatedArrayList(char* str) {
    StringArrayList *arr = createStringArrayList();

    char* savePtr;
    char* token = strtok_r(str, " ", &savePtr);

    if (token == NULL) {
        removeEnterChar(str);
        insertSAL(arr, str);
        return arr;
    }

    while(token != NULL) {
        removeEnterChar(token);
        insertSAL(arr, token);
        token = strtok_r(NULL, " ", &savePtr);
    }
    return arr;
}

/**
 * Keeps elements in the LinkedList that match the input.
 * Compares the input against each job's jobTitle.
 * True exact match requires jobTitle to match exactly (not case sensitive), and
 * false requires the string to be present in the jobTitle.
 */
void matchJobTitle(LinkedList *ll, char *str, bool exactMatch) {
    if (ll->head == NULL) return;

    StringArrayList *arr = getCommaSeparatedArrayList(str);

    Node *curr = ll->head;
    while(curr != NULL) {
        if (containsSAL(arr, curr->data->jobTitle, exactMatch)) break;
        else {
            removeFromLinkedList(ll, 0);
            curr = ll->head;
        }
    }
    if (curr == NULL) {
        deleteStringArrayList(arr);
        return;
    }

    while (curr->next != NULL) {
        if (containsSAL(arr, curr->next->data->jobTitle, exactMatch)) {
            curr = curr->next;
        }
        else {
            removeDataFromLinkedList(ll, curr->next->data);
        }
    }

    deleteStringArrayList(arr);
}

/**
 * Keeps elements in the LinkedList that match the input.
 * Compares the input against each job's jobTitle.
 *
 * If the input matches any of the created indexes, then that index will be returned.
 * If exactMatch is true, the indexes will be ignored.
 */
void matchJobTitleIndexed(LinkedList *ll, char *str, bool exactMatch) {
    if (ll->head == NULL) return;

    if (!exactMatch) {
        if (strcasecmp("engineer", str) == 0) {
            cloneLinkedList(ll, engineerJobTitleIndex);
            return;
        }
        else if (strcasecmp("software", str) == 0) {
            cloneLinkedList(ll, softwareJobTitleIndex);
            return;
        }
        else if (strcasecmp("developer", str) == 0) {
            cloneLinkedList(ll, developerJobTitleIndex);
            return;
        }
        else if (strcasecmp("analyst", str) == 0) {
            cloneLinkedList(ll, analystJobTitleIndex);
            return;
        }
        else if (strcasecmp("senior", str) == 0) {
            cloneLinkedList(ll, seniorJobTitleIndex);
            return;
        }
        else if (strcasecmp("data", str) == 0) {
            cloneLinkedList(ll, dataJobTitleIndex);
            return;
        }
    }

    matchJobTitle(ll, str, exactMatch);
}

/**
 * Keeps elements in the LinkedList that match the input.
 * Compares the input against each job's companyName.
 * True exact match requires companyName to match exactly (not case sensitive), and
 * false requires the string to be present in the companyName.
 */
void matchCompanyName(LinkedList *ll, char *str, bool exactMatch) {
    if (ll->head == NULL) return;

    StringArrayList *arr = getCommaSeparatedArrayList(str);

    Node *curr = ll->head;
    while(curr != NULL) {
        if (containsSAL(arr, curr->data->companyName, exactMatch)) break;
        else {
            removeFromLinkedList(ll, 0);
            curr = ll->head;
        }
    }
    if (curr == NULL) {
        deleteStringArrayList(arr);
        return;
    }

    while (curr->next != NULL) {
        if (containsSAL(arr, curr->next->data->companyName, exactMatch)) {
            curr = curr->next;
        }
        else {
            removeDataFromLinkedList(ll, curr->next->data);
        }
    }

    deleteStringArrayList(arr);
}

/**
 * Keeps elements in the LinkedList that match the input.
 * Compares the input against each job's city.
 * True exact match requires city to match exactly (not case sensitive), and
 * false requires the string to be present in the city.
 */
void matchCity(LinkedList *ll, char *str, bool exactMatch) {
    if (ll->head == NULL) return;

    StringArrayList *arr = getCommaSeparatedArrayList(str);

    Node *curr = ll->head;
    while(curr != NULL) {
        if (containsSAL(arr, curr->data->city, exactMatch)) break;
        else {
            removeFromLinkedList(ll, 0);
            curr = ll->head;
        }
    }
    if (curr == NULL) {
        deleteStringArrayList(arr);
        return;
    }

    while (curr->next != NULL) {
        if (containsSAL(arr, curr->next->data->city, exactMatch)) {
            curr = curr->next;
        }
        else {
            removeDataFromLinkedList(ll, curr->next->data);
        }
    }

    deleteStringArrayList(arr);
}

/**
 * Keeps elements in the LinkedList that match the input.
 * Compares the input against each job's city.
 *
 * If the input matches any of the created indexes, then that index will be returned.
 * If exactMatch is true, the indexes will be ignored.
 */
void matchCityIndexed(LinkedList *ll, char *str, bool exactMatch) {
    if (ll->head == NULL) return;

    if (!exactMatch) {
        if (strcasecmp("new york", str) == 0) {
            cloneLinkedList(ll, newYorkCityIndex);
            return;
        }
        else if (strcasecmp("easton", str) == 0) {
            cloneLinkedList(ll, eastonCityIndex);
            return;
        }
        else if (strcasecmp("boston", str) == 0) {
            cloneLinkedList(ll, bostonCityIndex);
            return;
        }
        else if (strcasecmp("seattle", str) == 0) {
            cloneLinkedList(ll, seattleCityIndex);
            return;
        }
        else if (strcasecmp("philadelphia", str) == 0) {
            cloneLinkedList(ll, philadelphiaCityIndex);
            return;
        }
    }

    matchCity(ll, str, exactMatch);
}

/**
 * Keeps elements in the LinkedList that match the input.
 * Compares the input against each job's state.
 * Exact matches are required for the state (not case sensitive)
 */
void matchState(LinkedList *ll, char *str) {
    if (ll->head == NULL) return;

    StringArrayList *arr = getCommaSeparatedArrayList(str);

    Node *curr = ll->head;
    while(curr != NULL) {
        if (containsExactSAL(arr, curr->data->state)) break;
        else {
            removeFromLinkedList(ll, 0);
            curr = ll->head;
        }
    }
    if (curr == NULL) {
        deleteStringArrayList(arr);
        return;
    }

    while (curr->next != NULL) {
        if (containsExactSAL(arr, curr->next->data->state)) {
            curr = curr->next;
        }
        else {
            removeDataFromLinkedList(ll, curr->next->data);
        }
    }

    deleteStringArrayList(arr);
}

/**
 * Keeps elements in the LinkedList that match the input.
 * Compares the input against each job's salary range.
 * If a jobs salary is within the min <= x <= max range at all, it is a match
 */
void matchSalary(LinkedList *ll, int min, int max) {
    if (ll->head == NULL) return;

    Node *curr = ll->head;
    while(curr != NULL) {
        if (curr->data->minSalary < max && curr->data->maxSalary > min) break;
        else {
            removeFromLinkedList(ll, 0);
            curr = ll->head;
        }
    }
    if (curr == NULL) return;

    while (curr->next != NULL) {
        if (curr->next->data->minSalary < max && curr->next->data->maxSalary > min) {
            curr = curr->next;
        }
        else {
            removeDataFromLinkedList(ll, curr->next->data);
        }
    }
}

/**
 * Keeps elements in the LinkedList that match the input.
 * Compares the input against each job's industry.
 * True exact match requires industry to match exactly (not case sensitive), and
 * false requires the string to be present in the industry.
 */
void matchIndustry(LinkedList *ll, char *str, bool exactMatch) {
    if (ll->head == NULL) return;

    StringArrayList *arr = getCommaSeparatedArrayList(str);

    Node *curr = ll->head;
    while(curr != NULL) {
        if (containsSAL(arr, curr->data->industry, exactMatch)) break;
        else {
            removeFromLinkedList(ll, 0);
            curr = ll->head;
        }
    }
    if (curr == NULL) {
        deleteStringArrayList(arr);
        return;
    }

    while (curr->next != NULL) {
        if (containsSAL(arr, curr->next->data->industry, exactMatch)) {
            curr = curr->next;
        }
        else {
            removeDataFromLinkedList(ll, curr->next->data);
        }
    }

    deleteStringArrayList(arr);
}

/**
 * Keeps elements in the LinkedList that match the input.
 * Compares the input against each job's industry.
 *
 * If the input matches any of the created indexes, then that index will be returned.
 * If exactMatch is true, the indexes will be ignored.
 */
void matchIndustryIndexed(LinkedList *ll, char *str, bool exactMatch) {
    if (ll->head == NULL) return;

    if (!exactMatch) {
        if (strcasecmp("education", str) == 0) {
            cloneLinkedList(ll, educationIndustryIndex);
            return;
        }
        else if (strcasecmp("software", str) == 0) {
            cloneLinkedList(ll, softwareIndustryIndex);
            return;
        }
        else if (strcasecmp("services", str) == 0) {
            cloneLinkedList(ll, servicesIndustryIndex);
            return;
        }
        else if (strcasecmp("information", str) == 0) {
            cloneLinkedList(ll, informationIndustryIndex);
            return;
        }
        else if (strcasecmp("technology", str) == 0) {
            cloneLinkedList(ll, technologyIndustryIndex);
            return;
        }
        else if (strcasecmp("healthcare", str) == 0) {
            cloneLinkedList(ll, healthcareIndustryIndex);
            return;
        }
    }

    matchIndustry(ll, str, exactMatch);
}

/**
 * Keeps elements in the LinkedList that match the input.
 * Compares the input against each job's required skills.
 * True exact match requires one skill to match the input exactly (not case sensitive), and
 * false requires the string to be present in one of the required skills.
 */
void matchRequiredSkills(LinkedList *ll, char *str, bool exactMatch) {
    if (ll->head == NULL) return;

    StringArrayList *arr = getCommaSeparatedArrayList(str);

    Node *curr = ll->head;
    while(curr != NULL) {
        if (containsListMatchSAL(curr->data->requiredSkills, arr, exactMatch)) break;
        else {
            removeFromLinkedList(ll, 0);
            curr = ll->head;
        }
    }
    if (curr == NULL) {
        deleteStringArrayList(arr);
        return;
    }

    while (curr->next != NULL) {
        if (containsListMatchSAL(curr->next->data->requiredSkills, arr, exactMatch)) {
            curr = curr->next;
        }
        else {
            removeDataFromLinkedList(ll, curr->next->data);
        }
    }

    deleteStringArrayList(arr);
}

/**
 * Keeps elements in the LinkedList that match the input.
 * Compares the input against each job's desired skills.
 * True exact match requires one skill to match the input exactly (not case sensitive), and
 * false requires the string to be present in one of the desired skills.
 */
void matchDesiredSkills(LinkedList *ll, char *str, bool exactMatch) {
    if (ll->head == NULL) return;

    StringArrayList *arr = getCommaSeparatedArrayList(str);

    Node *curr = ll->head;
    while(curr != NULL) {
        if (containsListMatchSAL(curr->data->desiredSkills, arr, exactMatch)) break;
        else {
            removeFromLinkedList(ll, 0);
            curr = ll->head;
        }
    }
    if (curr == NULL) {
        deleteStringArrayList(arr);
        return;
    }

    while (curr->next != NULL) {
        if (containsListMatchSAL(curr->next->data->desiredSkills, arr, exactMatch)) {
            curr = curr->next;
        }
        else {
            removeDataFromLinkedList(ll, curr->next->data);
        }
    }

    deleteStringArrayList(arr);
}

/**
 * Prints all jobs to the screen with a blank line between each job.
 */
void printJobs(BinaryTree *bt) {
    JobArrayList* arr = getSortedListFromTree(bt);

    if (arr->length > 0) {
        for (int i = 0; i < arr->length - 1; i++) {
            printJob(getJAL(arr, i));
            printf("\n");
        }
        printJob(getJAL(arr, arr->length - 1));
    }
    else {
        printf("Database empty\n");
    }

    deleteJobArrayListShallow(arr);
}

void outputJobs(BinaryTree *bt, FILE* fp) {
    JobArrayList* jal = getSortedListFromTree(bt);
    Job *j;
    for (int i = 0; i < jal->length; i++) {
        j = getJAL(jal, i);

        fprintf(fp, "%s\n", j->jobTitle);
        fprintf(fp, "%s\n", j->companyName);
        fprintf(fp, "%s\n", j->city);
        fprintf(fp, "%s\n", j->state);
        fprintf(fp, "%d %d\n", j->minSalary, j->maxSalary);
        fprintf(fp, "%s\n", j->industry);
        printSALToFile(j->requiredSkills, fp);
        printSALToFile(j->desiredSkills, fp);
        fprintf(fp, "%s\n\n", j->email);
    }
    deleteJobArrayListShallow(jal);
}

/**
 * Does the same as <string.h> strstr() function, but ignores case.
 * Written by Clifford (https://stackoverflow.com/questions/27303062/strstr-function-like-that-ignores-upper-or-lower-case)
 */
char* stristr(const char* haystack, const char* needle) {
    const char* p1 = haystack;
    const char* p2 = needle;
    const char* r = *p2 == 0 ? haystack : 0;

    while (*p1 != 0 && *p2 != 0) {
        if (tolower((unsigned char)*p1) == tolower((unsigned char)*p2)) {
            if(r == 0) {
                r = p1;
            }
            p2++;
        }
        else {
            p2 = needle;
            if (r != 0) {
                p1 = r + 1;
            }

            if (tolower((unsigned char)*p1) == tolower((unsigned char)*p2)) {
                r = p1;
                p2++;
            }
            else {
                r = 0;
            }
        }
        p1++;
    }

    return *p2 == 0 ? (char*)r : 0;
}