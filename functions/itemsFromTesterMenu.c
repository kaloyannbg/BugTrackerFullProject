#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../main.h"

void itemsFromTesterMenu(char c)
{
    switch (c)
    {
    case '1':
        printf(" -- CHECK ALL REPORTS. (#BUGS) --");
        printNewLines(1);
        printAllReports();
        break;
    case '2':
        printf(" -- CREATE NEW REPORT. (#BUG). --");
        printNewLines(1);
        createNewReport();
        break;
    case '3':
        printf(" -- CHECK SPECIFIC REPORT (#BUG).  --");
        break;

    default: (" -- You choosed invalid item from tester menu. ");
        break;
    }
}