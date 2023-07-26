//
// Created by Om Dharme on 04/03/23.
//

#ifndef HUNGYAPP_USER_H
#define HUNGYAPP_USER_H

#include "Stack.h"

typedef struct User{
    char id[10];
    long int phoneNum;
    char userName[40];
    char areaName[40];
    Stack previousOrders;
} User;

User createUser(char id[], long int phoneNum, char userName[], char areaName[]);

void printUserDetails(User user);

User addNewOrder(User user, Order order);


#endif //HUNGYAPP_USER_H
