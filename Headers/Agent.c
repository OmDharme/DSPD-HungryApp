//
// Created by Om Dharme on 02/03/23.
//

#include "Agent.h"
#include <string.h>
#include <stdio.h>

void printAgentDetails(Agent agent){
    printf("Agent Id: %s\n", agent.id);
    printf("Agent Phone Number: %ld\n", agent.phoneNum);
    printf("Agent Name: %s\n", agent.agentName);
    printf("Agent Commission: %f\n", agent.commission);
    printf("Agent Availability: ");
    if(agent.isFree) printf("Free\n");
    else printf("Not free\n");
    printf("Area Assigned: %s\n", agent.areaAssigned);
}
