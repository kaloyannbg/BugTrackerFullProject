#include <stdio.h>
#include <stdlib.h>
#include "headers/defineFile.h"
#include "headers/structFile.h"

FILE *fp; // ЗАЩО НЕ ТРЯБВА ДА Е NULL, КОДА ГЪРМИ
FILE *fTemp;

// CONSTANTS
void printLoginChoice();
void printCover(enUserType flag);
void printTesterMenu();
void printProgrammerMenu();
void printLoggedAs(enUserType flag); // да се поправи на енъм
void printReports(enPrintType flag); // да се поправи на енъм
void printParsedStruct(bugReport *report);
void printLoginContinue(enUserType flag); // p or P for programmer, t or T for tester // да се поправи на енъм

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
void checkReport();
void getShortDesc(char *sShortDesc);
void getDesc(char *sDesc);
void itemsFromProgrammerMenu(char c);
void fixReport();
// END [FUNCTIONS/ItemsFromTesterMenu.c]

// START [FUNCTIONS/memoryFunctions.c]
void free2DArrFromMemory(char **array, int size);
void freeStrings(bugReport *report);
void freeArrayOfStructs(int rowsInFile, bugReport *arrayOfStructs);
void freeArrayOfLoginStructs(int rowsInFile, LoginDetails *arrayOfStructs);
void freeStringsFromLoginStructure(LoginDetails *details);
// END [FUNCTIONS/memoryFunctions.c]

// START [FUNCTIONS/fileFunctions.c]
int isFileExist(char *fileName);
void createFileIfNotExist(char *fileName);
int countFileRows(char *fileName);
int isRowExist(int row, char *fileName);
void getRowByIDIfExist(int row, char *fileName, char *out);
int changeRow(char *replaceFile, char *withFile, char *rowToReplace, char *newRow);
// END [FUNCTIONS/fileFunctions.c]

// START [FUNCTIONS/stringFunctions.c]
char changeCharInArr(char *inputArr, char cChar, char toChar);
void getSentence(char *inputArr, int minLimit, int maxLimit);
void getStrFromAdress(char *str);
char stringUpperToLower(char *arr);
// END [FUNCTIONS/stringFunctions.c]

// START [FUNCTIONS/login.c]
int isSessionContinue(char *charAdress);
void getLoginDetailsFunc(LoginDetails *regInstance);
int isUsernameValid(char *username);
int isPasswordValid(char *password);
void doLogIn(LoginDetails *regInstance, LoginDetails *loginInstance, enUserType flag, int *isLogAdress); // flag 1 programmer, flag 2 tester
// END [FUNCTIONS/login.c]