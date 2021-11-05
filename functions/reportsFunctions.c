#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "../main.h"

#define IDS_LENGTH 16
#define SHORT_DESC_LENGTH 128
#define DESC_LENGTH 1024
#define DATE_LENGTH 100
#define WRITER_LENGTH 16
#define STATUS_LENGTH 8
#define MAX_RECORD_LEN 1300
#define DATABASE_FILE "DB.csv"

typedef struct // WE DEFINE TYPE OF TYPE STRUCTURE
{
    char uniqueID[IDS_LENGTH];             //     1. UNIQUE ID NUMBER
    char sShortDesc[SHORT_DESC_LENGTH];    //     2. SHORT DESCRIPTION
    char sDesc[DESC_LENGTH];               //     3. DESCRIPTION
    char sDateOfCreation[DATE_LENGTH];     //     4. DATE OF CREATION(current date)
    char sDateOfFixed[DATE_LENGTH];        //     5. DATE OF FIXED = 0 HERE
    char sDateOfClosed[DATE_LENGTH];       //     6. DATE OF CLOSED = 0 HERE
    char lastWriteInReport[WRITER_LENGTH]; //     7. LAST WRITER IN REPORT : TESTER OR PROGRAMMER
    char statusOfReport[STATUS_LENGTH];    //     8. STATUS : NEW | FIXED | CLOSED
} bugReport; // AND GIVE NAME HIM BUG REPORT

char *serialize(const bugReport *p); //WE USE CONST FOR NOT CHANGE CHARS IN ARRAYS

bugReport newReport;

FILE *fp;

void printAllReports()
{
    createFileIfNotExist(DATABASE_FILE);
    int len = 0;
    fp = fopen(DATABASE_FILE, "r");
    fseek(fp, 0, SEEK_END); // COUNT BYTES FROM BEGGINING

    len = ftell(fp);

    fseek(fp, 0, SEEK_SET); // SET POINTER AT ZERO POSITION

    char *dynArr = (char *)malloc(len * sizeof(char));

    fread(dynArr, sizeof(char), len * sizeof(char), fp);

    int flag = 0;
    for (int i = 0; i < len - 2; i++)
    {
        if(dynArr[i] == '"') {
            flag = (flag == 0);
        }
        else if (dynArr[i - 1] == '\n' && dynArr[i + 1] == ',')
        {
            putchar('#');
            printf("%-2c", dynArr[i]);
        }
        else if (dynArr[i] == ',' && flag == 0)
        {
            printf("  |  ");
        }
        else
        {
            printf("%c", dynArr[i]);
        }
    }

    free(dynArr);

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
    strcpy(newReport.sDateOfCreation, "date");
    strcpy(newReport.sDateOfFixed, "date");
    strcpy(newReport.sDateOfClosed, "date");
    strcpy(newReport.lastWriteInReport, "Tester");
    strcpy(newReport.statusOfReport, "NEW");
    fp = fopen(DATABASE_FILE, "a+"); // OPEN DATABASE FOR WRITING
                                     // fwrite(&newReport, sizeof(char), sizeof(newReport), fp);
                                     // fwrite(&newReport, sizeof(struct bugReport), sizeof(char), fp);
    char *sdata = serialize(&newReport);
    fprintf(fp, "%s\n", sdata);

    //fputc('\n', fp);
    free(sdata);
    fclose(fp);

    // WE FREE DYNAMMIC ARRAYS
    // free(newReport.sShortDesc);
    // free(sDesc);
}

char *serialize(const bugReport *p)
{
    char *out = malloc(MAX_RECORD_LEN * sizeof(*out));
    if (!out)
    {
        fprintf(stderr, "!! could not allocate memory\n");
    }
    else
    {
        memset(out, '\0', MAX_RECORD_LEN);
        sprintf(out, "\"#%-2s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"", p->uniqueID, p->sShortDesc, p->sDesc, p->sDateOfCreation, p->sDateOfFixed, p->sDateOfClosed, p->lastWriteInReport, p->statusOfReport);
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

        else if (c != '\r')
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
                newReport.sDesc[count] = c;
                newReport.sDesc[count + 1] = '\0';
                printf("%s", newReport.sDesc);
                count++;
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
            newReport.sDesc[count] = c;
            newReport.sDesc[count + 1] = '\0';
            printf("%s", newReport.sDesc);
            count++;
        }
    }
}
