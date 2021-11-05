#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "../main.h"

void printStringFromSecondElement(char *str)
{
    for (int i = 1; str[i] != '\0'; i++)
    {
        printf("%c", str[i]);
    }
}

void printStringTildaToComma(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '~')
        {
            printf(",");
        }
        else
        {
            printf("%c", str[i]);
        }
    }
}