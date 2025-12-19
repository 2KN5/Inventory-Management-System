#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "common.h"
#include "product.h"

// Check .c file for function explanations. 

void mainMenu(int *number);
void readProductName(char *EAN, char *str);
int runMS(int option, Product **inventory);

void clearScreen();
void pause();

#endif 
