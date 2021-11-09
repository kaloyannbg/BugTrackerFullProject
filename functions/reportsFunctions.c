#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../main.h"

typedef struct // WE DEFINE TYPE OF TYPE STRUCTURE
{
    char *uniqueID;          //     1. UNIQUE ID NUMBER
    char *sShortDesc;        //     2. SHORT DESCRIPTION
    char *sDesc;             //     3. DESCRIPTION
    char *sDateOfCreation;   //     4. DATE OF CREATION(current date)
    char *sDateOfFixed;      //     5. DATE OF FIXED = 0 HERE
    char *sDateOfClosed;     //     6. DATE OF CLOSED = 0 HERE
    char *lastWriteInReport; //     7. LAST WRITER IN REPORT : TESTER OR PROGRAMMER
    char *statusOfReport;    //     8. STATUS : NEW | FIXED | CLOSED

} bugReport; // AND GIVE NAME HIM BUG REPORT

bugReport newReport;

void printAllReports()
{
    createFileIfNotExist(DATABASE_FILE);
    fp = fopen(DATABASE_FILE, "r");
    char buffer[MAX_RECORD_LEN];
    char *fgetsFile = fgets(buffer, MAX_RECORD_LEN, fp);
    char miniBuffer[20]; // buffer with spaces
    int miniBufferCounter = 0, i = 0, j = 0;
    int maxSpaces = 6;
    while (fgetsFile != NULL)
    {
        for (int i = 0; i < strlen(buffer); i++)
        {
            if (buffer[i] == ',')
            {
                if (miniBufferCounter > 0)
                {
                }
                printf(" | ");
            }
            else if (buffer[i] != ',')
            {
                if (buffer[i] == '#' && i == 0)
                {
                    for (j = 0; buffer[j] != ','; j++)
                    {
                        miniBuffer[miniBufferCounter++] = buffer[j];
                    }
                    miniBuffer[miniBufferCounter] = '\0';
                    printf("%s ", miniBuffer);
                    for(int k = 0; k < (maxSpaces-strlen(miniBuffer)); k++ ) {
                        putchar(' ');
                    }
                }
                else if (i > strlen(miniBuffer))
                {
                    printf("%c", buffer[i]);
                }
            }
        }
        fgetsFile = fgets(buffer, MAX_RECORD_LEN, fp);
        miniBufferCounter = 0;
    }

    fclose(fp);
}

void createNewReport()
{
    createFileIfNotExist(DATABASE_FILE);

    clearScreen();
    printCover();
    printLoggedAsTester();
    printNewLines(1);
    newReport.sShortDesc = calloc(SHORT_DESC_LENGTH, sizeof(char));
    printf(" --- Enter text for short description. REPORT ID#%d ", countFileRows(DATABASE_FILE) + 1);
    getSentence(newReport.sShortDesc, 4, SHORT_DESC_LENGTH);
    printNewLines(1);
    if (strlen(newReport.sShortDesc) < 4)
    {
        printf(" --- Log in as tester and try again! ---");
        return;
    }
    newReport.sDesc = calloc(DESC_LENGTH, sizeof(char));
    printNewLines(1);
    printf(" --- Enter text for description. --- ");
    getSentence(newReport.sDesc, 10, DESC_LENGTH);
    printNewLines(1);
    if (strlen(newReport.sDesc) < 10)
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
    scanf("%s", getID);

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
        return;
    }

    char currDate[DATE_LENGTH];
    getCurrentTime(currDate);
    strcpy(explodeCurrentRecord[4], currDate);
    strcpy(explodeCurrentRecord[6], "PROGRAMMER"); // 7 newReport.lastWriteInReport =
    strcpy(explodeCurrentRecord[7], "FIXED");      // 8 newReport.statusOfReport =
    char newRow[MAX_RECORD_LEN];
    sprintf(newRow, "%s,%s,%s,%s,%s,%s,%s,%s\n", explodeCurrentRecord[0], explodeCurrentRecord[1], explodeCurrentRecord[2], explodeCurrentRecord[3], explodeCurrentRecord[4], explodeCurrentRecord[5], explodeCurrentRecord[6], explodeCurrentRecord[7]);
    clearScreen();
    printCover();
    printNewLines(1);
    printLoggedAsProgrammer();
    printNewLines(2);
    if (rewriteFileWithOneRow(REPLACE_FILE, DATABASE_FILE, currentRowCopy, newRow))
    {
        printf(" --- YOU FIX THE REPORT (#BUG) :  %s", newRow);
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
    scanf("%s", getID);

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
    printCover();
    printNewLines(1);
    printLoggedAsTester();
    printNewLines(2);
    if (rewriteFileWithOneRow(REPLACE_FILE, DATABASE_FILE, currentRowCopy, newRow))
    {
        printf(" --- YOU FIX THE REPORT (#BUG) :  %s", newRow);
    }
    else if (!rewriteFileWithOneRow(REPLACE_FILE, DATABASE_FILE, currentRowCopy, newRow))
    {
        printf(" --- Error! ---");
    }

    free2DArrFromMemory(explodeCurrentRecord, structCount);

    return;
}
