#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../main.h"

void free2DArrFromMemory(char **array, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(array[i]);
    }
    free(array);
}

void freeStrings(bugReport *report)
{
    free(report->sShortDesc);
    free(report->sDesc);
    free(report->sTester);
    free(report->sProgrammer);
}

void freeArrayOfStructs(int rowsInFile, bugReport *arrayOfStructs)
{
    for (int i = 0; i < rowsInFile; i++)
    {
        freeStrings(arrayOfStructs + i);
    }
    free(arrayOfStructs);
}

void freeStringsFromLoginStructure(LoginDetails *details)
{
    free(details->user);
    free(details->pass);
}

void freeArrayOfLoginStructs(int rowsInFile, LoginDetails *arrayOfStructs)
{
    for (int i = 0; i < rowsInFile; i++)
    {
        freeStringsFromLoginStructure(arrayOfStructs + i);
    }
    free(arrayOfStructs);
}