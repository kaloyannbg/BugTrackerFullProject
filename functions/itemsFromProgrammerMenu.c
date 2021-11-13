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
        printNewLines(1);
        fixReport();
        break;
    case '2':
        printf(" -- CHECK ALL REPORTS (#BUGS) --");
        printNewLines(1);
        printReports('A', &newReport);
        break;
    case '3':
        printf(" --  CHECK ALL REPORTS WITH STATUS NEW.(#NEW BUGS) --");
        printNewLines(1);
        printReports('N', &newReport);
        break;
    case '4':
        printf(" --  CHECK ALL REPORTS WITH STATUS FIXED.(#FIXED BUGS) --");
        printNewLines(1);
        printReports('F', &newReport);
        break;
    case '5':
        printf(" --  CHECK ALL REPORTS WITH STATUS CLOSED.(#CLOSED BUGS) --");
        printNewLines(1);
        printReports('C', &newReport);
        break;
    case '6':
        printf(" -- CHECK SPECIFIC REPORT (#BUG).  --");
        printNewLines(1);
        checkReport();
        break;

    default:
        (" -- You choosed invalid item from programmer menu. ");
        break;
    }
}