#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../main.h"

void printLoginChoice()
{
    printf(" -- Enter 1 for log in as programmer! --");
    printNewLines(1);
    printf(" -- Enter 2 for log in as tester! --");
    printNewLines(2);
}

void printLoggedAs(char flag)
{
    if (flag == 'p' || flag == 'P')
    {
        printf(" *          You are logged as PROGRAMMER          *");
    }
    else if (flag == 't' || flag == 'T')
    {
        printf(" *            You are logged as TESTER            *");
    }
}

void printLoginContinue(char flag)
{
    if (flag == 'p' || flag == 'P')
    {
        printf(" ---- Do you want to stay logged as: PROGRAMMER ? [y/n]: ");
    }
    else if (flag == 't' || flag == 'T')
    {
        printf(" ---- Do you want to stay logged as: TESTER ? [y/n]: ");
    }
}