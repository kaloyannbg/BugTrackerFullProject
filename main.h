#include <stdio.h>
#include <stdlib.h>
#include "headers/defineFile.h"
#include "headers/structFile.h"


FILE *fp;
FILE *fTemp;

// CONSTANTS
//
void printLoginChoice();
void printCover(char flag);
void printTesterMenu();
void printProgrammerMenu();
void printLoggedAs(char flag);
void printReports(char flag, bugReport *report);
void printParsedStruct(bugReport *report);
void printLoginContinue(char flag); // p or P for programmer, t or T for tester

// START [FUNCTIONS GLOBAL.C]
char charToInt(char c);
void getInt(int *var);
void getCharFromAdress(char *c);
void printNewLines(int count);
void clearScreen();
void makePause();
// END [FUNCTIONS GLOBAL.C]

// START [FUNCTIONS CHECKFUNCTIONS.C]
int countDigits(int num);
int isDigit(char c);
int isLetter(char c);
int isContinue();
// END [FUNCTIONS CHECKFUNCTIONS.C]

// START [FUNCTIONS/ItemsFromTesterMenu.c]
void itemsFromTesterMenu(char c);
void createNewReport();
void verifyReport();
void getShortDesc(char *sShortDesc);
void getDesc(char *sDesc);

void itemsFromProgrammerMenu(char c);
void fixReport();
// END [FUNCTIONS/ItemsFromTesterMenu.c]

// START [FUNCTIONS/memoryFunctions.c]
void free2DArrFromMemory(char **array, int size);
void freeStrings(bugReport *report);
// END [FUNCTIONS/memoryFunctions.c]

// START [FUNCTIONS/fileFunctions.c]
int isFileExist(char *fileName);
void createFileIfNotExist(char *fileName);
int countFileRows(char *fileName);
int isRowExist(int row, char *fileName);
void getRowByIDIfExist(int row, char *fileName, char *out);
int rewriteFileWithOneRow(char *replaceFile, char *withFile, char *rowToReplace, char *newRow);
// END [FUNCTIONS/fileFunctions.c]

// START [FUNCTIONS/stringFunctions.c]
char changeCharInArr(char *inputArr, char cChar, char toChar);
void getSentence(char *inputArr, int minLimit, int maxLimit);
void getStrFromAdress(char *str);
// END [FUNCTIONS/stringFunctions.c]

// START [FUNCTIONS/timeFunctions.c]
char getCurrentTime(char *out); // save current time in 'out' array
// END [FUNCTIONS/timeFunctions.c]

// START [FUNCTIONS/login.c]
int isSessionContinue(char *charAdress);
// END [FUNCTIONS/login.c]