//
// Created by Om Dharme on 04/03/23.
//

#include <stdio.h>
#include <string.h>
#include "User.h"


User createUser(char id[], long int phoneNum, char userName[], char areaName[]){
    User user;

    strcpy(user.id, id);
    user.phoneNum = phoneNum;
    strcpy(user.userName, userName);
    strcpy(user.areaName, areaName);

    initialiseStack(&user.previousOrders);

    return user;
}

void printUserDetails(User user){
    printf("User id: %s\n", user.id);
    printf("User phone num: %ld\n", user.phoneNum);
    printf("User name: %s\n", user.userName);
    printf("User area: %s\n", user.areaName);
    printf("Previous Orders details: \n");
    printStack(&user.previousOrders);
}

User addNewOrder(User user, Order order){
    Push(&user.previousOrders, order);

    return user;
}