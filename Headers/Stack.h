//
// Created by Om Dharme on 04/03/23.
//

#ifndef HUNGYAPP_STACK_H
#define HUNGYAPP_STACK_H

#include "Order.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Stack typedef
typedef struct Stack{
    int top;
    Order orders[100];
} Stack;

// Initialising the Stack
void initialiseStack(Stack* stack);

// Stack is empty if top == NULL
bool isStackEmpty(Stack* stack);

// Push function, returning status code
void Push(Stack* stack, Order order);

// Pop function, storing the popped value in val returning status code
Order Pop(Stack* stack);

void printStack(Stack* stack);

void printStackByIndex(Stack* stack);

#endif