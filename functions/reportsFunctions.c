#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "../main.h"

#define IDS_LENGTH 32
#define SHORT_DESC_LENGTH 128
#define DESC_LENGTH 1024
#define DATE_LENGTH 128
#define WRITER_LENGTH 16
#define STATUS_LENGTH 8
#define MAX_RECORD_LEN 2048
#define DATABASE_FILE "DB.csv"

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
} bugReport;                 // AND GIVE NAME HIM BUG REPORT

char *serialize(const bugReport *p); // WE USE CONST FOR NOT CHANGE CHARS IN ARRAYS

bugReport newReport;

FILE *fp;

void printAllReports()
{
    createFileIfNotExist(DATABASE_FILE);
    int len = 0;
    fp = fopen(DATABASE_FILE, "r");
    char c = 0;
    int flag = 0;
    while (c != EOF)
    {
        c = fgetc(fp);
        if (c == '\n' || c == '\r')
        {
            putchar('\n');
        }
        else if (c == '"')
        {
            flag = (flag == 0);
        }
        else if (flag == 1 && c != '"')
        {
            putchar(c);
        }
        else if (flag == 0 && c == ',')
        {
            printf(" | ");
        }
    }

    fclose(fp);
}

void createNewReport()
{
    createFileIfNotExist(DATABASE_FILE);

    // char *sShortDesc = malloc(SHORT_DESC_LENGTH * sizeof(char)); // 128
    // char *sDesc = malloc(DESC_LENGTH * sizeof(char));            // 1024

    printf(" -- REPORT (#BUG) NUMBER: #%d | CURRENT STATUS: NEW -- ", countFileRows(DATABASE_FILE) + 1);
    printNewLines(1);

    printf(" -- Enter short description at single line (MAX 128 chars) ");
    printNewLines(2);

    makePause();
    newReport.uniqueID = (char *)malloc(IDS_LENGTH);
    newReport.sShortDesc = malloc(SHORT_DESC_LENGTH);
    newReport.sDesc = (char *)malloc(DESC_LENGTH);
    newReport.sDateOfCreation = (char *)malloc(DATE_LENGTH);
    newReport.sDateOfFixed = (char *)malloc(DATE_LENGTH);
    newReport.sDateOfClosed = (char *)malloc(DATE_LENGTH);
    newReport.lastWriteInReport = (char *)malloc(WRITER_LENGTH);
    newReport.statusOfReport = (char *)malloc(STATUS_LENGTH);

    getShortDesc(newReport.sShortDesc);
    fflush(stdin);

    getDesc(newReport.sDesc);

    printNewLines(2);
    printf(" Your short desc: %s", newReport.sShortDesc);
    printNewLines(1);
    printf(" Your DESC: %s", newReport.sDesc);
    char buffer[IDS_LENGTH];
    strcpy(newReport.uniqueID, itoa(countFileRows(DATABASE_FILE) + 1, buffer, 10));

    // printf(" \n UNIQUE ID = %d \n", newReport.uniqueID);
    // strcpy(newReport.sDateOfCreation, "0-0-0 0:0:0");
    getCurrentTime(newReport.sDateOfCreation); // save current time in newReport.sDateOfCreation
    strcpy(newReport.sDateOfFixed, "Not fixed");
    strcpy(newReport.sDateOfClosed, "Not Closed");
    strcpy(newReport.lastWriteInReport, "Tester");
    strcpy(newReport.statusOfReport, "NEW");

    fp = fopen(DATABASE_FILE, "a+"); // OPEN DATABASE FOR WRITING
                                     // fwrite(&newReport, sizeof(char), sizeof(newReport), fp);
                                     // fwrite(&newReport, sizeof(struct bugReport), sizeof(char), fp);
    char *sdata = serialize(&newReport);
    fprintf(fp, "%s\n", sdata);

    // WE FREE DYNAMMIC ARRAYS
    free(newReport.uniqueID);
    free(newReport.sShortDesc);
    free(newReport.sDesc);
    free(newReport.sDateOfCreation);
    free(newReport.sDateOfFixed);
    free(newReport.sDateOfClosed);
    free(newReport.lastWriteInReport);
    free(newReport.statusOfReport);
    free(sdata);
    fclose(fp); // we close the file
}

char *serialize(const bugReport *p)
{
    char *out = malloc(MAX_RECORD_LEN * sizeof(*out));
    if (!out)
    {
        fprintf(stderr, "!! could not allocate memory !!");
        printNewLines(1);
    }
    else
    {
        memset(out, '\0', MAX_RECORD_LEN);
        sprintf(out, "\"#%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"", p->uniqueID, p->sShortDesc, p->sDesc, p->sDateOfCreation, p->sDateOfFixed, p->sDateOfClosed, p->lastWriteInReport, p->statusOfReport);
    }
    return out;
}

void getShortDesc(char *sShortDesc)
{

    char c = 0;
    int count = 0;
    clearScreen();
    printCover();
    printLoggedAsTester();
    printNewLines(1);
    printf(" -- PRESS '0' for SAVING -- ");
    printNewLines(1);
    printf(" -- YOUR SHORT DESCRIPTION: ");

    while (c != '0')
    {
        c = getch();
        if (c == '0' && count <= 3) // If user save but COUNTER IS 3 OR LESS
        {
            c = 'A'; // SOME RANDOM LETTER FOR CHANGE THAT 0 TO NOT QUIT FROM LOOP
            printNewLines(1);
            printf(" -- You can save minimum 4 symbols at short description! Please enter more chars! ");
            printNewLines(1);
        }
        else if (c == '0')
        {
            newReport.sShortDesc[++count] = ',';
            newReport.sShortDesc[++count] = '\0';
            printNewLines(1);
            printf(" -- Saved! --");
            break;
        }
        else if (c == '\b')
        {
            clearScreen();
            printCover();
            printLoggedAsTester();
            printNewLines(1);
            printf(" -- PRESS '0' for SAVING -- ");
            printNewLines(1);
            printf(" -- YOUR SHORT DESCRIPTION: ");
            if (count < 1)
            {
                count = 0;
            }
            else if (count > 0)
            {
                newReport.sShortDesc[--count] = '\0';
                printStringTildaToComma(newReport.sShortDesc);
            }
        }
        else if (count > SHORT_DESC_LENGTH)
        {
            printf(" \b"); // WE PRINT SPACE, AND DELETE IT WITH \b (backspace)
        }
        else if (c == ' ')
        {
            if (newReport.sShortDesc[count - 1] != ' ')
            {
                clearScreen();
                printCover();
                printLoggedAsTester();
                printNewLines(1);
                printf(" -- PRESS '0' for SAVING -- ");
                printNewLines(1);
                printf(" -- YOUR SHORT DESCRIPTION: ");
                newReport.sShortDesc[count] = c;
                newReport.sShortDesc[count + 1] = '\0';
                printStringTildaToComma(newReport.sShortDesc);
                count++;
            }
        }

        else if (c != '\r' && c != '"')
        {
            clearScreen();
            printCover();
            printLoggedAsTester();
            printNewLines(1);
            printf(" -- PRESS '0' for SAVING -- ");
            printNewLines(1);
            printf(" -- YOUR SHORT DESCRIPTION: ");
            newReport.sShortDesc[count++] = c;
            newReport.sShortDesc[count] = '\0';
            printStringTildaToComma(newReport.sShortDesc);
            // count++;
        }
    }
}

void getDesc(char *sDesc)
{

    char c = 0;
    int count = 0;
    clearScreen();
    printCover();
    printLoggedAsTester();
    printNewLines(1);
    printf(" -- Press '0' FOR SAVING --");
    printNewLines(1);
    printf(" -- YOUR DESCRIPTION: ");
    while (c != '0')
    {
        c = getch();
        if (c == '0' && count <= 10) // If user save but COUNTER IS 10 OR LESS
        {
            // memset(newReport.sShortDesc, 0, count);
            c = 'A'; // SOME RANDOM LETTER FOR CHANGE THAT 0 TO NOT QUIT FROM LOOP
            printNewLines(1);
            printf(" -- You can save minimum 11 symbols at description! Please enter more chars! ");
            printNewLines(1);
        }
        else if (c == '0')
        {
            printNewLines(1);
            printf(" -- Saved! --");
            break;
        }
        else if (c == '\b')
        {
            clearScreen();
            printCover();
            printLoggedAsTester();
            printNewLines(1);
            printf(" -- Press '0' FOR SAVING --");
            printNewLines(1);
            printf(" -- YOUR DESCRIPTION: ");
            if (count > 0)
            {
                newReport.sDesc[--count] = '\0';
                printf("%s", newReport.sDesc);
            }
        }
        else if (count > DESC_LENGTH)
        {
            printf(" \b"); // WE PRINT SPACE, AND DELETE IT WITH \b (backspace)
        }
        else if (c == ' ')
        {
            if (newReport.sDesc[count - 1] != ' ')
            {
                clearScreen();
                printCover();
                printLoggedAsTester();
                printNewLines(1);
                printf(" -- Press '0' FOR SAVING --");
                printNewLines(1);
                printf(" -- YOUR DESCRIPTION: ");
                newReport.sDesc[count++] = c;
                newReport.sDesc[count] = '\0';
                printf("%s", newReport.sDesc);
            }
        }

        else if (c != '\r')
        {
            clearScreen();
            printCover();
            printLoggedAsTester();
            printNewLines(1);
            printf(" -- Press '0' FOR SAVING --");
            printNewLines(1);
            printf(" -- YOUR DESCRIPTION: ");
            newReport.sDesc[count++] = c;
            newReport.sDesc[count] = '\0';
            printf("%s", newReport.sDesc);
        }
    }
}

void editSpecificNewReport()
{
    createFileIfNotExist(DATABASE_FILE);

    char c[20] = {0};
    printf(" -- Enter ID #: ");
    scanf("%s", c);

    char inputID[21] = {0};
    strcat(inputID, "#");
    strcat(inputID, c);

    int len = 0;
    fp = fopen(DATABASE_FILE, "r");
    char currentChar = 0;
    int countChars = 0;
    int flag = 0;
    while (currentChar != EOF)
    {
        currentChar = fgetc(fp);
        countChars++;
    }

    char *sData = (char *)malloc(countChars * sizeof(char));
    currentChar = 0, countChars = 0;

    fseek(fp, 0, SEEK_SET);

    while (currentChar != EOF)
    {
        currentChar = fgetc(fp);
        sData[countChars] = currentChar;
        countChars++;
    }

    char currentID[20] = {0};
    int counterID = 0, isMatched = 0, j = 0;
    char record[MAX_RECORD_LEN] = {0};

    for (int i = 0; i < countChars; i++)
    {
        if (sData[i] == '#')
        {
            for (j = i, counterID = 0; sData[j] != '"'; j++, counterID++)
            {
                currentID[counterID] = sData[j];
            }

            if (strcmp(inputID, currentID) == 0)
            {
                sprintf(record, "\"%s\" ", currentID);
                int recLen = strlen(record);
                for (int k = j, recCounter = j; sData[k] != '\n'; k++)
                {
                    if (sData[k] != '\0')
                    {
                        record[recLen++] = sData[k];
                    }
                }

                isMatched = 1;
                break;
            }

            memset(currentID, '\0', counterID);
        }
    }

    if (isMatched)
    {
        printf(" -- You hit ID! %s -- ", record);
    }
    else
    {
        printf(" -- Wrong ID --");
    }
    free(sData);

    fclose(fp);
}

void arrayToStruct(char *record, int size)
{
    for (int i = 0; i < size; i++)
    {
        
    }
}

// char *uniqueID;          //     1. UNIQUE ID NUMBER
//     char *sShortDesc;        //     2. SHORT DESCRIPTION
//     char *sDesc;             //     3. DESCRIPTION
//     char *sDateOfCreation;   //     4. DATE OF CREATION(current date)
//     char *sDateOfFixed;      //     5. DATE OF FIXED = 0 HERE
//     char *sDateOfClosed;     //     6. DATE OF CLOSED = 0 HERE
//     char *lastWriteInReport; //     7. LAST WRITER IN REPORT : TESTER OR PROGRAMMER
//     char *statusOfReport;    //     8. STATUS : NEW | FIXED | CLOSED
