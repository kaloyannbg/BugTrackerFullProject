#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../main.h"

void itemsFromProgrammerMenu(char c)
{
    switch (c)
    {
    case '1':
        printf(" -- FIX SPECIFIC NEW REPORT (#BUG). --");
        printNewLines(oneLine);
        fixReport();
        break;
    case '2':
        printf(" -- CHECK ALL REPORTS (#BUGS) --");
        printNewLines(oneLine);
        printReports(REGULAR_TYPE);
        break;
    case '3':
        printf(" --  CHECK ALL REPORTS WITH STATUS NEW.(#NEW BUGS) --");
        printNewLines(oneLine);
        printReports(NEW_TYPE);
        break;
    case '4':
        printf(" --  CHECK ALL REPORTS WITH STATUS FIXED.(#FIXED BUGS) --");
        printNewLines(oneLine);
        printReports(FIXED_TYPE);
        break;
    case '5':
        printf(" --  CHECK ALL REPORTS WITH STATUS CLOSED.(#CLOSED BUGS) --");
        printNewLines(oneLine);
        printReports(CLOSED_TYPE);
        break;
    case '6':
        printf(" -- CHECK SPECIFIC REPORT (#BUG).  --");
        printNewLines(oneLine);
        checkReport();
        break;
    case '7':
        printf(" -- PRINT REVERSED LIST OF BUGS (#BUGS).  --");
        printNewLines(oneLine);
        printReports(REVERSED_TYPE);
        break;
    default:
        (" -- You choosed invalid item from programmer menu. ");
        break;
    }
}