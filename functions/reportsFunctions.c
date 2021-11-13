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

void putReportInStruct(char *buffer)
{
    char *dynBuffer = (char *)malloc(strlen(buffer) + 1);
    strcpy(dynBuffer, buffer);
    newReport.sShortDesc = (char *)malloc(SHORT_DESC_LENGTH);
    newReport.sDesc = (char *)malloc(DESC_LENGTH);
    newReport.lastWriteInReport = (char *)malloc(WRITER_LENGTH);

    int countStr = 0;
    char *token = strtok(dynBuffer, ",");
    while (token != NULL)
    {
        switch (countStr)
        {
        case UNIQUE_ID_POS:
            newReport.uniqueID = atoi(token);
            break;
        case SHORT_DESC_POS:
            strcpy(newReport.sShortDesc, token);
            break;
        case DESC_POS:
            strcpy(newReport.sDesc, token);
            break;
        case DATE_CREATION_POS:
            newReport.sDateOfCreation = atoi(token);
            break;
        case DATE_FIXED_POS:
            newReport.sDateOfFixed = atoi(token);
            break;
        case DATE_CLOSED_POS:
            newReport.sDateOfClosed = atoi(token);
            break;
        case LAST_WRITER_POS:
            strcpy(newReport.lastWriteInReport, token);
            break;
        case STATUS_REPORT_POS:
            newReport.statusOfReport = atoi(token);
        default:
            break;
        }
        token = strtok(NULL, ",");
        countStr++;
    }
    free(dynBuffer);
}

void checkReport()
{

    createFileIfNotExist(DATABASE_FILE);

    char getID[20] = {0};

    printf(" -- Enter id TO CHECK #: ");
    getStrFromAdress(getID);

    int id = atoi(getID);

    if (!isRowExist(id, DATABASE_FILE))
    {
        printf(" -- Report with ID %d do not exist~ -- ", id);
        return;
    }
    char currentRow[MAX_RECORD_LEN] = {0};
    getRowByIDIfExist(id, DATABASE_FILE, currentRow);
    putReportInStruct(currentRow);
    printParsedStruct(&newReport);
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

    char currentRow[MAX_RECORD_LEN] = {0};
    getRowByIDIfExist(id, DATABASE_FILE, currentRow);
    putReportInStruct(currentRow);

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
    if (changeRow(REPLACE_FILE, DATABASE_FILE, currentRow, newRow))
    {
        printf(" --- YOU FIX THE REPORT (#BUG) --- ");
        printNewLines(2);
        printParsedStruct(&newReport);
    }
    else if (!changeRow(REPLACE_FILE, DATABASE_FILE, currentRow, newRow))
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

    char currentRow[MAX_RECORD_LEN] = {0};
    getRowByIDIfExist(id, DATABASE_FILE, currentRow);
    putReportInStruct(currentRow);

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
    if (changeRow(REPLACE_FILE, DATABASE_FILE, currentRow, newRow))
    {
        printf(" --- YOU VERIFIED (CLOSED) THE REPORT (#BUG) --- ");
        printNewLines(2);
        printParsedStruct(&newReport);
    }
    else if (!changeRow(REPLACE_FILE, DATABASE_FILE, currentRow, newRow))
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
    while (fgetsFile != NULL)
    {
        putReportInStruct(buffer);
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