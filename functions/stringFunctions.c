#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "../main.h"

void getStrFromAdress(char *str)
{
    scanf("%s", str);
    fflush(stdin);
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
    printNewLines(1);
    printf(" -- Press ENTER for save. -- ");
    minLimit = abs(minLimit);
    maxLimit = abs(maxLimit);

    char c = 0, d = 0;
    int countChars = 0;

    printNewLines(1);
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
        memset(inputArr, '\0', countChars);
        printNewLines(1);
        printf("  -- Sorry but you are under limit. Min limit is: %d chars -- ", minLimit);
    }
    else if (countChars > maxLimit)
    {
        memset(inputArr, '\0', countChars);
        printNewLines(1);
        printf("  - Sorry but you are out of limit. Max limit is: %d chars -- ", maxLimit);
    }
    else if (countChars > minLimit && countChars < maxLimit)
    {
        printNewLines(1);
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

void printParsedStruct(bugReport *report)
{
    printf(" --- %-5d | ", report->uniqueID);
    printParsedArr(report->sShortDesc, strlen(report->sShortDesc));
    printf(" | ");
    printParsedArr(report->sDesc, strlen(report->sDesc));
    printf(" | ");
    printf("%s", report->lastWriteInReport);
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


