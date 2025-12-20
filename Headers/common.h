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

#define EAN_BUF 15
#define NAME_LENGTH 32
#define BUFFER_SIZE 64
#define CUSTOMER_CODE_LEN 10

#define OPTION_MAX 5
#define OPTION_MIN 1

#define EAN_MAX_DIGITS 13
#define EAN_MIN_DIGITS 4

#define PRIORITY_MIN 1
#define PRIORITY_MAX 10

#define QTY_MAX_DIGITS 10

#endif 
