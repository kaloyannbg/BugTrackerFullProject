#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../main.h"

void createNewReport()
{
    createFileIfNotExist(DATABASE_FILE);

    clearScreen();
    printCover(TESTER);
    printNewLines(oneLine);
    newReport.sShortDesc = (string)calloc(SHORT_DESC_LENGTH, sizeof(char));
    printf(" --- Enter text for short description. REPORT ID#%d ", countFileRows(DATABASE_FILE) + 1);
    getSentence(newReport.sShortDesc, MIN_SHORT_DESC_LENGTH, SHORT_DESC_LENGTH);
    printNewLines(oneLine);
    if (strlen(newReport.sShortDesc) < MIN_SHORT_DESC_LENGTH || strlen(newReport.sShortDesc) > SHORT_DESC_LENGTH)
    {
        free(newReport.sShortDesc);
        printf(" --- Log in as tester and try again! ---");
        return;
    }
    newReport.sDesc = (string)calloc(DESC_LENGTH, sizeof(char));
    printNewLines(oneLine);
    printf(" --- Enter text for description. --- ");
    getSentence(newReport.sDesc, MIN_DESC_LENGTH, DESC_LENGTH);
    printNewLines(oneLine);
    if (strlen(newReport.sDesc) < MIN_DESC_LENGTH || strlen(newReport.sDesc) > DESC_LENGTH)
    {
        free(newReport.sShortDesc);
        free(newReport.sDesc);
        printf(" --- Log in as tester and try again! ---");
        return;
    }

    newReport.sTester = (string)malloc(WRITER_LENGTH);
    strcpy(newReport.sTester, regInstance.user);
    // strcat(newReport.sTester, "someTestHere");

    newReport.sProgrammer = (string)malloc(WRITER_LENGTH);
    strcpy(newReport.sProgrammer, UNDEFINED_NAME);

    newReport.uniqueID = countFileRows(DATABASE_FILE) + 1;
    newReport.sDateOfCreation = time(NULL);
    newReport.sDateOfFixed = 0;
    newReport.sDateOfClosed = 0;
    newReport.statusOfReport = NEW;

    char *arrayPutInFile = (char *)malloc(MAX_RECORD_LEN);
    fp = fopen(DATABASE_FILE, "a+");
    sprintf(arrayPutInFile, "%d,%s,%s,%d,%d,%d,%s,%s,%d", newReport.uniqueID, newReport.sShortDesc, newReport.sDesc, newReport.sDateOfCreation, newReport.sDateOfFixed, newReport.sDateOfClosed, newReport.sTester, newReport.sProgrammer, newReport.statusOfReport);
    fprintf(fp, "%s\n", arrayPutInFile);
    fclose(fp);

    freeStrings(&newReport);
    free(arrayPutInFile);
}

int isReportNew(int statusOfReport) // да си направя ретърн за тру анд фолс
{
    if (statusOfReport == NEW)
    {
        return true; // return true
    }

    return false; // return false
}

int isReportFixed(int statusOfReport)
{
    if (statusOfReport == FIXED)
    {
        return true;
    }
    return false;
}

void putReportInStruct(char *buffer)
{
    char *dynBuffer = (string)malloc(strlen(buffer) + 1);
    strcpy(dynBuffer, buffer);
    newReport.sShortDesc = (string)malloc(SHORT_DESC_LENGTH);
    newReport.sDesc = (string)malloc(DESC_LENGTH);
    newReport.sTester = (string)malloc(WRITER_LENGTH);
    newReport.sProgrammer = (string)malloc(WRITER_LENGTH);

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
        case TESTER_POS:
            strcpy(newReport.sTester, token);
            break;
        case PROGRAMMER_POS:
            strcpy(newReport.sProgrammer, token);
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

    char getID[MAX_ID_LENGTH] = {0};

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

    char getID[MAX_ID_LENGTH] = {0};

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
    printNewLines(oneLine);
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
    strcpy(newReport.sProgrammer, regInstance.user);
    char newRow[MAX_RECORD_LEN] = {0};

    sprintf(newRow, "%d,%s,%s,%d,%d,%d,%s,%s,%d\n", newReport.uniqueID, newReport.sShortDesc, newReport.sDesc, newReport.sDateOfCreation, newReport.sDateOfFixed, newReport.sDateOfClosed, newReport.sTester, newReport.sProgrammer, newReport.statusOfReport);
    clearScreen();
    printCover(PROGRAMMER);
    printNewLines(twoLines);
    if (changeRow(REPLACE_FILE, DATABASE_FILE, currentRow, newRow))
    {
        printf(" --- YOU FIX THE REPORT (#BUG) --- ");
        printNewLines(twoLines);
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

    char getID[MAX_ID_LENGTH] = {0};

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
    printNewLines(oneLine);
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
    strcpy(newReport.sTester, regInstance.user);

    char newRow[MAX_RECORD_LEN] = {0};
    sprintf(newRow, "%d,%s,%s,%d,%d,%d,%s,%s,%d\n", newReport.uniqueID, newReport.sShortDesc, newReport.sDesc, newReport.sDateOfCreation, newReport.sDateOfFixed, newReport.sDateOfClosed, newReport.sTester, newReport.sProgrammer, newReport.statusOfReport);
    clearScreen();
    printCover(PROGRAMMER);
    printNewLines(twoLines);
    if (changeRow(REPLACE_FILE, DATABASE_FILE, currentRow, newRow))
    {
        printf(" --- YOU VERIFIED (CLOSED) THE REPORT (#BUG) --- ");
        printNewLines(twoLines);
        printParsedStruct(&newReport);
    }
    else if (!changeRow(REPLACE_FILE, DATABASE_FILE, currentRow, newRow))
    {
        printf(" --- Error! ---");
    }
    freeStrings(&newReport);
    return;
}

void printReports(enPrintType flag)
{
    int rowsInFile = countFileRows(DATABASE_FILE);

    bugReport *arrayOfStructs = (bugReport *)malloc(rowsInFile * sizeof(bugReport));

    char *buffer = (string)calloc(MAX_RECORD_LEN, sizeof(char));
    fp = fopen(DATABASE_FILE, "r");

    for (int i = 0; i < rowsInFile; i++)
    {
        fgets(buffer, MAX_RECORD_LEN, fp);
        putReportInStruct(buffer);
        arrayOfStructs[i] = newReport;
    }

    free(buffer);
    fclose(fp);
    if (flag == REVERSED_TYPE)
    {
        for (int i = rowsInFile - 1; i >= 0; i--)
        {
            printParsedStruct(arrayOfStructs + i);
        }
    }
    else if (flag == REGULAR_TYPE) // all rows
    {
        for (int i = 0; i < rowsInFile; i++)
        {
            printParsedStruct(arrayOfStructs + i);
        }
    }
    else if (flag == NEW_TYPE)
    {
        for (int i = 0; i < rowsInFile; i++)
        {
            if (arrayOfStructs[i].statusOfReport == NEW)
            {
                printParsedStruct(arrayOfStructs + i);
            }
        }
    }
    else if (flag == FIXED_TYPE)
    {
        for (int i = 0; i < rowsInFile; i++)
        {
            if (arrayOfStructs[i].statusOfReport == FIXED)
            {
                printParsedStruct(arrayOfStructs + i);
            }
        }
    }
    else if (flag == CLOSED_TYPE)
    {
        for (int i = 0; i < rowsInFile; i++)
        {
            if (arrayOfStructs[i].statusOfReport == CLOSED)
            {
                printParsedStruct(arrayOfStructs + i);
            }
        }
    }

    freeArrayOfStructs(rowsInFile, arrayOfStructs);
}