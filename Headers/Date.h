//
// Created by Om Dharme on 02/03/23.
//

#ifndef HUNGYAPP_DATE_H
#define HUNGYAPP_DATE_H

#include "time.h"

typedef struct Date{
    int day;
    int month;
    int year;
} Date;

Date createDate(int day, int month, int year);

void printDate(Date date);

int getCurrentMonth();

Date getCurrentDate();

int dateComp(Date d1, Date d2);

#endif //HUNGYAPP_DATE_H
