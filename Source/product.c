#include "product.h"

void printMenu_9(char *EAN){
    printf("\n================================================\n");
    printf("         INSERT / UPDATE PRODUCT\n");
    printf("================================================\n\n");
    printf("Enter product EAN: %s\n", EAN);
    printf("Product already exists.\n");
    printf("Enter quantity to add: ");
}

void printMenu_10(Product *head, char *EAN){
    printf("\n================================================\n");
    printf("         INSERT / UPDATE PRODUCT\n");
    printf("================================================\n\n");
    printf("Enter product EAN: %s\n", EAN);
    printf("EAN incomplete.\n");
    printf("\n================================================\n");
    printf("\nMatching products:\n");
    int count = 1;
    Product *temp = head;
    while(temp){
        if(strncmp(temp->EAN, EAN, strlen(EAN)) == 0){
            printf("%d) %s - %s\n", count, temp->EAN, temp->productName);
            ++count;
        }
        temp = temp->next;
    }
    printf("\nSelect product number or 0 to cancel: ");
}

void printMenu_11(){
    printf("\n================================================\n");
    printf("                 INVENTORY\n");
    printf("================================================\n");
    printf("\nEnter code, name, or * to print all (e.g. 123, Milk, *): ");
}

void printMenu_12(char *EAN){
    printf("\n================================================\n");
    printf("         INSERT / UPDATE PRODUCT\n");
    printf("================================================\n\n");
    printf("Enter product EAN: %s\n", EAN);
    printf("EAN incomplete.\n");
    printf("\n================================================\n");
    printf("\nNo matching products found!\n");
}

void stringToLower(char *strToLower, char *str){
    for(int i = 0; i < strlen(str); ++i){
        strToLower[i] = tolower(str[i]);
    }
}

void readQuantityToAdd(char *EAN, int *quantity){

    // Print menu.
    clearScreen();
    printMenu_6(EAN);

    // Check for valid Quantity.
    while(1){

        // Initialize string.
        char buffer[BUFFER_SIZE] = {' '};
        if (!fgets(buffer, BUFFER_SIZE, stdin)) {
            clearScreen();
            printf("\nInput error.\n");
            printMenu_6(EAN);
            continue;
        }

        // Check if we exceeded the BUFFER_SIZE.
        if(!strchr(buffer, '\n')){
            clearBuffer();
            clearScreen();
            printf("\nInvalid quantity. Please try again.\n");
            printMenu_6(EAN);
            continue;
        }

        // Skip whitespace in the beginning. 
        char *temp = buffer;
        while(isspace(*temp)) ++temp;

        // Check if it's a digit, if not just skip.
        if(!isdigit(*temp)){
            clearScreen();
            printf("\nInvalid quantity. Please try again.\n");
            printMenu_6(EAN);
            continue;
        }

        // Get the whole number.
        int index = 0;
        char tempValue[BUFFER_SIZE] = {' '};
        while(index < (BUFFER_SIZE - 1) && isdigit(*temp)){
            tempValue[index] = *temp;
            ++temp; ++index;
        }
        tempValue[index] = '\0';
        
        // Check if there's anything else after the number.
        while(isspace(*temp)) ++temp;
        if(*temp == '\0'){
            int length = strlen(tempValue);
            if(length >= QTY_MAX_DIGITS){
                clearScreen();
                printf("\nInvalid quantity. Please try again.\n");
                printMenu_6(EAN);
                continue;
            }
            *quantity = atoi(tempValue);
            return;
        } 
        clearScreen();
        printf("\nInvalid quantity. Please try again.\n");
        printMenu_6(EAN);
    }
}

void readProductNumber(Product *head, char *EAN, int totalProducts, int *productNumber){

    // Print menu.
    clearScreen();
    printMenu_7(head, EAN);

    // Check for valid Quantity.
    while(1){

        // Initialize string.
        char buffer[BUFFER_SIZE] = {' '};
        if (!fgets(buffer, BUFFER_SIZE, stdin)) {
            clearScreen();
            printf("\nInput error.\n");
            printMenu_7(head, EAN);
            continue;
        }

        // Check if we exceeded the BUFFER_SIZE.
        if(!strchr(buffer, '\n')){
            clearBuffer();
            clearScreen();
            printf("\nInvalid product number. Please try again.\n");
            printMenu_7(head, EAN);
            continue;
        }

        // Skip whitespace in the beginning. 
        char *temp = buffer;
        while(isspace(*temp)) ++temp;

        // Check if it's a digit, if not just skip.
        if(!isdigit(*temp)){
            clearScreen();
            printf("\nInvalid product number. Please try again.\n");
            printMenu_7(head, EAN);
            continue;
        }

        // Get the whole number.
        int index = 0;
        char tempValue[BUFFER_SIZE] = {' '};
        while(index < (BUFFER_SIZE - 1) && isdigit(*temp)){
            tempValue[index] = *temp;
            ++temp; ++index;
        }
        tempValue[index] = '\0';

        // Check if there's anything else after the number.
        while(isspace(*temp)) ++temp;
        if(*temp == '\0'){
            int tempProductNumber = atoi(tempValue);
            if(!(tempProductNumber >= 0 && tempProductNumber <= totalProducts)){
                clearScreen();
                printf("\nInvalid product number. Please try again.\n");
                printMenu_7(head, EAN);
                continue;
            }
            *productNumber = tempProductNumber;
            return;
        } 
        clearScreen();
        printf("\nInvalid product number. Please try again.\n");
        printMenu_7(head, EAN);
    }
}

void readOption(Product *head, char *option){

    // Print menu.
    clearScreen();
    printMenu_11();

    while(1){

        // Initialize string.
        char buffer[NAME_LENGTH] = {' '};
        if (!fgets(buffer, NAME_LENGTH, stdin)) {
            clearScreen();
            printf("\nInput error.\n");
            printMenu_11();
            continue;
        }

        // Check if we exceeded the NAME_LENGTH.
        if(!strchr(buffer, '\n')){
            clearBuffer();
            clearScreen();
            printf("\nInvalid statement! Please try again.\n");
            printMenu_11();
            continue;
        } 

        
        // Different message for when the string is empty.
        buffer[strlen(buffer) - 1] = '\0';
        char *temp = buffer;
        while(isspace(*temp)) ++temp;
        if(strlen(temp) < 1){
            clearScreen();
            printf("\nNo input provided. Please enter a code, name, or *.\n");
            printMenu_11();
            continue;
        }
        strcpy(option, temp);
        return;
    }
}

int updateProduct(Product *head, char *EAN){
    // Check if product already exists
    int quantity;
    Product *curr = head;
    while(curr){
        if(strcmp(curr->EAN, EAN) == 0){
            readQuantityToAdd(curr->EAN, &quantity);
            curr->quantity += quantity;
            printf("\n================================================\n");
            printf("\nProduct quantity updated. New quantity: %d\n", curr->quantity);
            return 1;
        }
        curr = curr->next;
    }
    return 0;
} 

int suggestProduct(Product *head, char *EAN){

    // Check if the length of the EAN is between (4 - 12).
    if(strlen(EAN) != 13){

        // Create an array of all the valid EANS.
        int count = 0;
        Product *temp = head;
        while(temp){
            temp = temp->next;
            ++count;
        }

        char **validEANS = (char**)malloc(sizeof(char*) * count);
        for(int i = 0; i < count; ++i){
            validEANS[i] = (char*)malloc(sizeof(char) * EAN_BUF);
        }

        // Store the valid EANS.
        temp = head;
        int totalEanCount = 0;
        while(temp){
            if(strncmp(EAN, temp->EAN, strlen(EAN)) == 0){
                strcpy(validEANS[totalEanCount], temp->EAN);
                ++totalEanCount;
            }
            temp = temp->next;
        }
        
        // If we have no matching products.
        if(!head || totalEanCount == 0){
            clearScreen();
            printMenu_12(EAN);
            return 0;
        }

        // Read a valid product number.
        int productNumber;
        readProductNumber(head, EAN, totalEanCount, &productNumber);
        if(productNumber == 0) return 0;
        
        // Find the EAN at that product number and paste onto our EAN.
        strcpy(EAN, validEANS[productNumber - 1]);
    } 
    return 1;
}

Product *insertProduct(Product *head, char *EAN, char *productName, int quantity, double price){
    
    // Allocate the new product we want to add to the list.
    Product *newNode = malloc(sizeof(Product));
    if(!newNode){
        printf("Malloc failed!\n");
        return head;
    }
    strcpy(newNode->EAN, EAN);
    strcpy(newNode->productName, productName);
    newNode->quantity = quantity;
    newNode->price = price;
    newNode->next = NULL;

    // Add product to the list, sorted by EAN (Looks better).
    
    // Check if list is empty, or if the new product has a smaller EAN than the head.
    if(head == NULL || strcmp(newNode->EAN, head->EAN) < 0){
        newNode->next = head;
        return newNode; // Return the new head.
    }

    // Otherwise.
    Product *curr = head;
    while(curr->next && strcmp(newNode->EAN, curr->next->EAN) > 0){
        curr = curr->next;
    }

    newNode->next = curr->next;
    curr->next = newNode;
    return head;
}

void printInventory(Product *head){

    // Table header.
    char option[NAME_LENGTH];
        
    // Read the option.
    readOption(head, option);
    int length = strlen(option);

    // Get the amount of products in the list.
    int totalProducts = 0;
    Product *temp = head;
    while(temp){
        ++totalProducts;
        temp = temp->next;
    } 

    // Print the product list.
    if(totalProducts == 0){
        printf("\n----------------------------------------------------------\n\n");
        printf("List is empty! Please insert some products.\n\n");
        printf("----------------------------------------------------------\n");
        return;
    }
    printf("\n%-13s %-15s %-10s %-10s\n", "EAN", "Name", "Quantity", "Price");
    printf("----------------------------------------------------------\n");
    if(strcmp(option, "*") == 0){
        Product *product = head;
        while(product){
            // Product row format.
            printf("%-13s %-15s %-10d %.2f\n",
                    product->EAN,
                    product->productName,
                    product->quantity,
                    product->price);
    
            product = product->next;
        }
    } else if(isdigit(option[0])){
        Product *product = head;
        while(product){
            if(strncmp(product->EAN, option, length) == 0){
                // Product row format.
                printf("%-13s %-15s %-10d %.2f\n",
                    product->EAN,
                    product->productName,
                    product->quantity,
                    product->price);

                }
            product = product->next;
        }
    } else {
        Product *product = head;
        char lowerOption[NAME_LENGTH] = {' '}, lowerProductName[NAME_LENGTH] = {' '};
        stringToLower(lowerOption, option);
        while(product){
            stringToLower(lowerProductName, product->productName);
            if(strncmp(lowerOption, lowerProductName, length) == 0){
                // Product row format.
                printf("%-13s %-15s %-10d %.2f\n",
                    product->EAN,
                    product->productName,
                    product->quantity,
                    product->price);

                }
            product = product->next;
        }
    }
    printf("----------------------------------------------------------\n");
}