#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "main.h"

int main(void)
{
    char cLoginChoice = 0, cTesterMenuChoice = 0; // [cLoginChoice 1 = programmer, 2 = tester]

    do
    {
        clearScreen();
        printCover();
        printLoginChoice();
        char file[50] = "DB.csv";
        countFileRows(file);
        printf(" -- Please, enter your choice: ");
        getCharFromAdress(&cLoginChoice);
        switch (cLoginChoice)
        {
        case '0':
            clearScreen();
            printCover();
            printf(" -- Bye, bye! --");
            exit(0);
            break;
        case '1':
            clearScreen();
            printCover();
            printLoggedAsProgrammer();
            printNewLines(2);
            printProgrammerMenu();
            break;
        case '2':
            clearScreen();
            printCover();
            printLoggedAsTester();
            printNewLines(2);
            printTesterMenu();
            printNewLines(2);
            printf(" -- Please, enter your choice as tester: ");
            getCharFromAdress(&cTesterMenuChoice);
            printNewLines(1);
            itemsFromTesterMenu(cTesterMenuChoice);
            break;
        default:
            printf(" -- Invalid choice. Please try again! -- ");
            break;
        }

        printNewLines(2);
        makePause();
    } while (cLoginChoice != '0');

    return 0;
}