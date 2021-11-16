#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "main.h"

int main(void)
{
    system("color 0B");
    char cMenuChoice = 0, cChar = 0;
    int iLoginChoice = 0, isCont = 0, isLog = -1; // [iLoginChoice 1 = programmer, 2 = tester]
    do
    {
        clearScreen();
        printCover(GUEST);
        printLoginChoice();
        countFileRows(DATABASE_FILE);
        printf(" -- Please, enter your choice: ");
        scanf("%d", &iLoginChoice);
        cChar = 0, isCont = 0, isLog = 0;
        clearScreen();
        printCover(GUEST);
        switch (iLoginChoice)
        {
        case PRIMARY_MENU_EXIT:
            printf(" -- Bye, bye! --");
            exit(0);
            break;
        case PRIMARY_MENU_PROGRAMMER:
            doLogIn(&regInstance, &loginInstance, PROGRAMMER, &isLog);

            if (isLog != true)
            {
                break;
            }
            do
            {
                clearScreen();
                printCover(PROGRAMMER);
                printNewLines(twoLines);
                printProgrammerMenu();
                printNewLines(twoLines);
                printf(" -- Please, enter your choice as PROGRAMMER: ");
                getCharFromAdress(&cMenuChoice);
                printNewLines(oneLine);
                itemsFromProgrammerMenu(cMenuChoice);
                printNewLines(oneLine);
                printLoginContinue(PROGRAMMER);
                getCharFromAdress(&cChar);
                isCont = isSessionContinue(&cChar);
                while (isCont == undefine)
                {
                    clearScreen();
                    printCover(PROGRAMMER);
                    printLoginContinue(TESTER);
                    getCharFromAdress(&cChar);
                    isCont = isSessionContinue(&cChar);
                }

            } while (isCont != false);  //if return false user is quit from his profile.

            break;
        case PRIMARY_MENU_TESTER:
            doLogIn(&regInstance, &loginInstance, TESTER, &isLog);

            if (isLog != true)
            {
                break;
            }
            do
            {
                clearScreen();
                printCover(TESTER);
                printNewLines(twoLines);
                printTesterMenu();
                printNewLines(twoLines);
                printf(" -- Please, enter your choice as TESTER: ");
                getCharFromAdress(&cMenuChoice);
                printNewLines(oneLine);
                itemsFromTesterMenu(cMenuChoice);
                printNewLines(oneLine);
                printLoginContinue(TESTER);
                getCharFromAdress(&cChar);
                isCont = isSessionContinue(&cChar);
                while (isCont == undefine)
                {
                    clearScreen();
                    printCover(TESTER);
                    printLoginContinue(TESTER);
                    getCharFromAdress(&cChar);
                    isCont = isSessionContinue(&cChar);
                }
            } while (isCont != false); //if return false user is quit from his profile.
            break;
        case 3:
            printNewLines(twoLines);
            getLoginDetailsFunc(&regInstance);
            printNewLines(twoLines);
            break;
        default:
            printf(" -- Invalid choice. Please try again! -- ");
            break;
        }

        printNewLines(twoLines);
    } while (iLoginChoice != PRIMARY_MENU_EXIT);

    freeStringsFromLoginStructure(&regInstance);

    return 0;
}