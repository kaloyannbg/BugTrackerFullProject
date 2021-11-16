#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../main.h"

void printCover(enUserType flag)
{
    printf(" ************************************************** ");
    printNewLines(oneLine);
    printf(" *                                                * ");
    printNewLines(oneLine);
    printf(" *             Project: Bug tracker               * ");
    printNewLines(oneLine);
    printf(" *        Project Choice: Ivan Fildishev          * ");
    printNewLines(oneLine);
    printf(" *            Author: Kaloyan Angelov             * ");
    printNewLines(oneLine);
    printf(" *            START DATE: 03.11.2021              * ");
    printNewLines(oneLine);
    printf(" *                                                * ");
    printNewLines(oneLine);
    printf(" ************************************************** ");
    printNewLines(twoLines);
    printf(" ************************************************** ");
    printNewLines(oneLine);
    if (flag == PROGRAMMER)
    {
        printLoggedAs(PROGRAMMER);
        printNewLines(oneLine);
        printf("  \t    Your nickname: %s", regInstance.user);
    }
    else if (flag == TESTER)
    {
        printLoggedAs(TESTER);
        printNewLines(oneLine);
        printf("  \t    Your nickname: %s", regInstance.user);
    }
    else if(flag == GUEST)
    {
        printf(" *               You are not logged.              *");
    }

    printNewLines(oneLine);
    printf(" ************************************************** ");
    printNewLines(oneLine);
}