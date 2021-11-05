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

