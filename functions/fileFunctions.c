#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../main.h"

int isFileExist(char *fileName)
{
    fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        fclose(fp);
        return 0;
    }
    else
    {
        fclose(fp);
        return 1;
    }
}

void createFileIfNotExist(char *fileName)
{
    if (!isFileExist(fileName)) // if return 0
    {
        fp = fopen(fileName, "w");
        fclose(fp);
    }
}

int countFileRows(char *fileName)
{
    int count = 0;

    char buffer[MAX_RECORD_LEN];

    fp = fopen(fileName, "r");

    char *fgetsFile = fgets(buffer, MAX_RECORD_LEN, fp);

    while (fgetsFile != NULL)
    {
        count++;
        fgetsFile = fgets(buffer, MAX_RECORD_LEN, fp);
    }
    fclose(fp);
    return count;
}

int isRowExist(int row, char *fileName)
{
    fp = fopen(fileName, "r");
    char buffer[MAX_RECORD_LEN];
    int countRows = 1;
    char *fgetsFile = fgets(buffer, MAX_RECORD_LEN, fp);
    while (fgetsFile != NULL)
    {
        if (countRows == row)
        {
            fclose(fp);
            return 1;
        }
        countRows++;
        fgetsFile = fgets(buffer, MAX_RECORD_LEN, fp);
    }
    fclose(fp);
    return 0;
}

void getRowByIDIfExist(int row, char *fileName, char *out)
{

    fp = fopen(fileName, "r");

    char buffer[MAX_RECORD_LEN];

    char *fgetsFile = fgets(buffer, MAX_RECORD_LEN, fp); // If an error occurs, a null pointer is returned.
    int countRows = 1;
    while (fgetsFile != NULL)
    {
        if (countRows == row)
        {
            strcpy(out, buffer);
            fclose(fp);
            return;
        }
        countRows++;
        fgetsFile = fgets(buffer, MAX_RECORD_LEN, fp);
    }
    fclose(fp);
}

int changeRow(char *replaceFile, char *withFile, char *rowToReplace, char *newRow)
{
    char buffer[MAX_RECORD_LEN];
    fTemp = fopen(replaceFile, "w");
    fp = fopen(withFile, "r");
    int count = 0;
    fseek(fp, 0, SEEK_SET);
    fseek(fTemp, 0, SEEK_SET);
    fflush(stdin);

    char *fileP = fgets(buffer, MAX_RECORD_LEN, fp);

    while (fileP != NULL)
    {
        count++;
        // If current line is line to replace
        if (strcmp(buffer, rowToReplace) == 0)
        {
            fputs(newRow, fTemp);
        }
        else if (strcmp(buffer, rowToReplace) != 0)
        {
            fputs(buffer, fTemp);
        }
        memset(buffer, '\0', strlen(buffer));
        fileP = fgets(buffer, MAX_RECORD_LEN, fp);
    }

    fclose(fp);
    fclose(fTemp);

    fflush(stdin);

    if (remove(withFile) == 0)
    {
        remove(withFile);
        rename(replaceFile, withFile);
        return 1;
    }

    printf("%s , ", strerror(errno));
    return 0;
}