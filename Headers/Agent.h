//
// Created by Om Dharme on 02/03/23.
//

#ifndef HUNGYAPP_AGENT_H
#define HUNGYAPP_AGENT_H

#include "stdbool.h"

typedef struct Agent{
    char id[10];
    long int phoneNum;
    char agentName[40];
    float commission;
    bool isFree;
    char areaAssigned[40];
} Agent;

void printAgentDetails(Agent agent);



#endif //HUNGYAPP_AGENT_H
