//
// Created by Om Dharme on 02/03/23.
//

#include "Food.h"
#include <stdio.h>
#include <string.h>

void printFoodDetials(Food food){
    printf("Food name: %s\n", food.name);
    printf("Food price: %.2f\n", food.price);
    printf("Food restaurant: %s\n", food.restaurantName);
}

bool isEqualFood(Food food1, Food food2){
    return strcmp(food1.name, food2.name) == 0;
}