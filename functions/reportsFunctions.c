#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../main.h"

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

    newReport.lastWriteInReport = (char *)malloc(WRITER_LENGTH);
    strcpy(newReport.lastWriteInReport, "TESTER");

    newReport.uniqueID = countFileRows(DATABASE_FILE) + 1;
    newReport.sDateOfCreation = time(NULL);
    newReport.sDateOfFixed = 0;
    newReport.sDateOfClosed = 0;
    newReport.statusOfReport = NEW;

    char *arrayPutInFile = (char *)malloc(MAX_RECORD_LEN);
    fp = fopen(DATABASE_FILE, "a+");
    sprintf(arrayPutInFile, "%d,%s,%s,%d,%d,%d,%s,%d", newReport.uniqueID, newReport.sShortDesc, newReport.sDesc, newReport.sDateOfCreation, newReport.sDateOfFixed, newReport.sDateOfClosed, newReport.lastWriteInReport, newReport.statusOfReport);
    fprintf(fp, "%s\n", arrayPutInFile);
    fclose(fp);

    freeStrings(&newReport);
    free(arrayPutInFile);
}

int isReportNew(int statusOfReport)
{
    if (statusOfReport == NEW)
    {
        return 1;
    }

    return 0;
}

int isReportFixed(int statusOfReport)
{
    if (statusOfReport == FIXED)
    {
        return 1;
    }
    return 0;
}

void getExistingReport(int id, char *buffer)
{
    char currentRowRecord[MAX_RECORD_LEN];

    strcpy(currentRowRecord, buffer);

    strcat(currentRowRecord, ",");

    // char **explodeCurrentRecord = (char **)calloc(STRUCT_COUNT, sizeof(char));

    char explodeCurrentRecord[STRUCT_COUNT][DESC_LENGTH];

    int lengthCurrentRow = strlen(currentRowRecord);

    char bufferTwo[DESC_LENGTH];

    int countStrings = 0;
    int countChars = 0;

    for (int i = 0; i < lengthCurrentRow; i++)
    {
        if (currentRowRecord[i] != ',')
        {
            bufferTwo[countChars++] = currentRowRecord[i];
        }
        else if (currentRowRecord[i] == ',')
        {
            bufferTwo[countChars] = '\0';
            countChars = 0;
            // explodeCurrentRecord[countStrings] = (char *)calloc((strlen(bufferTwo) + 1), sizeof(char));
            strcpy(explodeCurrentRecord[countStrings], bufferTwo);
            memset(bufferTwo, '\0', strlen(bufferTwo));
            countStrings++;
        }
    }

    newReport.sShortDesc = (char *)malloc(SHORT_DESC_LENGTH);
    newReport.sDesc = (char *)malloc(DESC_LENGTH);
    newReport.lastWriteInReport = (char *)malloc(WRITER_LENGTH);

    newReport.uniqueID = id;
    strcpy(newReport.sShortDesc, explodeCurrentRecord[SHORT_DESC_POS]);
    strcpy(newReport.sDesc, explodeCurrentRecord[DESC_POS]);
    newReport.sDateOfCreation = atoi(explodeCurrentRecord[DATE_CREATION_POS]);
    newReport.sDateOfFixed = atoi(explodeCurrentRecord[DATE_FIXED_POS]);
    newReport.sDateOfClosed = atoi(explodeCurrentRecord[DATE_CLOSED_POS]);
    strcpy(newReport.lastWriteInReport, explodeCurrentRecord[LAST_WRITER_POS]);
    newReport.statusOfReport = atoi(explodeCurrentRecord[STATUS_REPORT_POS]);

    // free2DArrFromMemory(explodeCurrentRecord, MAX_RECORD_LEN);
}

void fixReport()
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

    char currentRowCopy[MAX_RECORD_LEN] = {0};
    char currentRow[MAX_RECORD_LEN] = {0};
    getRowByIDIfExist(id, DATABASE_FILE, currentRowCopy);
    getRowByIDIfExist(id, DATABASE_FILE, currentRow);
    getExistingReport(id, currentRow);

    if (isReportNew(newReport.statusOfReport) != 1)
    {
        printf(" --- Record is not \"NEW\". You can\'t change it. --- ");
        freeStrings(&newReport);
        return;
    }
    printf(" --- ID #%d is NEW. --- ", id);
    printNewLines(1);
    printf(" -- Do you want to change Report #%d to FIXED? [y/n]: ", id);

    if (!isContinue())
    {
        printf(" --- The BUG REPORT is not FIXED! --- ");
        freeStrings(&newReport);
        makePause();
        return;
    }

    newReport.sDateOfFixed = time(NULL);
    newReport.statusOfReport = FIXED;
    strcpy(newReport.lastWriteInReport, "PROGRAMMER");
    char newRow[MAX_RECORD_LEN];

    sprintf(newRow, "%d,%s,%s,%d,%d,%d,%s,%d\n", newReport.uniqueID, newReport.sShortDesc, newReport.sDesc, newReport.sDateOfCreation, newReport.sDateOfFixed, newReport.sDateOfClosed, newReport.lastWriteInReport, newReport.statusOfReport);
    clearScreen();
    printCover('P');
    printNewLines(2);
    if (rewriteFileWithOneRow(REPLACE_FILE, DATABASE_FILE, currentRowCopy, newRow))
    {
        printf(" --- YOU FIX THE REPORT (#BUG) --- ");
        printNewLines(2);
        printParsedStruct(&newReport);
    }
    else if (!rewriteFileWithOneRow(REPLACE_FILE, DATABASE_FILE, currentRowCopy, newRow))
    {
        printf(" --- Error! ---");
    }

    freeStrings(&newReport);
    return;
}

void verifyReport()
{
    createFileIfNotExist(DATABASE_FILE);

    char getID[20] = {0};

    printf(" -- Enter id TO VERIFY #: ");
    getStrFromAdress(getID);

    int id = atoi(getID);

    if (!isRowExist(id, DATABASE_FILE))
    {
        printf(" -- Wrong ID -- ");
        return;
    }

    char currentRowCopy[MAX_RECORD_LEN] = {0};
    char currentRow[MAX_RECORD_LEN] = {0};
    getRowByIDIfExist(id, DATABASE_FILE, currentRowCopy);
    getRowByIDIfExist(id, DATABASE_FILE, currentRow);
    getExistingReport(id, currentRow);

    if (isReportFixed(newReport.statusOfReport) != 1)
    {
        printf(" --- Record is not \"FIXED\". You can\'t change it. --- ");
        freeStrings(&newReport);
        return;
    }

    printf(" --- ID #%d is FIXED. --- ", id);
    printNewLines(1);
    printf(" -- Do you want to change Report #%d to CLOSED? [y/n]: ", id);

    if (!isContinue())
    {
        printf(" --- The BUG REPORT is not CLOSED! --- ");
        freeStrings(&newReport);
        makePause();
        return;
    }
    newReport.sDateOfClosed = time(NULL);
    newReport.statusOfReport = CLOSED;
    strcpy(newReport.lastWriteInReport, "TESTER");

    char newRow[MAX_RECORD_LEN];
    sprintf(newRow, "%d,%s,%s,%d,%d,%d,%s,%d\n", newReport.uniqueID, newReport.sShortDesc, newReport.sDesc, newReport.sDateOfCreation, newReport.sDateOfFixed, newReport.sDateOfClosed, newReport.lastWriteInReport, newReport.statusOfReport);
    clearScreen();
    printCover('P');
    printNewLines(2);
    if (rewriteFileWithOneRow(REPLACE_FILE, DATABASE_FILE, currentRowCopy, newRow))
    {
        printf(" --- YOU VERIFIED (CLOSED) THE REPORT (#BUG) --- ");
        printNewLines(2);
        printParsedStruct(&newReport);
    }
    else if (!rewriteFileWithOneRow(REPLACE_FILE, DATABASE_FILE, currentRowCopy, newRow))
    {
        printf(" --- Error! ---");
    }
    freeStrings(&newReport);
    return;
}

void printReports(char flag, bugReport *report)
{
    fp = fopen(DATABASE_FILE, "r");
    char buffer[MAX_RECORD_LEN] = {0};
    char *fgetsFile = fgets(buffer, MAX_RECORD_LEN, fp);
    int idCount = 0;
    while (fgetsFile != NULL)
    {
        idCount++;
        getExistingReport(idCount, buffer);
        if (flag == 'a' || flag == 'A')
        {
            printParsedStruct(&newReport);
        }
        else if (report->statusOfReport == NEW && (flag == 'n' || flag == 'N'))
        {
            printParsedStruct(&newReport);
        }
        else if (report->statusOfReport == FIXED && (flag == 'f' || flag == 'F'))
        {
            printParsedStruct(&newReport);
        }
        else if (report->statusOfReport == CLOSED && (flag == 'c' || flag == 'C'))
        {
            printParsedStruct(&newReport);
        }
        memset(buffer, '\0', MAX_RECORD_LEN);
        fgetsFile = fgets(buffer, MAX_RECORD_LEN, fp);
    }
    freeStrings(&newReport);
    fclose(fp);
}