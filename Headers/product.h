#ifndef PRODUCT_H
#define PRODUCT_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

// Linked list for inventory products with EAN, name, quantity, and price.
typedef struct Product {
    char EAN[EAN_BUF];
    char productName[NAME_LENGTH];
    int quantity;
    double price;
    struct Product *next;
} Product;

// Check .c file for function explanations. 

void printInventory(MenuParameters *par, Product *head);
int updateProduct(MenuParameters *par, Product *head, char *EAN);
int suggestProduct(MenuParameters *par, Product *head, char *EAN);
Product *insertProduct(Product *head, char *EAN, char *productName, int quantity, double price);

#endif 
