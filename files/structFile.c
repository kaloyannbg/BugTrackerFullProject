#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

enum StatusOfReport
{
    NEW = 1,
    FIXED,
    CLOSED
};

typedef struct // WE DEFINE TYPE OF TYPE STRUCTURE
{
    unsigned long long int uniqueID;    //     1. UNIQUE ID NUMBER
    char *sShortDesc;                   //     2. SHORT DESCRIPTION
    char *sDesc;                        //     3. DESCRIPTION
    time_t sDateOfCreation;             //     4. DATE OF CREATION(current date)
    time_t sDateOfFixed;                //     5. DATE OF FIXED = 0 HERE
    time_t sDateOfClosed;               //     6. DATE OF CLOSED = 0 HERE
    char *lastWriteInReport;            //     7. LAST WRITER IN REPORT : TESTER OR PROGRAMMER
    enum StatusOfReport statusOfReport; //     8. STATUS : NEW | FIXED | CLOSED

} bugReport; // AND GIVE NAME HIM BUG REPORT

bugReport newReport;