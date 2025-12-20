#ifndef PRODUCT_H
#define PRODUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "common.h"

// Comment here

typedef struct Product {
    char EAN[EAN_BUF];
    char productName[NAME_LENGTH];
    int quantity;
    double price;
    struct Product *next;
} Product;


// Check .c file for function explanations. 

Product *insertProduct(Product *head, char *EAN, char *productName, int quantity, double price);
int suggestProduct(Product *head, char *EAN);
int updateProduct(Product *head, char *EAN);
void printInventory(Product *head);

#endif 
