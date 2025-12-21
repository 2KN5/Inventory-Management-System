#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

// Forward declarations to avoid circular dependencies.
typedef struct Product Product;
typedef struct OrderBucket OrderBucket;

// Check .c file for function explanations. 

void mainMenu(int *number);
void freeInventory(Product *inventory);
void runMS(int option, Product **inventory, OrderBucket *ob, MenuParameters *par);
int isValidBuffer(void (*printMenu)(MenuParameters*), MenuParameters *par, char *buffer, int bufferSize);

#endif