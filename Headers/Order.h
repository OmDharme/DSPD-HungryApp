//
// Created by Om Dharme on 02/03/23.
//

#ifndef HUNGYAPP_ORDER_H
#define HUNGYAPP_ORDER_H

#include "Food.h"
#include "Agent.h"
#include "Date.h"

typedef struct Order{
    char userId[10];
    Food food;
    Date dateOrdered;
    char agentAssignedId[10];
} Order;

void printOrderDetails(Order order);

#endif //HUNGYAPP_ORDER_H
