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

void freeStrings(bugReport *report) {
    free(report->sShortDesc);
    free(report->sDesc);
    free(report->lastWriteInReport);
}