#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../main.h"

//#define MAX_BUFFER_SIZE 100000
FILE *fp;

//char buffer[MAX_BUFFER_SIZE];

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
    int len = 0;
     char *buffer = 0;

    fp = fopen(fileName, "r");
    fseek(fp, 0, SEEK_END); // get bytes of file , 300 chars = 300 bytes

    len = ftell(fp);        // COUNT BYTES FROM BEGGINING
    fseek(fp, 0, SEEK_SET); // SET POINTER AT ZERO POSITION

    len += 1; // ADD 1 CHAR FOR TERMINATION ZERO
    buffer = (char *)malloc(len * sizeof(char)); // CREATE DYNAMIC BUFFER FOR CONTENT OF FILE
    fread(buffer, sizeof(char), len - 1, fp); // SAVE ALL CONTENT FROM FILE AT BUFFER len-1 (because we save that space for \0)
    buffer[len] = '\0';
    fclose(fp);
    int counter = 0, counterNewLines = 0;

    while (counter < len)
    {
        if (buffer[counter] == '\n')
        {
            counterNewLines++;
        }
        counter++;
    }

   // memset(buffer, 0, len);     // clear our buffer
    free(buffer);
    return counterNewLines; // +1 BECAUSE WE DONT COUNT NEWLINE BEFORE FIRST STRING
}