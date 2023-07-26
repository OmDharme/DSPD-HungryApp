//
// Created by Om Dharme on 02/03/23.
//

#ifndef HUNGYAPP_RESTAURANT_H
#define HUNGYAPP_RESTAURANT_H

#include <string.h>
#include <stdio.h>
#include "Area.h"
#include "Food.h"
#include "Stack.h"

typedef struct Restaurant{
    char restaurantName[40];
    char areaName[40];
    int availableSeats;
    char specialFacilities[50];
    Food menu[30];
    char type[20];
    char cuisine[10][40];
} Restaurant;

void printRestaurantDetails(Restaurant restaurant);

void printRestaurantDescription(Restaurant restaurant);


#endif //HUNGYAPP_RESTAURANT_H
