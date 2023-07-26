//
// Created by Om Dharme on 04/03/23.
//

#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void initialiseStack(Stack* stack){
    stack->top = -1;
}

bool isStackEmpty(Stack* stack){
    if(stack->top != -1){
        return false;
    }

    return true;
}

void Push(Stack* stack, Order order){

    if(stack->top != 99){
        stack->top++;
        stack->orders[stack->top] = order;
    }

}

Order Pop(Stack* stack){

    Order order = stack->orders[stack->top];
    stack->top--;

    return order;
}

void printStack(Stack* stack){
    int top = stack->top;
    while(top >= 0){
        printOrderDetails(stack->orders[top]);
        top--;
    }
}

void printStackByIndex(Stack* stack){
    int top = stack->top;
    while(top >= 0){
        printf("%d: %s\n", stack->top-top+1, stack->orders[top].food.name);
        top--;
    }
}