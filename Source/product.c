#include "product.h"
#include "utils.h" 

// PRINT MENUs START.

void printMenu_9(MenuParameters *par){
    printf("\n================================================\n");
    printf("         INSERT / UPDATE PRODUCT\n");
    printf("================================================\n\n");
    printf("Enter product EAN: %s\n", par->EAN);
    printf("Product already exists.\n");
    printf("Enter quantity to add: ");
}

// -> MENU 10 START.
void printMenu_10_Par(MenuParameters *par){
    printf("\n================================================\n");
    printf("         INSERT / UPDATE PRODUCT\n");
    printf("================================================\n\n");
    printf("Enter product EAN: %s\n", par->EAN);
    printf("EAN incomplete.\n");
    printf("\n================================================\n");
    printf("\nMatching products:\n");
}

void printMenu_10_MP(Product *head, char *EAN){
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

void printMenu_10(MenuParameters *par, Product *head){
    printMenu_10_Par(par);
    printMenu_10_MP(head, par->EAN);
}
// -> MENU 10 END.

void printMenu_11(MenuParameters *par){
    printf("\n================================================\n");
    printf("                 INVENTORY\n");
    printf("================================================\n");
    printf("\nEnter code, name, or * to print all (e.g. 123, Milk, *): ");
}

void printMenu_12(MenuParameters *par){
    printf("\n================================================\n");
    printf("         INSERT / UPDATE PRODUCT\n");
    printf("================================================\n\n");
    printf("Enter product EAN: %s\n", par->EAN);
    printf("EAN incomplete.\n");
    printf("\n================================================\n");
    printf("\nNo matching products found!\n");
}

// PRINT MENUs END.

// Inserts new product into inventory list sorted by EAN for organized display.
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

    // Add product to the list, sorted by EAN (Looks better for print).
    
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

    // Place newNode in the list and return the head.
    newNode->next = curr->next;
    curr->next = newNode;
    return head;
}

// Convert all characters of a string to lower.
void stringToLower(char *strToLower, char *str){
    for(int i = 0; i < strlen(str); ++i){
        strToLower[i] = tolower(str[i]);
    }
}

// Gets additional quantity for existing product.
void readQuantityToAdd(MenuParameters *par, char *EAN, int *quantity){

    // Initialize parameters.
    strcpy(par->errorMsg, "\nInvalid quantity. Please try again.\n");
    strcpy(par->EAN, EAN);

    // Print menu.
    clearScreen();
    printMenu_9(par);

    // Check for valid quantity, positive only and less than QTY_MAX_DIGITS.
    while(1){

        // Initialize string.
        char buffer[BUFFER_SIZE] = {' '};
        if(!isValidBuffer(printMenu_9, par, buffer, sizeof(buffer))) continue;
        
        // Skip whitespace in the beginning. 
        char *temp = buffer;
        while(isspace(*temp)) ++temp;

        // Check if it's a digit, if not just skip.
        if(!isdigit(*temp)){
            clearScreen();
            printf("%s", par->errorMsg);
            printMenu_9(par);
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
                printf("%s", par->errorMsg);
                printMenu_9(par);
                continue;
            }
            *quantity = atoi(tempValue);
            return;
        } 
        clearScreen();
        printf("%s", par->errorMsg);
        printMenu_9(par);
    }
}

// Validates option number Based On Number of (valid) EANS.
// Our number of valid EANS is totalProducts.
void readOption_BONE(MenuParameters *par, Product *head, char *EAN, int totalProducts, int *productNumber){

    // Initialize parameters.
    strcpy(par->errorMsg, "\nInvalid product number. Please try again.\n");
    strcpy(par->EAN, EAN);

    // Print menu.
    clearScreen();
    printMenu_10(par, head);

    // Get valid option number, in the range of -> (1 - totalProducts).
    while(1){

        // We dont use the function isValidBuffer here.
        // Since printMenu_10(), has 2 parameters.

        // Initialize string.
        char buffer[BUFFER_SIZE] = {' '};
        // Get input and check for input errors.
        if (!fgets(buffer, BUFFER_SIZE, stdin)) {
            clearScreen();
            printf("\nInput error.\n");
            printMenu_10(par, head);
            continue;
        }

        // Check if we exceeded the bufferSize.
        if(!strchr(buffer, '\n')){
            clearBuffer();
            clearScreen();
            printf("%s", par->errorMsg);
            printMenu_10(par, head);
            continue;
        }    

        // Skip whitespace in the beginning. 
        char *temp = buffer;
        while(isspace(*temp)) ++temp;

        // Check if it's a digit, if not just skip.
        if(!isdigit(*temp)){
            clearScreen();
            printf("%s", par->errorMsg);
            printMenu_10(par, head);
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
                printf("%s", par->errorMsg);
                printMenu_10(par, head);
                continue;
            }
            *productNumber = tempProductNumber;
            return;
        } 
        clearScreen();
        printf("%s", par->errorMsg);
        printMenu_10(par, head);
    }
}

// Gets inventory search filter.
// Input validation [Code, Name, or (*)] is done within the printInventory() function.
void readOption_PRINT(MenuParameters *par, Product *head, char *option){

    // Initialize parameters.
    strcpy(par->errorMsg, "\nInvalid statement! Please try again.\n");

    // Print menu.
    clearScreen();
    printMenu_11(par);

    // Get non-empty option.
    while(1){

        // Initialize string.
        char buffer[NAME_LENGTH] = {' '};
        if(!isValidBuffer(printMenu_11, par, buffer, sizeof(buffer))) continue;
        
        // Different message for when the string is empty.
        buffer[strlen(buffer) - 1] = '\0';
        char *temp = buffer;
        while(isspace(*temp)) ++temp;
        if(strlen(temp) < 1){
            clearScreen();
            printf("\nNo input provided. Please enter a code, name, or *.\n");
            printMenu_11(par);
            continue;
        }
        strcpy(option, temp);
        return;
    }
}

// Scan if product already exists and update.
int updateProduct(MenuParameters *par, Product *head, char *EAN){
    int quantity;
    Product *curr = head;
    while(curr){
        if(strcmp(curr->EAN, EAN) == 0){
            readQuantityToAdd(par, curr->EAN, &quantity);
            curr->quantity += quantity;
            printf("\n================================================\n");
            printf("\nProduct quantity updated. New quantity: %d\n", curr->quantity);
            return 1;
        }
        curr = curr->next;
    }
    return 0;
} 

// Suggests matching products for incomplete EAN and allows user selection.
int suggestProduct(MenuParameters *par, Product *head, char *EAN){

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
            strcpy(par->EAN, EAN);
            printMenu_12(par);
            return 0;
        }

        // Read a valid option, based on number of valid EANS.
        int option;
        readOption_BONE(par, head, EAN, totalEanCount, &option);
        if(option == 0) return 0;
        
        // Find the EAN at that option number and copy it into our EAN.
        strcpy(EAN, validEANS[option - 1]);
    } 
    return 1;
}

// Displays inventory with filtering by EAN, product name or (*).
void printInventory(MenuParameters *par, Product *head){
    
    // Read the option.
    char option[NAME_LENGTH];
    readOption_PRINT(par, head, option);
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

        // Print ALL products in the list.
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

        // Print products with matching EAN.
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

        // Print products with matching NAME.
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