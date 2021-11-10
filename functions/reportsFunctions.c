#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../main.h"

enum StatusOfReport {NEW = 1, FIXED, CLOSED};

typedef struct // WE DEFINE TYPE OF TYPE STRUCTURE
{
    unsigned long long int uniqueID;          //     1. UNIQUE ID NUMBER
    char *sShortDesc;        //     2. SHORT DESCRIPTION
    char *sDesc;     //     3. DESCRIPTION
    time_t *sDateOfCreation;   //     4. DATE OF CREATION(current date)
    time_t *sDateOfFixed;      //     5. DATE OF FIXED = 0 HERE
    time_t *sDateOfClosed;     //     6. DATE OF CLOSED = 0 HERE
    char *lastWriteInReport; //     7. LAST WRITER IN REPORT : TESTER OR PROGRAMMER
    enum StatusOfReport statusOfReport;    //     8. STATUS : NEW | FIXED | CLOSED

} bugReport; // AND GIVE NAME HIM BUG REPORT

bugReport newReport;

void createNewReport()
{
    createFileIfNotExist(DATABASE_FILE);

    clearScreen();
    printCover('T');
    printNewLines(1);
    newReport.sShortDesc = calloc(SHORT_DESC_LENGTH, sizeof(char));
    printf(" --- Enter text for short description. REPORT ID#%d ", countFileRows(DATABASE_FILE) + 1);
    getSentence(newReport.sShortDesc, 4, SHORT_DESC_LENGTH);
    printNewLines(1);
    if (strlen(newReport.sShortDesc) < 4 || strlen(newReport.sShortDesc) > SHORT_DESC_LENGTH)
    {
        printf(" --- Log in as tester and try again! ---");
        return;
    }
    newReport.sDesc = calloc(DESC_LENGTH, sizeof(char));
    printNewLines(1);
    printf(" --- Enter text for description. --- ");
    getSentence(newReport.sDesc, 10, DESC_LENGTH);
    printNewLines(1);
    if (strlen(newReport.sDesc) < 10 || strlen(newReport.sDesc) > DESC_LENGTH)
    {
        printf(" --- Log in as tester and try again! ---");
        return;
    }

    newReport.uniqueID = (char *)malloc(IDS_LENGTH);
    // newReport.sShortDesc = (char *)malloc(SHORT_DESC_LENGTH); WE ARE ALREADY CREATE IT
    // newReport.sDesc = (char *)malloc(DESC_LENGTH); WE ARE ALREADY CREATE IT
    newReport.sDateOfCreation = (char *)malloc(DATE_LENGTH);
    newReport.sDateOfFixed = (char *)malloc(DATE_LENGTH);
    newReport.sDateOfClosed = (char *)malloc(DATE_LENGTH);
    newReport.lastWriteInReport = (char *)malloc(WRITER_LENGTH);
    newReport.statusOfReport = (char *)malloc(STATUS_LENGTH);

    char buffer[IDS_LENGTH];
    strcpy(newReport.uniqueID, itoa(countFileRows(DATABASE_FILE) + 1, buffer, 10));

    getCurrentTime(newReport.sDateOfCreation); // save current time in newReport.sDateOfCreation
    strcpy(newReport.sDateOfFixed, "Not fixed");
    strcpy(newReport.sDateOfClosed, "Not Closed");
    strcpy(newReport.lastWriteInReport, "Tester");
    strcpy(newReport.statusOfReport, "NEW");

    char *arrayPutInFile = (char *)malloc(MAX_RECORD_LEN);
    fp = fopen(DATABASE_FILE, "a+");
    sprintf(arrayPutInFile, "#%s,%s,%s,%s,%s,%s,%s,%s", newReport.uniqueID, newReport.sShortDesc, newReport.sDesc, newReport.sDateOfCreation, newReport.sDateOfFixed, newReport.sDateOfClosed, newReport.lastWriteInReport, newReport.statusOfReport);
    fprintf(fp, "%s\n", arrayPutInFile);
    fclose(fp);

    free(newReport.uniqueID);
    free(newReport.sShortDesc);
    free(newReport.sDesc);
    free(newReport.sDateOfCreation);
    free(newReport.sDateOfFixed);
    free(newReport.sDateOfClosed);
    free(newReport.lastWriteInReport);
    free(newReport.statusOfReport);
    free(arrayPutInFile);
}

int isReportNew(char *status)
{
    char NEW[] = "NEW\n";
    if (strcmp(status, NEW) == 0)
    {
        return 1;
    }

    return 0;
}

int isReportFixed(char *status)
{
    char FIXED[] = "FIXED\n";
    if (strcmp(status, FIXED) == 0)
    {
        return 1;
    }
    return 0;
}

void editSpecificNewReport()
{
    createFileIfNotExist(DATABASE_FILE);

    char getID[20] = {0};

    printf(" -- Enter id TO FIX #: ");
    getStrFromAdress(getID);

    int id = atoi(getID);

    if (!isRowExist(id, DATABASE_FILE))
    {
        printf(" -- Wrong ID -- ");
        return;
    }

    char currentRowRecord[MAX_RECORD_LEN];
    getRowByIDIfExist(id, DATABASE_FILE, currentRowRecord);
    char currentRowCopy[MAX_RECORD_LEN];
    strcpy(currentRowCopy, currentRowRecord);

    strcat(currentRowRecord, ",");

    int structCount = sizeof(bugReport) / sizeof(char *); // We get bytes of bugReport structure and divison by char *, because we have only char* in

    char **explodeCurrentRecord = (char **)calloc(structCount, sizeof(char *));

    int lengthCurrentRow = strlen(currentRowRecord);

    char buffer[DESC_LENGTH];

    int countStrings = 0;
    int countChars = 0;

    for (int i = 0; i < lengthCurrentRow; i++)
    {
        if (currentRowRecord[i] != ',')
        {
            buffer[countChars++] = currentRowRecord[i];
        }
        else if (currentRowRecord[i] == ',')
        {
            buffer[countChars] = '\0';
            countChars = 0;
            explodeCurrentRecord[countStrings] = (char *)calloc((strlen(buffer) + 1), sizeof(char));
            strcpy(explodeCurrentRecord[countStrings], buffer);
            memset(buffer, '\0', strlen(buffer));
            countStrings++;
        }
    }

    newReport.statusOfReport = explodeCurrentRecord[7];

    printf(" --- %s ", currentRowCopy);

    if (!isReportNew(newReport.statusOfReport))
    {
        printf(" --- Record is not \"NEW\". You can\'t change it. --- ");
        free2DArrFromMemory(explodeCurrentRecord, structCount);
        return;
    }

    printf(" --- ID #%d is NEW. --- ", id);
    printNewLines(1);
    printf(" -- Do you want to change Report #%d to FIXED? [y/n]: ", id);

    if (!isContinue())
    {
        printf(" --- The BUG REPORT is not FIXED! --- ");
        free2DArrFromMemory(explodeCurrentRecord, structCount);
        makePause();
        return;
    }

    char currDate[DATE_LENGTH];
    getCurrentTime(currDate);
    strcpy(explodeCurrentRecord[4], currDate);
    strcpy(explodeCurrentRecord[6], "PROGRAMMER"); // 7 newReport.lastWriteInReport
    strcpy(explodeCurrentRecord[7], "FIXED");      // 8 newReport.statusOfReport
    char newRow[MAX_RECORD_LEN];
    sprintf(newRow, "%s,%s,%s,%s,%s,%s,%s,%s\n", explodeCurrentRecord[0], explodeCurrentRecord[1], explodeCurrentRecord[2], explodeCurrentRecord[3], explodeCurrentRecord[4], explodeCurrentRecord[5], explodeCurrentRecord[6], explodeCurrentRecord[7]);
    clearScreen();
    printCover('P');
    printNewLines(2);
    if (rewriteFileWithOneRow(REPLACE_FILE, DATABASE_FILE, currentRowCopy, newRow))
    {
        printf(" --- YOU FIX THE REPORT (#BUG) --- ");
        printNewLines(2);
        parsePrintArray(newRow, strlen(newRow));
    }
    else if (!rewriteFileWithOneRow(REPLACE_FILE, DATABASE_FILE, currentRowCopy, newRow))
    {
        printf(" --- Error! ---");
    }

    free2DArrFromMemory(explodeCurrentRecord, structCount);

    return;
}

void verifyFixedReport()
{
    createFileIfNotExist(DATABASE_FILE);

    char getID[20] = {0};

    printf(" -- Enter id TO VERIFY #: ");
    getStrFromAdress(getID);

    int id = atoi(getID);

    if (!isRowExist(id, DATABASE_FILE))
    {
        printf(" -- ID #%d don\'exist! -- ", id);
        return;
    }

    if (!isRowExist(id, DATABASE_FILE))
    {
        printf(" -- Wrong ID -- ");
        return;
    }

    char currentRowRecord[MAX_RECORD_LEN];
    getRowByIDIfExist(id, DATABASE_FILE, currentRowRecord);
    char currentRowCopy[MAX_RECORD_LEN];
    strcpy(currentRowCopy, currentRowRecord);

    strcat(currentRowRecord, ",");

    int structCount = sizeof(bugReport) / sizeof(char *); // We get bytes of bugReport structure and divison by char *, because we have only char* in

    char **explodeCurrentRecord = (char **)calloc(structCount, sizeof(char *));

    int lengthCurrentRow = strlen(currentRowRecord);

    char buffer[DESC_LENGTH];

    int countStrings = 0;
    int countChars = 0;

    for (int i = 0; i < lengthCurrentRow; i++)
    {
        if (currentRowRecord[i] != ',')
        {
            buffer[countChars++] = currentRowRecord[i];
        }
        else if (currentRowRecord[i] == ',')
        {
            buffer[countChars] = '\0';
            countChars = 0;
            explodeCurrentRecord[countStrings] = (char *)calloc((strlen(buffer) + 1), sizeof(char));
            strcpy(explodeCurrentRecord[countStrings], buffer);
            memset(buffer, '\0', strlen(buffer));
            countStrings++;
        }
    }

    newReport.statusOfReport = explodeCurrentRecord[7];

    printf(" --- %s ", currentRowCopy);

    if (!isReportFixed(newReport.statusOfReport))
    {
        printf(" --- Record is not \"Fixed\". You can\'t change it. --- ");
        free2DArrFromMemory(explodeCurrentRecord, structCount);
        return;
    }

    printf(" --- ID #%d is FIXED. --- ", id);
    printNewLines(1);
    printf(" -- Do you want to change Report #%d to CLOSED? [y/n]: ", id);

    if (!isContinue())
    {
        printf(" --- The BUG REPORT is not CLOSED! --- ");
        free2DArrFromMemory(explodeCurrentRecord, structCount);
        return;
    }

    char currDate[DATE_LENGTH];
    getCurrentTime(currDate);
    strcpy(explodeCurrentRecord[5], currDate);
    strcpy(explodeCurrentRecord[6], "TESTER"); // 7 newReport.lastWriteInReport =
    strcpy(explodeCurrentRecord[7], "CLOSED"); // 8 newReport.statusOfReport =
    char newRow[MAX_RECORD_LEN];
    sprintf(newRow, "%s,%s,%s,%s,%s,%s,%s,%s\n", explodeCurrentRecord[0], explodeCurrentRecord[1], explodeCurrentRecord[2], explodeCurrentRecord[3], explodeCurrentRecord[4], explodeCurrentRecord[5], explodeCurrentRecord[6], explodeCurrentRecord[7]);
    clearScreen();
    printCover('T');
    printNewLines(2);
    if (rewriteFileWithOneRow(REPLACE_FILE, DATABASE_FILE, currentRowCopy, newRow))
    {
        printf(" --- YOU VERIFIED THE REPORT (#BUG) --- ");
        printNewLines(2);
        parsePrintArray(newRow, strlen(newRow));
    }
    else if (!rewriteFileWithOneRow(REPLACE_FILE, DATABASE_FILE, currentRowCopy, newRow))
    {
        printf(" --- Error! ---");
    }

    free2DArrFromMemory(explodeCurrentRecord, structCount);

    return;
}

void printReports(char flag)
{
    fp = fopen(DATABASE_FILE, "r");

    char *buffer = malloc(MAX_RECORD_LEN);

    char *fgetsFile = fgets(buffer, MAX_RECORD_LEN, fp);

    int countChars = 0;

    while (fgetsFile != NULL)
    {
        countChars = 0;
        for (int i = strlen(buffer) - 2; buffer[i] != ','; i--) // Str len - \n (2 chars) in that string
        {
            countChars++;
        }
        if (flag == 'a' || flag == 'A')
        {
            parsePrintArray(buffer, strlen(buffer));
        }
        else if (countChars == 3 && (flag == 'n' || flag == 'N'))
        {
            parsePrintArray(buffer, strlen(buffer));
        }
        else if (countChars == 5 && (flag == 'f' || flag == 'F'))
        {
            parsePrintArray(buffer, strlen(buffer));
        }
        else if (countChars == 6 && (flag == 'c' || flag == 'C'))
        {
            parsePrintArray(buffer, strlen(buffer));
        }

        fgetsFile = fgets(buffer, MAX_RECORD_LEN, fp);
    }

    free(buffer);
    fclose(fp);
}
