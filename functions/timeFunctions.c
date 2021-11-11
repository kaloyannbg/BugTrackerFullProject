#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../main.h"
char getCurrentTime(char *out) //save current time in 'out' array
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);  
    memset(out, '\0', DATE_LENGTH);

    sprintf(out, "%d-%d-%d %d:%d:%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

}