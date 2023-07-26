//
// Created by Om Dharme on 02/03/23.
//

#ifndef HUNGYAPP_AREA_H
#define HUNGYAPP_AREA_H

typedef struct Area{
    char areaName[20];
    char nearbyAreas[4][10];
} Area;

void printAreaDetails(Area area);

#endif //HUNGYAPP_AREA_H
