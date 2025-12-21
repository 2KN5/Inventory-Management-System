#include "orderQueue.h"   
#include "product.h"      
#include "utils.h"

void printMenu_1(MenuParameters *par){
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

void printMenu_2(MenuParameters *par){
    printf("\n================================================\n");
    printf("         INSERT / UPDATE PRODUCT\n");
    printf("================================================\n\n");
    printf("Enter product EAN: ");
}

void printMenu_3(MenuParameters *par){
    printf("\n================================================\n");
    printf("         INSERT / UPDATE PRODUCT\n");
    printf("================================================\n\n");
    printf("Enter product EAN: %s\n", par->EAN);
    printf("Enter product name: ");
}

void printMenu_4(MenuParameters *par){
    printf("\n================================================\n");
    printf("         INSERT / UPDATE PRODUCT\n");
    printf("================================================\n\n");
    printf("Enter product EAN: %s\n", par->EAN);
    printf("Enter product name: %s\n", par->productName);
    printf("Enter quantity: ");
}

void printMenu_5(MenuParameters *par){
    printf("\n================================================\n");
    printf("         INSERT / UPDATE PRODUCT\n");
    printf("================================================\n\n");
    printf("Enter product EAN: %s\n", par->EAN);
    printf("Enter product name: %s\n", par->productName);
    printf("Enter quantity: %d\n", par->quantity);
    printf("Enter price: ");
}

void printMenu_6(MenuParameters *par){
    printf("\n================================================\n");
    printf("             INSERT NEW ORDER\n");
    printf("================================================\n");
    printf("\nEnter customer code: ");
}

void printMenu_7(MenuParameters *par){
    printf("\n================================================\n");
    printf("             INSERT NEW ORDER\n");
    printf("================================================\n");
    printf("\nEnter customer code: %s\n", par->customerCode);
    printf("Enter customer name: ");
}

void printMenu_8(MenuParameters *par){
    printf("\n================================================\n");
    printf("             INSERT NEW ORDER\n");
    printf("================================================\n");
    printf("\nEnter customer code: %s\n", par->customerCode);
    printf("Enter customer name: %s\n", par->customerName);
    printf("Enter order priority (%d - %d): ", PRIORITY_MIN, PRIORITY_MAX);
}

// PRINT MENUs END.

// Validates input, prevents buffer overflow, re-displays (given) menu on error.
int isValidBuffer(void (*printMenu)(MenuParameters*), MenuParameters *par, char *buffer, int bufferSize){

    // Get input and check for input errors.
    if (!fgets(buffer, bufferSize, stdin)) {
        clearScreen();
        printf("\nInput error.\n");
        printMenu(par);
        return 0;
    }

    // Check if we exceeded the bufferSize.
    if(!strchr(buffer, '\n')){
        clearBuffer();
        clearScreen();
        printf("%s", par->errorMsg);
        printMenu(par);
        return 0;
    }    
    return 1;
}

// Displays main menu and validates user selection (1-5), with error handling.
void mainMenu(int *number){
    
    // Initialize parameters.
    MenuParameters *par = malloc(sizeof(*par));
    if(!par) {
        printf("Memory allocation failed\n");
        return;
    }
    strcpy(par->errorMsg, "\nInvalid option. Please enter a number between 1 and 5.\n");
    
    // Print menu.
    clearScreen();
    printMenu_1(par);

    // Check for valid number, no extra characters after entering a number, etc.
    while(1){

        // Read the buffer.
        char buffer[BUFFER_SIZE] = {' '};
        if(!isValidBuffer(printMenu_1, par, buffer, sizeof(buffer))) continue;

        // Skip whitespace in the beginning. 
        char *temp = buffer;
        while(isspace(*temp)) ++temp;

        // Check if it's a digit, if not just skip.
        if(!isdigit(*temp)){
            clearScreen();
            printf("%s", par->errorMsg);
            printMenu_1(par);
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
                printf("%s", par->errorMsg);
                printMenu_1(par);
                continue;
            }
            break;
        } 
        clearScreen();
        printf("%s", par->errorMsg);
        printMenu_1(par);
    }
    free(par);
}

// Validates EAN input (digit-only, 4-13 chars).
void readEAN(MenuParameters *par, char *EAN){

    // Initialize parameters.
    sprintf(par->errorMsg, "\nInvalid EAN. Please try again | (%d - %d) Characters.\n", EAN_MIN_DIGITS, EAN_MAX_DIGITS);

    // Print menu.
    clearScreen();
    printMenu_2(par);

    // Check for valid EAN, , no extra characters after entering a number, etc.
    while(1){

        // Initialize string.
        char buffer[EAN_BUF] = {' '};
        if(!isValidBuffer(printMenu_2, par, buffer, sizeof(buffer))) continue;

        // Skip whitespace in the beginning. 
        char *temp = buffer;
        while(isspace(*temp)) ++temp;

        // Check if it's a digit, if not just skip.
        if(!isdigit(*temp)){
            clearScreen();
            printf("%s", par->errorMsg);
            printMenu_2(par);
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
                printf("%s", par->errorMsg);
                printMenu_2(par);
                continue;
            }
            strcpy(EAN, tempValue);
            return;
        } 
        clearScreen();
        printf("%s", par->errorMsg);
        printMenu_2(par);
    }
}

// Gets product name from user with non-empty validation.
void readProductName(MenuParameters *par, char *EAN, char *productName){

    // Initialize parameters.
    strcpy(par->errorMsg, "\nInvalid product name!\n");
    strcpy(par->EAN, EAN);

    // Print menu.
    clearScreen();
    printMenu_3(par);
    
    // Check if product name is less than NAME_LENGTH, and check for empty string.
    while(1){

        // Initialize string.
        char buffer[NAME_LENGTH] = {' '};
        if(!isValidBuffer(printMenu_3, par, buffer, sizeof(buffer))) continue;

        // Check if the user gave no input.
        buffer[strlen(buffer) - 1] = '\0';
        char *temp = buffer;
        while(isspace(*temp)) ++temp;
        if(strlen(temp) < 1){
            clearScreen();
            printf("\nNo input provided. Please enter a product name.\n");
            printMenu_3(par);
            continue;
        }
        strcpy(productName, temp);
        return;
    }
}

// Validates quantity input (digit-only, positive numbers only, length checks).
void readQuantity(MenuParameters *par, char *EAN, char *productName, int *quantity){

    // Initialize parameters.
    strcpy(par->errorMsg, "\nInvalid quantity. Please try again.\n");
    strcpy(par->EAN, EAN);
    strcpy(par->productName, productName);

    // Print menu.
    clearScreen();
    printMenu_4(par);

    // Check for valid quantity, positive only and less than QTY_MAX_DIGITS.
    while(1){

        // Initialize string.
        char buffer[BUFFER_SIZE] = {' '};
        if(!isValidBuffer(printMenu_4, par, buffer, sizeof(buffer))) continue;

        // Skip whitespace in the beginning. 
        char *temp = buffer;
        while(isspace(*temp)) ++temp;

        // Check if it's a digit, if not just skip.
        if(!isdigit(*temp)){
            clearScreen();
            printf("%s", par->errorMsg);
            printMenu_4(par);
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
                printMenu_4(par);
                continue;
            }
            *quantity = atoi(tempValue);
            return;
        } 
        clearScreen();
        printf("%s", par->errorMsg);
        printMenu_4(par);
    }
}

// Validates price input with decimal format checking (e.g., 12.50).
// Only accepts dots, not commas.
void readPrice(MenuParameters *par, char *EAN, char *productName, int quantity, double *price){

    // Initialize parameters.
    strcpy(par->errorMsg, "\nInvalid price. Please enter a reasonable value (e.g. 12.50).\n");
    strcpy(par->EAN, EAN);
    strcpy(par->productName, productName);
    par->quantity = quantity;

    // Print menu.
    clearScreen();
    printMenu_5(par);

    // Check for valid price.
    // Since it's a double, we only accept dots to avoid issues with the compiler.
    while(1){

        // Initialize string.
        char buffer[BUFFER_SIZE] = {' '};
        if(!isValidBuffer(printMenu_5, par, buffer, sizeof(buffer))) continue;

        // Skip whitespace in the beginning. 
        char *temp = buffer;
        while(isspace(*temp)) ++temp;

        // Check if it's a digit, if not just skip.
        if(!isdigit(*temp)){
            clearScreen();
            printf("%s", par->errorMsg);
            printMenu_5(par);
            continue;
        }

        // Get the whole number.
        int length = 0;
        char finalDouble[BUFFER_SIZE] = {' '};

        // Get first part of the number (e.g., 12.50 -> 12).
        int index = 0;
        char tempValue[BUFFER_SIZE] = {' '};
        while(index < (BUFFER_SIZE - 1) && isdigit(*temp)){
            tempValue[index] = *temp;
            ++temp; ++index;
        }
        length = index;
        strcpy(finalDouble, tempValue);

        // Check if there's a dot after the number and include it in the string.
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
                printf("%s", par->errorMsg);
                printMenu_5(par);
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
                printf("%s", par->errorMsg);
                printMenu_5(par);
                continue;
            }
            *price = atof(finalDouble);
            return;
        } 
        clearScreen();
        printf("%s", par->errorMsg);
        printMenu_5(par);
    }
}

// Gets customer CODE with length validation and non-empty input checking.
void readCustomerCode(MenuParameters *par, char *customerCode){

    // Initialize parameters.
    strcpy(par->errorMsg, "\nInvalid customer code!\n");

    // Print menu.
    clearScreen();
    printMenu_6(par);

    // Check if customer CODE is less than CUSTOMER_CODE_LEN, and check for empty string.
    while(1){

        // Initialize string.
        char buffer[CUSTOMER_CODE_LEN] = {' '};
        if(!isValidBuffer(printMenu_6, par, buffer, sizeof(buffer))) continue;
        
        // Check if the user gave no input.
        buffer[strlen(buffer) - 1] = '\0';
        char *temp = buffer;
        while(isspace(*temp)) ++temp;
        if(strlen(temp) < 1){
            clearScreen();
            printf("\nNo input provided. Please enter a customer code.\n");
            printMenu_6(par);
            continue;
        }
        strcpy(customerCode, temp);
        return;
    }
}

// Gets customer NAME with length validation and non-empty input checking.
void readCustomerName(MenuParameters *par, char *customerCode, char *customerName){

    // Initialize parameters.
    strcpy(par->errorMsg, "\nInvalid customer name!\n");
    strcpy(par->customerCode, customerCode);

    // Print menu.
    clearScreen();
    printMenu_7(par);

    // Check if customer NAME is less than NAME_LENGTH, and check for empty string.
    while(1){

        // Initialize string.
        char buffer[NAME_LENGTH] = {' '};
        if(!isValidBuffer(printMenu_7, par, buffer, sizeof(buffer))) continue;
        
        // Check if the user gave no input.
        buffer[strlen(buffer) - 1] = '\0';
        char *temp = buffer;
        while(isspace(*temp)) ++temp;
        if(strlen(temp) < 1){
            clearScreen();
            printf("\nNo input provided. Please enter a customer name.\n");
            printMenu_7(par);
            continue;
        }
        strcpy(customerName, temp);
        return;
    }
}

// Validates order priority input with range check -> (1-10).
void readPriority(MenuParameters *par, char *customerCode, char *customerName, int *priority){

    // Initialize parameters.
    sprintf(par->errorMsg, "\nInvalid option. Please enter a number between %d and %d.\n", PRIORITY_MIN, PRIORITY_MAX);
    strcpy(par->customerCode, customerCode);
    strcpy(par->customerName, customerName);

    // Print menu.
    clearScreen();
    printMenu_8(par);

    // Check if input is valid, no extra characters after entering a number, etc.
    while(1){

        // Initialize string.
        char buffer[BUFFER_SIZE] = {' '};
        if(!isValidBuffer(printMenu_8, par, buffer, sizeof(buffer))) continue;

        // Skip whitespace in the beginning. 
        char *temp = buffer;
        while(isspace(*temp)) ++temp;

        // Check if it's a digit, if not just skip.
        if(!isdigit(*temp)){
            clearScreen();
            printf("%s", par->errorMsg);
            printMenu_8(par);
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
                printf("%s", par->errorMsg);
                printMenu_8(par);
                continue;
            }
            return;
        } 
        clearScreen();
        printf("%s", par->errorMsg);
        printMenu_8(par);
    }
}

// Frees entire product, linked-list (in this case our inventory), from the memory.
void freeInventory(Product *inventory){
    Product *current = inventory;
    while(current){
        Product *next = current->next;
        free(current);
        current = next;
    }
}

// Run the program.
void runMS(int option, Product **inventory, OrderBucket *ob, MenuParameters *par){
    switch (option){
    case 1:
        // Initialize variables.
        int quantity;
        double price;
        char EAN[EAN_BUF], productName[NAME_LENGTH];

        // Read the EAN.
        readEAN(par, EAN);
        
        // Suggest product if the prefix is NOT 13 characters long.
        if(!suggestProduct(par, *inventory, EAN)) break; 

        // Check for product updates.
        if(updateProduct(par, *inventory, EAN)) break;

        // Read product name.
        readProductName(par, EAN, productName);

        // Read quantity.
        readQuantity(par, EAN, productName, &quantity);

        // Read price.
        readPrice(par, EAN, productName, quantity, &price);

        printf("\n================================================\n");
        printf("\nProduct added successfully.\n");

        // Add product to the list.
        *inventory = insertProduct(*inventory, EAN, productName, quantity, price);
        break;
    case 2:
        // Initialize variables.
        char customerCode[CUSTOMER_CODE_LEN];
        char customerName[NAME_LENGTH];
        int priority;

        // Read the customer CODE and NAME, making sure they are not empty.
        readCustomerCode(par, customerCode);
        readCustomerName(par, customerCode, customerName);

        // Read priority (For the queue).
        readPriority(par, customerCode, customerName, &priority);

        // Insert the order into the FIFO queue, based on priority.
        insertNewOrder(par, customerCode, customerName, priority, ob);
        break;
    case 3:
        // Print the inventory (Sorted by EAN).
        printInventory(par, *inventory);
        break;
    case 4:
        // Print all orders, based on priority.
        printAllOrders(ob, *inventory);
        break;
    default:
        // Exit.
        printf("\nExiting Program. Goodbye!\n");
        break;
    }
}



