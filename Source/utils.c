#include "utils.h"

void printMenu_1(){
    printf("\n================================================\n");
    printf("         INVENTORY MANAGEMENT SYSTEM\n");
    printf("================================================\n\n");
    printf("1. Insert / Update Product\n");
    printf("2. Insert New Order\n");
    printf("3. Print Inventory\n");
    printf("4. Execute Orders\n");
    printf("5. Exit\n\n");
    printf("------------------------------------------------\n");
    printf("Select option: ");
}

void printMenu_2(){
    printf("\n================================================\n");
    printf("         INSERT / UPDATE PRODUCT\n");
    printf("================================================\n\n");
    printf("Enter product EAN: ");
}

void printMenu_3(char *EAN){
    printf("\n================================================\n");
    printf("         INSERT / UPDATE PRODUCT\n");
    printf("================================================\n\n");
    printf("Enter product EAN: %s\n", EAN);
    printf("Enter product name: ");
}

void printMenu_4(char *EAN, char *productName){
    printf("\n================================================\n");
    printf("         INSERT / UPDATE PRODUCT\n");
    printf("================================================\n\n");
    printf("Enter product EAN: %s\n", EAN);
    printf("Enter product name: %s\n", productName);
    printf("Enter quantity: ");
}

void printMenu_5(char *EAN, char *productName, int quantity){
    printf("\n================================================\n");
    printf("         INSERT / UPDATE PRODUCT\n");
    printf("================================================\n\n");
    printf("Enter product EAN: %s\n", EAN);
    printf("Enter product name: %s\n", productName);
    printf("Enter quantity: %d\n", quantity);
    printf("Enter price: ");
}

void printMenu_6(){
    printf("\n================================================\n");
    printf("             INSERT NEW ORDER\n");
    printf("================================================\n");
    printf("\nEnter customer code: ");
}

void printMenu_7(char *customerCode){
    printf("\n================================================\n");
    printf("             INSERT NEW ORDER\n");
    printf("================================================\n");
    printf("\nEnter customer code: %s\n", customerCode);
    printf("Enter customer name: ");
}

void printMenu_8(char *customerCode, char *customerName){
    printf("\n================================================\n");
    printf("             INSERT NEW ORDER\n");
    printf("================================================\n");
    printf("\nEnter customer code: %s\n", customerCode);
    printf("Enter customer name: %s\n", customerName);
    printf("Enter order priority (%d - %d): ", PRIORITY_MIN, PRIORITY_MAX);
}

void mainMenu(int *number){
    
    // Print menu.
    clearScreen();
    printMenu_1();

    // Check if input is valid, no extra characters after entering a number, etc.
    while(1){

        // Initialize string.
        char buffer[BUFFER_SIZE] = {' '};
        if (!fgets(buffer, BUFFER_SIZE, stdin)) {
            clearScreen();
            printf("\nInput error.\n");
            printMenu_1();
            continue;
        }

        // Check if we exceeded the BUFFER_SIZE.
        if(!strchr(buffer, '\n')){
            clearBuffer();
            clearScreen();
            printf("\nInvalid option. Please enter a number between 1 and 5.\n");
            printMenu_1();
            continue;
        }

        // Skip whitespace in the beginning. 
        char *temp = buffer;
        while(isspace(*temp)) ++temp;

        // Check if it's a digit, if not just skip.
        if(!isdigit(*temp)){
            clearScreen();
            printf("\nInvalid option. Please enter a number between 1 and 5.\n");
            printMenu_1();
            continue;
        }

        // Get the whole number.
        int index = 0;
        char tempNumber[BUFFER_SIZE] = {' '};
        while(index < (BUFFER_SIZE - 1) && isdigit(*temp)){
            tempNumber[index] = *temp;
            ++temp; ++index;
        }
        tempNumber[index] = '\0';
        
        // Check if there's anything else after the number.
        while(isspace(*temp)) ++temp;
        if(*temp == '\0'){
            *number = atoi(tempNumber);
            if(!(*number >= OPTION_MIN && *number <= OPTION_MAX)){
                clearScreen();
                printf("\nInvalid option. Please enter a number between 1 and 5.\n");
                printMenu_1();
                continue;
            }
            return;
        } 
        clearScreen();
        printf("\nInvalid option. Please enter a number between 1 and 5.\n");
        printMenu_1();
    }
}

void readEAN(char *EAN){

    // Print menu.
    clearScreen();
    printMenu_2();

    // Check for valid EAN.
    while(1){

        // Initialize string.
        char buffer[EAN_BUF] = {' '};
        if (!fgets(buffer, EAN_BUF, stdin)) {
            clearScreen();
            printf("\nInput error.\n");
            printMenu_2();
            continue;
        }

        // Check if we exceeded the EAN_DIGITS.
        if(!strchr(buffer, '\n')){
            clearBuffer();
            clearScreen();
            printf("\nInvalid EAN. Please try again | (%d - %d) Characters.\n", EAN_MIN_DIGITS, EAN_MAX_DIGITS);
            printMenu_2();
            continue;
        }

        // Skip whitespace in the beginning. 
        char *temp = buffer;
        while(isspace(*temp)) ++temp;

        // Check if it's a digit, if not just skip.
        if(!isdigit(*temp)){
            clearScreen();
            printf("\nInvalid EAN. Please try again | (%d - %d) Characters.\n", EAN_MIN_DIGITS, EAN_MAX_DIGITS);
            printMenu_2();
            continue;
        }

        // Get the whole number.
        int index = 0;
        char tempValue[EAN_BUF] = {' '};
        while(index < (EAN_BUF - 1) && isdigit(*temp)){
            tempValue[index] = *temp;
            ++temp; ++index;
        }
        tempValue[index] = '\0';
        
        // Check if there's anything else after the number.
        while(isspace(*temp)) ++temp;
        if(*temp == '\0'){
            int length = strlen(tempValue);
            if(!(length >= EAN_MIN_DIGITS && length <= EAN_MAX_DIGITS)){
                clearScreen();
                printf("\nInvalid EAN. Please try again | (%d - %d) Characters.\n", EAN_MIN_DIGITS, EAN_MAX_DIGITS);
                printMenu_2();
                continue;
            }
            strcpy(EAN, tempValue);
            return;
        } 
        clearScreen();
        printf("\nInvalid EAN. Please try again | (%d - %d) Characters.\n", EAN_MIN_DIGITS, EAN_MAX_DIGITS);
        printMenu_2();
    }
}

void readProductName(char *EAN, char *productName){

    // Print menu.
    clearScreen();
    printMenu_3(EAN);
    
    while(1){

        // Initialize string.
        char buffer[NAME_LENGTH] = {' '};
        if (!fgets(buffer, NAME_LENGTH, stdin)) {
            clearScreen();
            printf("\nInput error.\n");
            printMenu_3(EAN);
            continue;
        }

        // Check if we exceeded the NAME_LENGTH.
        if(!strchr(buffer, '\n')){
            clearBuffer();
            clearScreen();
            printf("\nInvalid product name!\n");
            printMenu_3(EAN);
            continue;
        } 

        buffer[strlen(buffer) - 1] = '\0';
        char *temp = buffer;
        while(isspace(*temp)) ++temp;
        if(strlen(temp) < 1){
            clearScreen();
            printf("\nNo input provided. Please enter a product name.\n");
            printMenu_3(EAN);
            continue;
        }
        strcpy(productName, temp);
        return;
    }
}

void readQuantity(char *EAN, char *productName, int *quantity){

    // Print menu.
    clearScreen();
    printMenu_4(EAN, productName);

    // Check for valid Quantity.
    while(1){

        // Initialize string.
        char buffer[BUFFER_SIZE] = {' '};
        if (!fgets(buffer, BUFFER_SIZE, stdin)) {
            clearScreen();
            printf("\nInput error.\n");
            printMenu_4(EAN, productName);
            continue;
        }

        // Check if we exceeded the BUFFER_SIZE.
        if(!strchr(buffer, '\n')){
            clearBuffer();
            clearScreen();
            printf("\nInvalid quantity. Please try again.\n");
            printMenu_4(EAN, productName);
            continue;
        }

        // Skip whitespace in the beginning. 
        char *temp = buffer;
        while(isspace(*temp)) ++temp;

        // Check if it's a digit, if not just skip.
        if(!isdigit(*temp)){
            clearScreen();
            printf("\nInvalid quantity. Please try again.\n");
            printMenu_4(EAN, productName);
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
                printMenu_4(EAN, productName);
                continue;
            }
            *quantity = atoi(tempValue);
            return;
        } 
        clearScreen();
        printf("\nInvalid quantity. Please try again.\n");
        printMenu_4(EAN, productName);
    }
}

void readPrice(char *EAN, char *productName, int quantity, double *price){
    // Print menu.
    clearScreen();
    printMenu_5(EAN, productName, quantity);

    // Check for valid Quantity.
    while(1){

        // Initialize string.
        char buffer[BUFFER_SIZE] = {' '};
        if (!fgets(buffer, BUFFER_SIZE, stdin)) {
            clearScreen();
            printf("\nInput error.\n");
            printMenu_5(EAN, productName, quantity);
            continue;
        }

        // Check if we exceeded the BUFFER_SIZE.
        if(!strchr(buffer, '\n')){
            clearBuffer();
            clearScreen();
            printf("\nInvalid price. Please enter a reasonable value (e.g. 12.50).\n");
            printMenu_5(EAN, productName, quantity);
            continue;
        }

        // Skip whitespace in the beginning. 
        char *temp = buffer;
        while(isspace(*temp)) ++temp;

        // Check if it's a digit, if not just skip.
        if(!isdigit(*temp)){
            clearScreen();
            printf("\nInvalid price. Please enter a reasonable value (e.g. 12.50).\n");
            printMenu_5(EAN, productName, quantity);
            continue;
        }

        // Get the whole number.
        int length = 0;
        char finalDouble[BUFFER_SIZE] = {' '};

        // Get the first part.
        int index = 0;
        char tempValue[BUFFER_SIZE] = {' '};
        while(index < (BUFFER_SIZE - 1) && isdigit(*temp)){
            tempValue[index] = *temp;
            ++temp; ++index;
        }
        length = index;
        strcpy(finalDouble, tempValue);

        // Check if there's a dot after the number.
        if(*temp == '.'){
            strcat(finalDouble, ".");
            ++temp; ++length;

            // We MUST have at least one digit after the dot.
            index = 0;
            tempValue[0] = '\0';
            while(index < (BUFFER_SIZE - 1) && isdigit(*temp)){
                tempValue[index] = *temp;
                ++temp; ++index;
            }
            if(strlen(tempValue) < 1){
                clearScreen();
                printf("\nInvalid price. Please enter a reasonable value (e.g. 12.50).\n");
                printMenu_5(EAN, productName, quantity);
                continue;
            }
            length += index;
        }

        // Assign final double value.
        strcat(finalDouble, tempValue);
        finalDouble[length] = '\0';
        
        // Check if there's anything else after the number.
        while(isspace(*temp)) ++temp;
        if(*temp == '\0'){
            int length = strlen(finalDouble);
            if(length > 10){
                clearScreen();
                printf("\nInvalid price. Please enter a reasonable value (e.g. 12.50).\n");
                printMenu_5(EAN, productName, quantity);
                continue;
            }
            *price = atof(finalDouble);
            return;
        } 
        clearScreen();
        printf("\nInvalid price. Please enter a reasonable value (e.g. 12.50).\n");
        printMenu_5(EAN, productName, quantity);
    }
}

void readCustomerCode(char *customerCode){

    // Print menu.
    clearScreen();
    printMenu_6();

    while(1){

        // Initialize string.
        char buffer[CUSTOMER_CODE_LEN] = {' '};
        if (!fgets(buffer, CUSTOMER_CODE_LEN, stdin)) {
            clearScreen();
            printf("\nInput error.\n");
            printMenu_6();
            continue;
        }

        // Check if we exceeded the CUSTOMER_CODE_LEN.
        if(!strchr(buffer, '\n')){
            clearBuffer();
            clearScreen();
            printf("\nInvalid customer code!\n");
            printMenu_6();
            continue;
        } 

        buffer[strlen(buffer) - 1] = '\0';
        char *temp = buffer;
        while(isspace(*temp)) ++temp;
        if(strlen(temp) < 1){
            clearScreen();
            printf("\nNo input provided. Please enter a product name.\n");
            printMenu_6();
            continue;
        }
        strcpy(customerCode, temp);
        return;
    }
}

void readCustomerName(char *customerCode, char *customerName){

    // Print menu.
    clearScreen();
    printMenu_7(customerCode);

    while(1){

        // Initialize string.
        char buffer[NAME_LENGTH] = {' '};
        if (!fgets(buffer, NAME_LENGTH, stdin)) {
            clearScreen();
            printf("\nInput error.\n");
            printMenu_7(customerCode);
            continue;
        }

        // Check if we exceeded the NAME_LENGTH.
        if(!strchr(buffer, '\n')){
            clearBuffer();
            clearScreen();
            printf("\nInvalid customer name!\n");
            printMenu_7(customerCode);
            continue;
        } 
        
        buffer[strlen(buffer) - 1] = '\0';
        char *temp = buffer;
        while(isspace(*temp)) ++temp;
        if(strlen(temp) < 1){
            clearScreen();
            printf("\nNo input provided. Please enter a product name.\n");
            printMenu_7(customerCode);
            continue;
        }
        strcpy(customerName, temp);
        return;
    }
}

void readPriority(char *customerCode, char *customerName, int *priority){

    // Print menu.
    clearScreen();
    printMenu_8(customerCode, customerName);

    // Check if input is valid, no extra characters after entering a number, etc.
    while(1){

        // Initialize string.
        char buffer[BUFFER_SIZE] = {' '};
        if (!fgets(buffer, BUFFER_SIZE, stdin)) {
            clearScreen();
            printf("\nInput error.\n");
            printMenu_8(customerCode, customerName);
            continue;
        }

        // Check if we exceeded the BUFFER_SIZE.
        if(!strchr(buffer, '\n')){
            clearBuffer();
            clearScreen();
            printf("\nInvalid option. Please enter a number between %d and %d.\n", PRIORITY_MIN, PRIORITY_MAX);
            printMenu_8(customerCode, customerName);
            continue;
        }

        // Skip whitespace in the beginning. 
        char *temp = buffer;
        while(isspace(*temp)) ++temp;

        // Check if it's a digit, if not just skip.
        if(!isdigit(*temp)){
            clearScreen();
            printf("\nInvalid option. Please enter a number between %d and %d.\n", PRIORITY_MIN, PRIORITY_MAX);
            printMenu_8(customerCode, customerName);
            continue;
        }

        // Get the whole number.
        int index = 0;
        char tempNumber[BUFFER_SIZE] = {' '};
        while(index < (BUFFER_SIZE - 1) && isdigit(*temp)){
            tempNumber[index] = *temp;
            ++temp; ++index;
        }
        tempNumber[index] = '\0';
        
        // Check if there's anything else after the number.
        while(isspace(*temp)) ++temp;
        if(*temp == '\0'){
            *priority = atoi(tempNumber);
            if(!(*priority >= PRIORITY_MIN && *priority <= PRIORITY_MAX)){
                clearScreen();
                printf("\nInvalid option. Please enter a number between %d and %d.\n", PRIORITY_MIN, PRIORITY_MAX);
                printMenu_8(customerCode, customerName);
                continue;
            }
            return;
        } 
        clearScreen();
        printf("\nInvalid option. Please enter a number between %d and %d.\n", PRIORITY_MIN, PRIORITY_MAX);
        printMenu_8(customerCode, customerName);
    }
}

void freeInventory(Product *inventory){
    Product *current = inventory;
    while(current){
        Product *next = current->next;
        free(current);
        current = next;
    }
}

// Run the program.
void runMS(int option, Product **inventory, OrderBucket *ob){
    switch (option){
    case 1:
        // Initialize variables.
        int quantity;
        double price;
        char EAN[EAN_BUF], productName[NAME_LENGTH];

        // Read the EAN.
        readEAN(EAN);
        
        // Suggest product if the prefix is NOT 13 characters long.
        if(!suggestProduct(*inventory, EAN)) break; 

        // Check for product updates.
        if(updateProduct(*inventory, EAN)) break;

        // If we suggest a product, then call updateQuantity().
        readProductName(EAN, productName);
        readQuantity(EAN, productName, &quantity);
        readPrice(EAN, productName, quantity, &price);
        printf("\n================================================\n");
        printf("\nProduct added successfully.\n");

        // Add product to the list;
        *inventory = insertProduct(*inventory, EAN, productName, quantity, price);
        break;
    case 2:
        // Variables.
        char customerCode[CUSTOMER_CODE_LEN];
        char customerName[NAME_LENGTH];
        int priority;

        // Read the variables.
        readCustomerCode(customerCode);
        readCustomerName(customerCode, customerName);
        readPriority(customerCode, customerName, &priority);

        // Insert the order into the FIFO queue, based on priority.
        insertNewOrder(customerCode, customerName, priority, ob);
        break;
    case 3:
        printInventory(*inventory);
        break;
    case 4:
        printAllOrders(ob, *inventory);
        break;
    default:
        printf("\nExiting Program. Goodbye!\n");
        break;
    }
}



