#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../main.h"

void printTesterMenu()
{
    printf(" -- Enter 1 to CREATE NEW REPORT. (#BUG). -- ");
    printNewLines(oneLine);
    printf(" -- Enter 2 to VERIFY SPECIFIC REPORT (#BUG). -- ");
    printNewLines(oneLine);
    printf(" -- Enter 3 to CHECK ALL REPORTS. (#BUGS) -- ");
    printNewLines(oneLine);
    printf(" -- Enter 4 to CHECK ALL REPORTS WITH STATUS NEW.(#NEW BUGS) -- ");
    printNewLines(oneLine);
    printf(" -- Enter 5 to CHECK ALL REPORTS WITH STATUS FIXED.(#FIXED BUGS) -- ");
    printNewLines(oneLine);
    printf(" -- Enter 6 to CHECK ALL REPORTS WITH STATUS CLOSED.(#CLOSED BUGS) -- ");
    printNewLines(oneLine);
    printf(" -- Enter 7 to CHECK SPECIFIC REPORT (#BUG). -- ");
    printNewLines(oneLine);
    printf(" -- Enter 8 to PRINT REVERSED LIST OF BUGS (#BUGS). --");
    printNewLines(oneLine);
}