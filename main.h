#ifndef TEST
#define TEST
//CONSTANTS
//
void printLoginChoice();
void printCover();
void printTesterMenu();
void printProgrammerMenu();
void printLoggedAsTester();
void printLoggedAsProgrammer();
void printAllReports();

// START [FUNCTIONS GLOBAL.C]
void getInt(int *var);
void getCharFromAdress(char *c);
void printNewLines(int count);
void clearScreen();
void makePause();
// END [FUNCTIONS GLOBAL.C]

// START [FUNCTIONS CHECKFUNCTIONS.C]
int isDigit(char c);
int isLetter(char c);
// END [FUNCTIONS CHECKFUNCTIONS.C]

// START [FUNCTIONS/ItemsFromTesterMenu.c]
void itemsFromTesterMenu(char c);
void createNewReport();
void getShortDesc(char *sShortDesc);
void getDesc(char *sDesc);
// END [FUNCTIONS/ItemsFromTesterMenu.c]

// START [FUNCTIONS/memoryFunctions.c]

// END [FUNCTIONS/memoryFunctions.c]

// START [FUNCTIONS/fileFunctions.c]
int isFileExist(char *fileName);
void createFileIfNotExist(char *fileName);
int countFileRows(char *fileName);
// END [FUNCTIONS/fileFunctions.c]

// START [FUNCTIONS/stringFunctions.c]
void printStringFromSecondElement(char *str);
void printStringTildaToComma(char *str);
// END [FUNCTIONS/stringFunctions.c]

#endif