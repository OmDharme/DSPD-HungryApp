//
// Created by Om Dharme on 02/03/23.
//

#include "Restaurant.h"

void printRestaurantDetails(Restaurant restaurant){
    printf("Restaurant Name: %s\n", restaurant.restaurantName);
    printf("Area Name: %s\n", restaurant.areaName);
    printf("Restaurant Available Seats: %d\n", restaurant.availableSeats);
    printf("Restaurant Special Facilities: %s\n", restaurant.specialFacilities);
    printf("Restaurant Menu: \n");
    for(int i=0; i<30; i++){
        if(restaurant.menu[i].price == 0.0) break;
        printFoodDetials(restaurant.menu[i]);
    }
    printf("Restaurant Type: %s\n", restaurant.type);
    printf("Restaurant Cuisine: ");
    for(int i=0; i<10; i++){
        if(strcmp("", restaurant.cuisine[i]) == 0) break;
        printf("%s ", restaurant.cuisine[i]);
    }
    printf("\n");
}

void printRestaurantDescription(Restaurant restaurant){
    printf("Restaurant Name: %s\n", restaurant.restaurantName);
    printf("Area Name: %s\n", restaurant.areaName);
    printf("Available Seats: %d\n", restaurant.availableSeats);
    printf("Special Facilities: %s\n", restaurant.specialFacilities);
    printf("Restaurant Type: %s\n", restaurant.type);
    printf("Restaurant Cuisine: ");
    for(int i=0; i<10; i++){
        if(strcmp("", restaurant.cuisine[i]) == 0) break;
        printf("%s ", restaurant.cuisine[i]);
    }
    printf("\n");
}
