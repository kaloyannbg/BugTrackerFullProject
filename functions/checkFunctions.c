#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../main.h"

int isLetter(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int isDigit(char c)
{
    return (c >= '0' && c <= '9');
}

int isContinue()
{
    char contin = 0;
    fflush(stdin);
    getCharFromAdress(&contin);
    fflush(stdin);
    if (contin == 'y' || contin == 'Y')
    {
        return 1;
    }
    return 0;
}

int countDigits(int num)
{
    int count = 0;
    do
    {
        num /= 10;
        ++count;

    } while (num != 0);
    return num;
}
