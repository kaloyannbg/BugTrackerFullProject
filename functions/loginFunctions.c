#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../main.h"

int isSessionContinue(char *charAdress)
{
    if (*charAdress == 'y' || *charAdress == 'Y')
    {
        return 1;
    }
    else if (*charAdress == 'n' || *charAdress == 'N')
    {
        return 0;
    }

    return -1;
}