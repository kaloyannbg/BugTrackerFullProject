#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../main.h"

void printProgrammerMenu()
{
    printf(" -- Enter 1 to FIX SPECIFIC NEW REPORT (#BUG) -- ");
    printNewLines(1);
    printf(" -- Enter 2 to CHECK ALL REPORTS (#BUGS) -- ");
    printNewLines(1);
    printf(" -- Enter 3 to CHECK ALL REPORTS WITH STATUS NEW.(#NEW BUGS) -- ");
    printNewLines(1);
    printf(" -- Enter 4 to CHECK ALL REPORTS WITH STATUS FIXED.(#FIXED BUGS) -- ");
    printNewLines(1);
    printf(" -- Enter 5 to CHECK ALL REPORTS WITH STATUS CLOSED.(#CLOSED BUGS) -- ");
    printNewLines(1);
    printf(" -- Enter 6 to CHECK SPECIFIC REPORT (#BUG). -- ");
    printNewLines(1);
}