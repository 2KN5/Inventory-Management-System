#include "printMenus.h"


void printMenu_1(){
    printf("\n===== Inventory Management System =====\n\n");
    printf("1. Insert / Update Product\n");
    printf("2. Insert New Order\n");
    printf("3. Print Inventory\n");
    printf("4. Execute Orders\n");
    printf("5. Exit\n");
    printf("Select option: ");
}

void printMenu_2(){
    printf("\n=======================================\n\n");
    printf("Enter product EAN: ");
}

void printMenu_3(char *EAN){
    printf("\n=======================================\n\n");
    printf("Enter product EAN: %s\n", EAN);
    printf("Enter product name: ");
}

void printMenu_4(char *EAN, char *productName){
    printf("\n=======================================\n\n");
    printf("Enter product EAN: %s\n", EAN);
    printf("Enter product name: %s\n", productName);
    printf("Enter quantity: ");
}

void printMenu_5(char *EAN, char *productName, int quantity){
    printf("\n=======================================\n\n");
    printf("Enter product EAN: %s\n", EAN);
    printf("Enter product name: %s\n", productName);
    printf("Enter quantity: %d\n", quantity);
    printf("Enter price: ");
}
