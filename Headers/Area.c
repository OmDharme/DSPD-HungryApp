//
// Created by Om Dharme on 02/03/23.
//

#include "Area.h"
#include <stdio.h>
#include <string.h>

void printAreaDetails(Area area){
    printf("Area name: %s\n", area.areaName);
    printf("Nearby Areas: ");
    for(int i=0; i<4; i++){
        if(strcmp(area.nearbyAreas[i], "None") != 0) printf("%s ", area.nearbyAreas[i]);
    }
    printf("\n");
}
