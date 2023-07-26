//
// Created by Om Dharme on 02/03/23.
//

#include "Date.h"
#include "stdio.h"

Date createDate(int day, int month, int year){
    Date date;

    date.day = day;
    date.month = month;
    date.year = year;

    return date;
}

void printDate(Date date){
    printf("%d/%d/%d", date.day, date.month, date.year);
}

int getCurrentMonth(){
    time_t t;
    time(&t);

    struct tm *timeInfo = localtime(&t);
    return timeInfo->tm_mon + 1;
}

Date getCurrentDate(){
    time_t t;
    time(&t);

    struct tm *timeInfo = localtime(&t);

    return createDate(timeInfo->tm_mday, timeInfo->tm_mon+1, timeInfo->tm_year);
}

int dateComp(Date d1, Date d2){
    if(d1.year < d2.year) return -1;
    else if(d1.year > d2.year) return 1;
    else{
        if(d1.month < d2.month) return -1;
        else if(d1.month > d2.month) return 1;
        else{
            if(d1.day < d2.day) return -1;
            else if(d1.day > d2.day) return 1;
            else return 0;
        }
    }
}