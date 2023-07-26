//
// Created by Om Dharme on 02/03/23.
//

#include "Order.h"
#include <stdio.h>
#include <string.h>

void printOrderDetails(Order order){
    printf("User Id: %s\n", order.userId);
    printf("Food Details:\n");
    printFoodDetials(order.food);
    printf("Date ordered: ");
    printDate(order.dateOrdered);
    printf("\n");
    printf("Agent Assigned Id: %s\n", order.agentAssignedId);
}