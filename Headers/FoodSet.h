//
// Created by Om Dharme on 11/03/23.
//

#ifndef HUNGYAPP_FOODSET_H
#define HUNGYAPP_FOODSET_H

#include "Food.h"
#include <stdio.h>

typedef struct FoodSetEl{
    Food food;
    int freq;
} FoodSetEl;

typedef struct FoodSet{
    FoodSetEl foods[100];
    int top;
} FoodSet;

void initialiseFoodSet(FoodSet* foodSet){
    foodSet->top = -1;
}

void printFoodSet(FoodSet* foodSet);

void insertInFoodSet(FoodSet* foodSet, Food food){
    bool found = false;
    int i;

    for(i=0; i<=foodSet->top && !found; i++){
        if(isEqualFood(foodSet->foods[i].food, food)){
            found = true;
            i--;
        }
    }

    if(!found){
        foodSet->top++;
        foodSet->foods[foodSet->top].food = food;
        foodSet->foods[foodSet->top].freq = 1;
    }else{
        foodSet->foods[i].freq++;

        for(int j=0; j<i; j++){
            if(foodSet->foods[j].freq < foodSet->foods[i].freq){
                FoodSetEl temp = foodSet->foods[j];
                foodSet->foods[j] = foodSet->foods[i];
                foodSet->foods[i] = temp;
                break;
            }
        }
    }

}

void printFoodSet(FoodSet* foodSet){
    for(int i=0; i<=foodSet->top; i++){
        printf("%s - %d\n", foodSet->foods[i].food.name, foodSet->foods[i].freq);
    }

    printf("\n\n");
}

#endif //HUNGYAPP_FOODSET_H
