#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../main.h"

void printCover(char flag)
{
    char DBFile[7] = "DB.csv";
    printf(" ************************************************** ");
    printNewLines(1);
    printf(" *                                                * ");
    printNewLines(1);
    printf(" *             Project: Bug tracker               * ");
    printNewLines(1);
    printf(" *        Project Choice: Ivan Fildishev          * ");
    printNewLines(1);
    printf(" *            Author: Kaloyan Angelov             * ");
    printNewLines(1);
    printf(" *            START DATE: 03.11.2021              * ");
    printNewLines(1);
    printf(" *                                                * ");
    printNewLines(1);
    printf(" ************************************************** ");
    printNewLines(2);
    printf(" ************************************************** ");
    printNewLines(1);
    if (flag == 'p' || flag == 'P')
    {
        printLoggedAs(flag);
    }
    else if (flag == 't' || flag == 'T')
    {
        printLoggedAs(flag);
    }
    else
    {
        printf(" *               You are not logged.              *");
    }

    printNewLines(1);
    printf(" ************************************************** ");
    printNewLines(2);
}