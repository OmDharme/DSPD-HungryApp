//
// Created by Om Dharme on 11/03/23.
//

#ifndef HUNGYAPP_RESTAURANTSET_H
#define HUNGYAPP_RESTAURANTSET_H

#include "Restaurant.h"
#include <stdio.h>

typedef struct RestaurantSetEl{
    char restaurantName[40];
    int freq;
} RestaurantSetEl;

typedef struct RestaurantSet{
    RestaurantSetEl restaurants[100];
    int top;
} RestaurantSet;

void initialiseRestaurantSet(RestaurantSet* restaurantSet){
    restaurantSet->top = -1;
}

void printRestaurantSet(RestaurantSet* restaurantSet);

void insertInRestaurantSet(RestaurantSet* restaurantSet, char restaurantName[]){
    bool found = false;
    int i;

    for(i=0; i<=restaurantSet->top && !found; i++){
        if(strcmp(restaurantSet->restaurants[i].restaurantName, restaurantName) == 0){
            found = true;
            i--;
        }
    }

    if(!found){
        restaurantSet->top++;
        strcpy(restaurantSet->restaurants[restaurantSet->top].restaurantName,restaurantName);
        restaurantSet->restaurants[restaurantSet->top].freq = 1;
    }else{
        restaurantSet->restaurants[i].freq++;

        for(int j=0; j<i; j++){
            if(restaurantSet->restaurants[j].freq < restaurantSet->restaurants[i].freq){
                RestaurantSetEl temp = restaurantSet->restaurants[j];
                restaurantSet->restaurants[j] = restaurantSet->restaurants[i];
                restaurantSet->restaurants[i] = temp;
                break;
            }
        }
    }

}

void printRestaurantSet(RestaurantSet* restaurantSet){
    for(int i=0; i<=restaurantSet->top; i++){
        printf("%s - %d\n", restaurantSet->restaurants[i].restaurantName, restaurantSet->restaurants[i].freq);
    }

    printf("\n\n");
}

#endif //HUNGYAPP_RESTAURANTSET_H
