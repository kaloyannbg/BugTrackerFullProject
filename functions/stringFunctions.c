#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <conio.h>
#include "../main.h"

void getStrFromAdress(char *str)
{
    scanf("%s", str);
    fflush(stdin);
}

char stringUpperToLower(char *arr)
{
    while (*(arr) != '\0')
    {
        *(arr) = tolower(*(arr));
        *(arr++);
    }
}

char changeCharInArr(char *inputArr, char cChar, char toChar)
{
    for (int i = 0; inputArr[i] != '\0'; i++)
    {
        if (inputArr[i] == cChar)
        {
            inputArr[i] = toChar;
        }
    }
}

void getSentence(char *inputArr, int minLimit, int maxLimit)
{
    printf(" -- Min limit: %d -- Max limit of chars: %d. -- ", minLimit, maxLimit);
    printNewLines(oneLine);
    printf(" -- Press ENTER for save. -- ");
    minLimit = abs(minLimit);
    maxLimit = abs(maxLimit);

    char c = 0, d = 0;
    int countChars = 0;

    printNewLines(oneLine);
    printf(" -- Your text: ");

    while (c != '\n')
    {
        c = getchar();
        if (countChars > maxLimit)
        {
            // printf(" --- Sorry but you are out of limit. Max limit is: 128 chars --- ");
            countChars++;
            break;
        }
        else if (c == ' ')
        {
            inputArr[countChars++] = ' ';
            c = getchar();
            if (c == ' ')
            {
                while (c == ' ')
                {
                    c = getchar();
                }
            }
            if (c == ',')
            {
                inputArr[countChars++] = '/';
            }
            else if (c != '\n')
            {
                inputArr[countChars++] = c;
            }
            else if (c == '\n')
            {
                inputArr[countChars] = '\0';
                break;
            }
        }
        else if (c == ',')
        {
            inputArr[countChars++] = '/';
        }
        else if (c != '\n')
        {
            inputArr[countChars++] = c;
        }
        else if (c == '\n')
        {
            inputArr[countChars] = '\0';
            break;
        }
    }

    if (countChars < minLimit)
    {
        memset(inputArr, 0, countChars); // MEMSET DA OPRAVQ
        printNewLines(oneLine);
        printf("  -- Sorry but you are under limit. Min limit is: %d chars -- ", minLimit);
    }
    else if (countChars > maxLimit)
    {
        memset(inputArr, 0, countChars);
        printNewLines(oneLine);
        printf("  - Sorry but you are out of limit. Max limit is: %d chars -- ", maxLimit);
    }
    else if (countChars > minLimit && countChars < maxLimit)
    {
        printNewLines(oneLine);
        printf("  - Congratz! -- ");
    }
}

void printParsedArr(char *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == '/')
        {
            putchar(',');
        }
        else
        {
            printf("%c", arr[i]);
        }
    }
}

void printDateFromTimestamp(time_t timestamp)
{
    time_t t = timestamp;
    struct tm *tm = localtime(&t);
    printf("%02d-%02d-%02d %02d:%02d:%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
}

void printParsedStruct(bugReport *report)
{
    printf(" --- %-5d | ", report->uniqueID);
    printParsedArr(report->sShortDesc, strlen(report->sShortDesc));
    printf(" | ");
    printParsedArr(report->sDesc, strlen(report->sDesc));
    printf(" | ");
    printDateFromTimestamp(report->sDateOfCreation);
    printf(" | ");
    if (report->sDateOfFixed == 0)
    {
        printf("NOT FIXED");
    }
    else
    {
        printDateFromTimestamp(report->sDateOfFixed);
    }
    printf(" | ");
    if (report->sDateOfClosed == 0)
    {
        printf("NOT VERIFIED");
    }
    else
    {
        printDateFromTimestamp(report->sDateOfClosed);
    }
    printf(" | ");
    printf("TESTER: %s", report->sTester);
    printf(" | ");
    printf("PROGRAMMER: %s", report->sProgrammer);
    printf(" | ");
    if (report->statusOfReport == NEW)
    {
        printf("NEW");
    }
    else if (report->statusOfReport == FIXED)
    {
        printf("FIXED");
    }
    else if (report->statusOfReport == CLOSED)
    {
        printf("CLOSED");
    }
    printf(" | ");
    putchar('\n');
}

int isUsernameValid(char *username)
{

    if (strlen(username) <= 3 || strlen(username) >= 21)
    {
        return -1;
    }

    while (*username != '\0')
    {
        if (!isLetter(*(username)))
        {
            return 0;
        }

        *(username++);
    }
    return 1;
}

int isPasswordValid(char *password)
{
    if (strlen(password) <= 4 || strlen(password) >= 21)
    {
        return -1;
    }

    while (*password != '\0')
    {
        if (!isDigit(*(password)))
        {
            return 0;
        }
        *(password++);
    }
    return 1;
}

void parsePasswordToStars(string buffer, int currentSize)
{
    for (int i = 0; i < currentSize; i++)
    {
        putchar('*');
    }
}

void getPassword(string buffer, int maxSize)
{
    char c = 0;
    int cCounter = 0;
    memset(buffer, 0, strlen(buffer));
    while (c != '\n')
    {
        clearScreen();
        printCover(GUEST);
        printf(" -- Username: %s", regInstance.user);
        printNewLines(oneLine);
        printf(" -- Password: ");
        parsePasswordToStars(buffer, strlen(buffer));
        c = getch();
        if (c == '\b')
        {
            if (cCounter >= true)
            {
                buffer[--cCounter] = '\0';
            }
        }
        else if (cCounter == maxSize)
        {
            printNewLines(oneLine);
            printf(" -- You are on max password length: %d!", maxSize);
            printNewLines(oneLine);
            makePause();
        }

        else if (c != '\r')
        {
            buffer[cCounter++] = c;
        }
        else if (c == '\r')
        {
            buffer[cCounter] = '\0';
            return;
        }
    }
}
