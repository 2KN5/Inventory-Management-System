#include "orderQueue.h"
#include "product.h" 
#include "utils.h"

// PRINT MENUs START.

void printMenu_13(MenuParameters *par){
    printf("\n================================================\n");
    printf("             INSERT NEW ORDER\n");
    printf("================================================\n");    
    printf("\nEnter customer code: %s\n", par->customerCode);
    printf("Enter customer name: %s\n", par->customerName);
    printf("Enter order priority (%d - %d): %d\n", PRIORITY_MIN, PRIORITY_MAX, par->priority);
    printf("\n================================================\n\n");
    printf("Current items in order: %d\n\n", par->count);
    printf("Enter product EAN (or 0 to finish): ");
}

void printMenu_14(MenuParameters *par){
    printf("\n================================================\n");
    printf("             INSERT NEW ORDER\n");
    printf("================================================\n");
    printf("\nEnter customer code: %s\n", par->customerCode);
    printf("Enter customer name: %s\n", par->customerName);
    printf("Enter order priority (%d - %d): %d\n", PRIORITY_MIN, PRIORITY_MAX, par->priority);
    printf("\n================================================\n\n");
    printf("Current items in order: %d\n\n", par->count);
    printf("Enter product EAN (or 0 to finish): %s\n", par->EAN);
    printf("Enter quantity: ");
}

// PRINT MENUs END.

// Find product name by EAN.
Product* findItemByEAN(const char *ean, Product *inventory){
    if(!ean || !inventory) return NULL;
    Product *current = inventory;
    while(current != NULL){
        if(strcmp(current->EAN, ean) == 0) return current;
        current = current->next;
    }
    return NULL; 
}

// Validates EAN input (digit-only, 4-13 chars).
void readItemEAN(MenuParameters *par, char *itemEAN, char *customerCode, char *customerName, int priority, int count){

    // Initialize parameters.
    strcpy(par->errorMsg, "\nInvalid EAN. Has to be 13 characters long.\n");
    strcpy(par->customerCode, customerCode);
    strcpy(par->customerName, customerName);
    par->priority = priority;
    par->count = count;

    // Print menu.
    clearScreen();
    printMenu_13(par);

    // Check for valid EAN, , no extra characters after entering a number, etc.
    while(1){

        // Initialize string.
        char buffer[EAN_BUF] = {' '};
        if(!isValidBuffer(printMenu_13, par, buffer, sizeof(buffer))) continue;

        // Skip whitespace in the beginning. 
        char *temp = buffer;
        while(isspace(*temp)) ++temp;

        // Check if it's a digit, if not just skip.
        if(!isdigit(*temp)){
            clearScreen();
            printf("%s", par->errorMsg);
            printMenu_13(par);
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
            if(length != EAN_MAX_DIGITS && strcmp(tempValue, "0") != 0){
                clearScreen();
                printf("%s", par->errorMsg);
                printMenu_13(par);
                continue;
            }
            strcpy(itemEAN, tempValue);
            return;
        } 
        clearScreen();
        printf("%s", par->errorMsg);
        printMenu_13(par);
    }
}

// Validates quantity input (digit-only, positive numbers only, length checks).
void readItemQuantity(MenuParameters *par, char *itemEAN, int *quantity, char *customerCode, char *customerName, int priority, int count){

    // Initialize parameters.
    strcpy(par->errorMsg, "\nInvalid EAN. Has to be 13 characters long.\n");
    strcpy(par->customerCode, customerCode);
    strcpy(par->customerName, customerName);
    strcpy(par->EAN, itemEAN);
    par->priority = priority;
    par->count = count;

    // Print menu.
    clearScreen();
    printMenu_14(par);

    // Check for valid quantity, positive only and less than QTY_MAX_DIGITS.
    while(1){

        // Initialize string.
        char buffer[BUFFER_SIZE] = {' '};
        if(!isValidBuffer(printMenu_14, par, buffer, sizeof(buffer))) continue;

        // Skip whitespace in the beginning. 
        char *temp = buffer;
        while(isspace(*temp)) ++temp;

        // Check if it's a digit, if not just skip.
        if(!isdigit(*temp)){
            clearScreen();
            printf("%s", par->errorMsg);
            printMenu_14(par);
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
                printMenu_14(par);
                continue;
            }
            *quantity = atoi(tempValue);
            return;
        } 
        clearScreen();
        printf("%s", par->errorMsg);
        printMenu_14(par);
    }
}

// Initialize an empty Queue.
void initializeQueue(Queue *q){
    q->front = NULL;
    q->rear = NULL;
}

// Check if the queue is empty.
int isEmpty(Queue *queue){
    if(queue->front == NULL) return 1;
    return 0;
}

// Check if order bucket is empty.
int isOBEmpty(OrderBucket *ob){
    for(int i = PRIORITY_MIN; i <= PRIORITY_MAX; ++i){
        if(!isEmpty(&ob->buckets[i])) return 0;
    }
    return 1;
}

// Insert an element into the queue.
void enqueue(Queue *queue, Order *order){

    // Set order next item to NULL.
    order->next = NULL;

    // Check if queue is empty.
    if(isEmpty(queue)){
        queue->front = queue->rear = order;
    } else {
        queue->rear->next = order;
        queue->rear = order;
    }
}

// Remove an element from the queue.
Order *dequeue(Queue *queue){

    // Check if queue is empty.
    if(isEmpty(queue)) return NULL;

    // If it's not, store the order and move to the next element.
    Order *order = queue->front;
    queue->front = order->next;

    // If it was the last element, set rear to NULL.
    if(isEmpty(queue)) queue->rear = NULL;

    // Detach and return the node.
    order->next = NULL;
    return order;
}

// Initialize the order bucket, basically an array of Queues.
void initializeOB(OrderBucket *ob){
    for(int i = PRIORITY_MIN; i <= PRIORITY_MAX; ++i){
        initializeQueue(&ob->buckets[i]);
    }
}

// Put order into FIFO queue, corresponding to its priority.
void enqueueOB(OrderBucket *ob, Order *order){
    enqueue(&ob->buckets[order->priority], order);
}

// Dequeue element from queue with priority x.
Order *dequeueOB(OrderBucket *ob, int priority){

    // Ensure that priority won't cause any issues.
    // Although, I've already made sure this won't happen.
    if(priority < PRIORITY_MIN) priority = PRIORITY_MIN;
    if(priority > PRIORITY_MAX) priority = PRIORITY_MAX;

    return dequeue(&ob->buckets[priority]);
}

// Dequeue the order with the highest priority, that's first in line.
Order *dequeueOBNext(OrderBucket *ob){
    for(int priority = PRIORITY_MAX; priority >= PRIORITY_MIN; --priority){
        if(!isEmpty(&ob->buckets[priority])){
            return dequeue(&ob->buckets[priority]);
        }
    }
    return NULL;
}

// Free all order item nodes, then the order itself.
void freeOrder(Order *order){
    if(!order) return;
    OrderItem *current = order->items;
    while(current){
        OrderItem *next = current->next;
        free(current);
        current = next;
    }
    order->items = NULL;
}

// Free the entire order bucket.
void freeOrderBucket(OrderBucket *ob){
    for(int i = PRIORITY_MIN; i <= PRIORITY_MAX; ++i){
        Order *order;
        while((order = dequeue(&ob->buckets[i])) != NULL) free(order);
    }
}

// Print all orders.
void printAllOrders(OrderBucket *ob, Product *inventory){

    // Clear the screen.
    clearScreen();

    // Check if order bucket is empty.
    if(isOBEmpty(ob)){
        printf("\n============================================\n\n");
        printf("Order Queue Status: EMPTY\n");
        printf("There are no orders waiting to be processed.\n");
        printf("\n============================================\n");
        return;
    }

    // If not execute orders.
    printf("\n============= Executing Orders =============\n\n");

    Order *order;
    int orderCount = 0;
    while((order = dequeueOBNext(ob)) != NULL){
        orderCount++;

        printf("Customer: %s (Code: %s)\n", order->customerName, order->customerCode);
        printf("Priority: %d\n\n", order->priority);
        printf("| %-15s | %-10s | %-10s | %-10s | %-10s |\n", 
               "Product", "Requested", "Fulfilled", "Unit Price", "Total");
        printf("|-----------------|------------|------------|------------|------------|\n");

        char parFul[MAX_ITEMS][NAME_LENGTH];
        char outOfStockNames[MAX_ITEMS][NAME_LENGTH];
        char notFoundEANs[MAX_ITEMS][EAN_BUF];
        int pfCount = 0, osCount = 0, nfCount = 0;
        double orderTotal = 0.0;

        OrderItem *currItem = order->items;
        while(currItem){

            // Find item by EAN, inside the inventory.
            Product *itemFound = findItemByEAN(currItem->EAN, inventory);
            if(!itemFound){
                strcpy(notFoundEANs[nfCount], currItem->EAN);
                ++nfCount; 
                currItem = currItem->next;
                continue;
            }

            // If found, check if it's in stock.
            if(itemFound->quantity == 0){
                strcpy(outOfStockNames[osCount], itemFound->productName);
                ++osCount;
                currItem = currItem->next;
                continue;
            }

            // Calculate fulfillment.
            int ffQuantity;
            int reqQuantity = currItem->quantity;
            int avQuantity = itemFound->quantity;

            // Check if requested quantity is less than the available.
            if(reqQuantity <= avQuantity){
                ffQuantity = reqQuantity;
                itemFound->quantity -= reqQuantity;
            } else {
                ffQuantity = avQuantity;
                strcpy(parFul[pfCount], itemFound->productName);
                ++pfCount;
                itemFound->quantity = 0;
            }
            
            double itemTotal = ffQuantity * itemFound->price;
            orderTotal += itemTotal;

            // Print the product row.
            printf("| %-15s | %-10d | %-10d | %-10.2f | %-10.2f |\n", 
                   itemFound->productName, reqQuantity, ffQuantity, itemFound->price, itemTotal);

            currItem = currItem->next;
        }
        
        printf("|-----------------|------------|------------|------------|------------|\n");
        
        // Print order total.
        printf("\nOrder Total: $%.2f\n", orderTotal);
        
        // Print partial fulfillment warnings.
        if(pfCount > 0){
            printf("\nWARNING: Partial fulfillment for: ");
            for(int i = 0; i < pfCount; i++){
                printf("%s%s", parFul[i], (i < pfCount-1) ? ", " : "\n");
            }
        }
        
        // Out of stock warnings.
        if(osCount > 0){
            printf("\nProducts out of stock:\n");
            for(int i = 0; i < osCount; i++){
                printf("- %s\n", outOfStockNames[i]);
            }
        }
        
        // Product not found by EAN warnings.
        if(nfCount > 0){
            printf("\nProducts not found (By EAN):\n");
            for(int i = 0; i < nfCount; i++){
                printf("- %s\n", notFoundEANs[i]);
            }
        }
        
        printf("\n============================================\n\n");
        
        // Free the order.
        freeOrder(order);
        free(order);
    }
    
    if(orderCount > 0){
        printf("Executed %d order(s) successfully.\n", orderCount);
    }
}

// Insert new order.
void insertNewOrder(MenuParameters *par, char *customerCode, char *customerName, int priority, OrderBucket *ob){

    // Create the new order.
    Order *newOrder = malloc(sizeof(*newOrder));
    if(!newOrder){
        printf("Malloc failed!\n");
        return;
    }
    strcpy(newOrder->customerCode, customerCode);
    strcpy(newOrder->customerName, customerName);
    newOrder->priority = priority;
    newOrder->items = NULL;
    newOrder->next = NULL;

    // Create the item list.
    int count = 0;
    OrderItem *head = NULL;
    OrderItem *tail = NULL;

    // Insert items into the list.
    while(1){
    
        // Read the values.
        char itemEAN[EAN_BUF];
        int quantity;
        readItemEAN(par, itemEAN, customerCode, customerName, priority, count);
        if(strcmp(itemEAN, "0") == 0) break;
        readItemQuantity(par, itemEAN, &quantity, customerCode, customerName, priority, count);
   
        // In case of duplicates, merge quantities.
        int found = 0;
        OrderItem *checkEAN = head;
        while(checkEAN){
            if(strcmp(checkEAN->EAN, itemEAN) == 0){
                checkEAN->quantity += quantity;
                found = 1;
                break;
            }
            checkEAN = checkEAN->next;
        }
        if(found) continue;
        ++count;

        // Create the new item.
        OrderItem *item = malloc(sizeof(*item));
        if(!item){
            printf("Malloc failed!\n");
            return;
        }
        strcpy(item->EAN, itemEAN);
        item->quantity = quantity;
        item->next = NULL;

        if(!head){
            head = tail = item;
        } else {
            tail->next = item;
            tail = item;
        }
    }
    if(!head){
        printf("\n================================================\n\n");
        printf("No items entered. Order cancelled.\n");
        free(newOrder);
        return;
    }

    // If the list is not empty, add it to the buckets, based on priority.
    newOrder->items = head;
    enqueueOB(ob, newOrder);
    printf("\n================================================\n\n");
    printf("Order inserted successfully.\n");
}
