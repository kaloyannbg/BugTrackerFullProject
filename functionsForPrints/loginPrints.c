#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../main.h"

void printLoginChoice()
{
    printf(" -- Enter 1 for log in as programmer! --");
    printNewLines(oneLine);
    printf(" -- Enter 2 for log in as tester! --");
    printNewLines(oneLine);
    printf(" -- Enter 3 for new registration! --");
    printNewLines(twoLines);
}

void printLoggedAs(enUserType flag)
{
    if (flag == PROGRAMMER)
    {
        printf(" *          You are logged as PROGRAMMER          *");
    }
    else if (flag == TESTER)
    {
        printf(" *            You are logged as TESTER            *");
    }
}

void printLoginContinue(enUserType flag)
{
    if (flag == PROGRAMMER)
    {
        printf(" ---- Do you want to stay logged as: PROGRAMMER ? [y/n]: ");
    }
    else if (flag == TESTER)
    {
        printf(" ---- Do you want to stay logged as: TESTER ? [y/n]: ");
    }
}