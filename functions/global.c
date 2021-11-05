#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../main.h"

void getInt(int *var)
{
    scanf("%d", var);
}

void getCharFromAdress(char *c)
{
    scanf("%c", c);
    fflush(stdin);
}

void printNewLines(int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("\n");
    }
}

void clearScreen()
{
    system("cls");
}

void makePause()
{
    system("PAUSE");
}