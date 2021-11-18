#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../main.h"

int isSessionContinue(char *charAdress)
{
    if (*charAdress == 'y' || *charAdress == 'Y')
    {
        return true;
    }
    else if (*charAdress == 'n' || *charAdress == 'N')
    {
        return false;
    }

    return undefine;
}

void putDetailsInStruct(char *buffer)
{
    char *dynBuffer = (string)malloc(strlen(buffer) + 1);
    strcpy(dynBuffer, buffer);
    loginInstance.user = (string)malloc(MAX_USERNAME_LENGTH);
    loginInstance.pass = (string)malloc(MAX_PASSWORD_LENGTH);

    int countStr = 0;
    char *token = strtok(dynBuffer, ",");
    while (token != NULL)
    {
        switch (countStr)
        {
        case USERNAME:
            strcpy(loginInstance.user, token);
            break;
        case PASSWORD:
            strcpy(loginInstance.pass, token);
            break;
        case USERTYPE:
            loginInstance.userType = atoi(token);
            break;
        default:
            break;
        }
        token = strtok(NULL, ",");
        countStr++;
    }
    free(dynBuffer);
}

void makeRegistration(LoginDetails *regInstance, LoginDetails *loginInstance)
{

    int fileRows = countFileRows(DATABASE_WITH_USERS);
    if (fileRows == 0)
    {
        fp = fopen(DATABASE_WITH_USERS, "w");
        char *putInFileArr = (string)calloc(MAX_USERNAME_AND_PASS_LENGTH, sizeof(char));
        stringUpperToLower(regInstance->user);
        sprintf(putInFileArr, "%s,%s,%d", regInstance->user, regInstance->pass, regInstance->userType);
        fprintf(fp, "%s\n", putInFileArr);
        fclose(fp);
        free(putInFileArr);
        freeStringsFromLoginStructure(regInstance);
        printNewLines(oneLine);
        printf(" -- Succesfully registration! -- ");
        printNewLines(oneLine);
        makePause();
        return;
    }

    LoginDetails *arrayOfUsers = (LoginDetails *)malloc(fileRows * sizeof(LoginDetails));
    char buffer[MAX_USERNAME_AND_PASS_LENGTH] = {0};
    fp = fopen(DATABASE_WITH_USERS, "r");
    for (int i = 0; i < fileRows; i++)
    {
        fgets(buffer, MAX_USERNAME_AND_PASS_LENGTH, fp);
        putDetailsInStruct(buffer);
        arrayOfUsers[i] = *loginInstance;
    }
    fclose(fp);
    for (int i = 0; i < fileRows; i++)
    {
        if (strcmp(arrayOfUsers[i].user, regInstance->user) == 0)
        {
            printf(" -- Sorry, but this name is already taken. --");
            printNewLines(oneLine);
            freeStringsFromLoginStructure(regInstance);
            freeArrayOfLoginStructs(fileRows, arrayOfUsers);
            return;
        }
    }

    fp = fopen(DATABASE_WITH_USERS, "a+");
    char *putInFileArr = (string)calloc(MAX_USERNAME_AND_PASS_LENGTH, sizeof(char));
    stringUpperToLower(regInstance->user);
    sprintf(putInFileArr, "%s,%s,%d", regInstance->user, regInstance->pass, regInstance->userType);
    fprintf(fp, "%s\n", putInFileArr);
    fclose(fp);
    free(putInFileArr);
    printNewLines(oneLine);
    printf(" -- Succesfully registration! -- ");
    printNewLines(oneLine);
    makePause();
    freeStringsFromLoginStructure(regInstance);
    freeArrayOfLoginStructs(fileRows, arrayOfUsers);
}

void getLoginDetailsFunc(LoginDetails *regInstance)
{
    createFileIfNotExist(DATABASE_WITH_USERS);
    printf(" -- USER REQUIRMENTS: USERNAME CAN BE ONLY LETTERS | Min letters: 4 | Max letters: 20");
    printNewLines(oneLine);
    printf(" -- PASS REQUIRMENTS: PASSWORD CAN BE ONLY DIGITS  | Min digits: 5 | Max digits: 20");
    printNewLines(oneLine);

    printf(" -- Register new programmer/tester");
    printNewLines(twoLines);
    printf(" -- Please enter your username: ");
    char buffer[MAX_USERNAME_LENGTH] = {0}; // username max length and password max length is equal = 32;
    getStrFromAdress(buffer);
    if (isUsernameValid(buffer) == 0)
    {
        printf(" -- Your username can have only letters! -- ");
        printNewLines(oneLine);
        makePause();
        return;
    }
    else if (isUsernameValid(buffer) == -1)
    {
        printf(" -- Username: Min. length 4 symbols , Max. length 20 symbols");
        printNewLines(oneLine);
        makePause();
        return;
    }
    regInstance->user = (string)malloc(strlen(buffer) + 1);
    strcpy(regInstance->user, buffer);
    printf(" -- Please enter your password: ");
    getPassword(buffer, MAX_PASSWORD_LENGTH);
    printNewLines(oneLine);
    if (isPasswordValid(buffer) == 0)
    {
        printf(" -- Your password can have only digits! -- ");
        printNewLines(oneLine);
        makePause();
        return;
    }
    else if (isPasswordValid(buffer) == -1)
    {
        printf(" -- Password: Min. length 5 digits , Max. length 20 symbols");
        printNewLines(oneLine);
        makePause();
        return;
    }
    regInstance->pass = (string)malloc(strlen(buffer) + 1);
    strcpy(regInstance->pass, buffer);
    printf(" -- Type 1 for programmer | Type 2 for tester: ");
    scanf("%d", &regInstance->userType);
    if (regInstance->userType != 1 && regInstance->userType != 2)
    {
        printf(" -- Sorry, but your choice is not valid! -- ");
        makePause();
        printNewLines(oneLine);
        return;
    }
    makeRegistration(regInstance, &loginInstance);
}

void doLogIn(LoginDetails *regInstance, LoginDetails *loginInstance, enUserType flag, int *isLogAdress) // flag 1 programmer, flag 2 tester
{
    createFileIfNotExist(DATABASE_WITH_USERS);

    char *buffer = (string)calloc(MAX_USERNAME_AND_PASS_LENGTH, sizeof(char));
    printf(" -- Username: ");
    getStrFromAdress(buffer);
    regInstance->user = (string)malloc(strlen(buffer) + 1);
    strcpy(regInstance->user, buffer);
    printf(" -- Password: ");
    getPassword(buffer, MAX_USERNAME_AND_PASS_LENGTH);
    printNewLines(oneLine);
    regInstance->pass = (string)malloc(strlen(buffer) + 1);
    strcpy(regInstance->pass, buffer);
    int fileRows = countFileRows(DATABASE_WITH_USERS);
    if (fileRows == 0)
    {
        printf(" -- WE DON\'T HAVE REGISTERED TESTERS/PROGRAMMERS, YOU CAN BE FIRST! ");
        freeStringsFromLoginStructure(regInstance);
        free(buffer);
        *isLogAdress = 0;
        printNewLines(oneLine);
        makePause();
        return;
    }

    LoginDetails *arrayOfUsers = (LoginDetails *)malloc(fileRows * sizeof(LoginDetails));
    fp = fopen(DATABASE_WITH_USERS, "r");
    for (int i = 0; i < fileRows; i++)
    {
        fgets(buffer, MAX_USERNAME_AND_PASS_LENGTH, fp);
        putDetailsInStruct(buffer);
        arrayOfUsers[i] = *loginInstance;
    }
    fclose(fp);
    stringUpperToLower(regInstance->user);
    for (int i = 0; i < fileRows; i++)
    {
        if ((strcmp(arrayOfUsers[i].user, regInstance->user) == 0) && (strcmp(arrayOfUsers[i].pass, regInstance->pass) == 0) && (arrayOfUsers[i].userType == flag)) //  && strcmp(arrayOfUsers[i].pass, regInstance->pass) == 0 && arrayOfUsers[i] .userType == flag
        {
            printf(" -- Hello, %s. --", regInstance->user);
            printNewLines(oneLine);
            *isLogAdress = 1;
            freeArrayOfLoginStructs(fileRows, arrayOfUsers);
            free(buffer);
            makePause();
            return;
        }
    }

    printf(" -- Wrong username, password or user type -- ");
    printNewLines(oneLine);
    *isLogAdress = 0;
    freeArrayOfLoginStructs(fileRows, arrayOfUsers);
    free(buffer);
    makePause();
}