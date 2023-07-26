//
// Created by Om Dharme on 02/03/23.
//

#ifndef HUNGYAPP_FOOD_H
#define HUNGYAPP_FOOD_H

#include "stdbool.h"

typedef struct Food{
    char name[50];
    float price;
    char restaurantName[50];
} Food;


void printFoodDetials(Food food);

bool isEqualFood(Food food1, Food food2);

#endif //HUNGYAPP_FOOD_H
