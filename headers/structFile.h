#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "enumFile.h"

typedef char *string;
typedef unsigned long long int int_ut;
typedef long long int int_t;

typedef struct // WE DEFINE TYPE OF TYPE STRUCTURE
{
    int_ut uniqueID;    //     1. UNIQUE ID NUMBER
    string sShortDesc;                   //     2. SHORT DESCRIPTION
    string sDesc;                        //     3. DESCRIPTION
    time_t sDateOfCreation;             //     4. DATE OF CREATION(current date)
    time_t sDateOfFixed;                //     5. DATE OF FIXED = 0 HERE
    time_t sDateOfClosed;               //     6. DATE OF CLOSED = 0 HERE
    string sTester;                      //     7. Tester NICKNAME
    string sProgrammer;                  //     8. Programmer NICKNAME
    enum StatusOfReport statusOfReport; //     9. STATUS : NEW | FIXED | CLOSED

} bugReport; // AND GIVE NAME HIM BUG REPORT

bugReport newReport; // with extern in c file където ще го ползвам да инклудна хедъра , тук ще е екстърн

typedef struct
{
    string user;
    string pass;
    enum eUserType userType;
} LoginDetails;

LoginDetails loginInstance; // with extern in c file където ще го ползвам да инклудна хедъра , тук ще е екстърн
LoginDetails regInstance; // with extern in c file където ще го ползвам да инклудна хедъра , тук ще е екстърн
