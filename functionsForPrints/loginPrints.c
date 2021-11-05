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

void printLoggedAsTester()
{
    printf(" -- You are logged as: Tester -- ");
}

void printLoggedAsProgrammer()
{
    printf(" -- You are logged as: Programmer -- ");
}
