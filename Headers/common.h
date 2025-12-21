#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>

// Clear the screen.
static inline void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Pause system (Made for debugging).
static inline void pause(){
    printf("\nPress ENTER to continue...");
    getchar();
}

// Clear input.
static inline void clearBuffer(){
    int ch;
    while((ch = getchar()) != '\n' && ch != EOF);
}

// Definitions.

#define EAN_BUF 15
#define NAME_LENGTH 32
#define BUFFER_SIZE 64
#define ERROR_MSG_MAX 100
#define CUSTOMER_CODE_LEN 20

#define MAX_ITEMS 200

#define OPTION_MIN 1
#define OPTION_MAX 5

#define EAN_MIN_DIGITS 4
#define EAN_MAX_DIGITS 13

#define PRIORITY_MIN 1
#define PRIORITY_MAX 10

#define QTY_MAX_DIGITS 10

// Container for all UI parameters.
// Define here since it's used across ALL menu input validation functions.
typedef struct MenuParameters {

    // Customer info.
    char customerCode[CUSTOMER_CODE_LEN];
    char customerName[NAME_LENGTH];
    
    // Product info.
    char EAN[EAN_BUF];
    char productName[NAME_LENGTH];
    
    // Order info.
    int priority;
    int count;  
    int quantity;
    double price;
    
    // For error messages.
    char errorMsg[ERROR_MSG_MAX];

} MenuParameters;

#endif