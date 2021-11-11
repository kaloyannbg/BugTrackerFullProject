#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "main.h"
//#define DATABASE_FILE "DB.csv"

int main(void)
{
    system("color 0B");
    char cLoginChoice = 0, cMenuChoice = 0, cChar = 0; // [cLoginChoice 1 = programmer, 2 = tester]
    int isCont = 0;
    do
    {
        clearScreen();
        printCover('N');
        printLoginChoice();
        countFileRows(DATABASE_FILE);
        printf(" -- Please, enter your choice: ");
        getCharFromAdress(&cLoginChoice);
        cChar = 0, isCont = 0;
        switch (cLoginChoice)
        {
        case '0':
            clearScreen();
            printCover('N');
            printf(" -- Bye, bye! --");
            exit(0);
            break;
        case '1':
            do
            {
                clearScreen();
                printCover('P');
                printNewLines(2);
                printProgrammerMenu();
                printNewLines(2);
                printf(" -- Please, enter your choice as PROGRAMMER: ");
                getCharFromAdress(&cMenuChoice);
                printNewLines(1);
                itemsFromProgrammerMenu(cMenuChoice);
                printNewLines(1);
                printLoginContinue('P');
                getCharFromAdress(&cChar);
                isCont = isSessionContinue(&cChar);
                while (isCont == -1)
                {
                    clearScreen();
                    printCover('P');
                    printLoginContinue('P');
                    getCharFromAdress(&cChar);
                    isCont = isSessionContinue(&cChar);
                }
            } while (isCont != 0);

            break;
        case '2':
            do
            {
                clearScreen();
                printCover('T');
                printNewLines(2);
                printTesterMenu();
                printNewLines(2);
                printf(" -- Please, enter your choice as TESTER: ");
                getCharFromAdress(&cMenuChoice);
                printNewLines(1);
                itemsFromTesterMenu(cMenuChoice);
                printNewLines(1);
                printLoginContinue('T');
                getCharFromAdress(&cChar);
                isCont = isSessionContinue(&cChar);
                while (isCont == -1)
                {
                    clearScreen();
                    printCover('T');
                    printLoginContinue('T');
                    getCharFromAdress(&cChar);
                    isCont = isSessionContinue(&cChar);
                }
            } while (isCont != 0);
            break;
        default:
            printf(" -- Invalid choice. Please try again! -- ");
            break;
        }

        printNewLines(2);
    } while (cLoginChoice != '0');

    return 0;
}