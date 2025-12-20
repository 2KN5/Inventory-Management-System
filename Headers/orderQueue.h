#ifndef ORDERQUEUE_H
#define ORDERQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"
#include "product.h"

typedef struct OrderItem {
    char EAN[EAN_BUF];
    int quantity;
    struct OrderItem *next; // Linked list.
} OrderItem;

typedef struct Order {
    char customerCode[CUSTOMER_CODE_LEN];
    char customerName[NAME_LENGTH];
    int priority;
    OrderItem *items;
    struct Order *next; // For queue linkage.
} Order;

typedef struct Queue {
    Order *front;
    Order *rear;
} Queue;

typedef struct OrderBucket {
    Queue buckets[PRIORITY_MAX + 1]; // Priority is set to be 1-10.
} OrderBucket;

// Check .c file for function explanations. 

int isEmpty(Queue *queue);
void initializeQueue(Queue *q);
void enqueue(Queue *queue, Order *order);
void initializeOB(OrderBucket *ob);
void enqueueOB(OrderBucket *ob, Order *order);
Order *dequeue(Queue *queue);
Order *dequeueOB(OrderBucket *ob, int priority);
Order *dequeueOBNext(OrderBucket *ob);

void insertNewOrder(char *customerCode, char *customerName, int priority, OrderBucket *ob);
void freeOrder(Order *order);
void freeOrderBucket(OrderBucket *ob);

void printAllOrders(OrderBucket *ob, Product *inventory);

#endif 
