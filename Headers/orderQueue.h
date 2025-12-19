#ifndef ORDERQUEUE_H
#define ORDERQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "common.h"

// Check .c file for function explanations. 

void initializeQueue();
int isEmpty();
int isFull();
void enqueue();
int dequeue();
void display();

#endif 
