#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "common.h"
#include "product.h"
#include "orderQueue.h"

// Check .c file for function explanations. 

void mainMenu(int *number);
void runMS(int option, Product **inventory, OrderBucket *ob);

void freeInventory(Product *inventory);

#endif 
