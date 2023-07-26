//
// Created by Om Dharme on 05/03/23.
//

#ifndef HUNGYAPP_AGENTLL_H
#define HUNGYAPP_AGENTLL_H

#include "../Headers/Agent.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AgentNode{
    Agent agent;
    struct AgentNode *left;
    struct AgentNode *right;
    int height;
} AgentNode;

AgentNode* createAgentNode(Agent agent){
    AgentNode* newNode = (AgentNode*)malloc(sizeof(AgentNode));

    newNode->agent = agent;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;

    return newNode;
}

int getAgentHeight(AgentNode* agentNode){
    if(!agentNode) return 0;

    return agentNode->height;
}

AgentNode *rightRotateAgent(AgentNode *y) {
    AgentNode *x = y->left;
    AgentNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getAgentHeight(y->left), getAgentHeight(y->right)) + 1;
    x->height = max(getAgentHeight(x->left), getAgentHeight(x->right)) + 1;

    return x;
}

AgentNode *leftRotateAgent(AgentNode *x) {
    AgentNode *y = x->right;
    AgentNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getAgentHeight(x->left), getAgentHeight(x->right)) + 1;
    y->height = max(getAgentHeight(y->left), getAgentHeight(y->right)) + 1;

    return y;
}

int getBalanceAgent(AgentNode* agentNode) {
    if (agentNode == NULL)
        return 0;
    return getAgentHeight(agentNode->left) - getAgentHeight(agentNode->right);
}

AgentNode* insertAgentNode(AgentNode* root, Agent agent) {
    // Find the correct position to insertNode the node and insertNode it
    if (root == NULL)
        return createAgentNode(agent);

    if (strcmp(agent.id,root->agent.id) < 0)
        root->left = insertAgentNode(root->left, agent);
    else if (strcmp(agent.id,root->agent.id) > 0)
        root->right = insertAgentNode(root->right, agent);
    else
        return root;

    // Update the balance factor of each node and
    // Balance the tree
    root->height = 1 + max(getAgentHeight(root->left),
                           getAgentHeight(root->right));

    int balance = getBalanceAgent(root);
    if (balance > 1 && strcmp(agent.id,root->left->agent.id) < 0)
        return rightRotateAgent(root);

    if (balance < -1 && strcmp(agent.id,root->right->agent.id) > 0)
        return leftRotateAgent(root);

    if (balance > 1 && strcmp(agent.id,root->left->agent.id) > 0) {
        root->left = leftRotateAgent(root->left);
        return rightRotateAgent(root);
    }

    if (balance < -1 && strcmp(agent.id,root->right->agent.id) < 0) {
        root->right = rightRotateAgent(root->right);
        return leftRotateAgent(root);
    }

    return root;
}

AgentNode* initialiseAgentData(){
    AgentNode *root = NULL;

//    Reading all Area data from agentList.txt, and storing in agents array
    Agent agents[12];
    FILE* agentFile = fopen("./../Data/agentList.txt", "r");
    fread(&agents, sizeof(Agent), 12, agentFile);

    for(int i=0; i<12; i++){
        root = insertAgentNode(root, agents[i]);
    }

    return root;
}

void printAgentsData(AgentNode* root){
    if(!root) return;

    printAgentDetails(root->agent);
    printf("\n");

    printAgentsData(root->left);
    printAgentsData(root->right);
}

//void printAgentListAreaWise(AgentNode* agentHead, AreaNode* areaHead){
//    AgentNode* agentTemp = agentHead;
//    AreaNode* areaTemp = areaHead;
//
//    while(areaTemp != NULL){
//        agentTemp = agentHead;
//        while(agentTemp != NULL){
//            if(strcmp(agentTemp->agent.areaAssigned, areaTemp->area.areaName) == 0){
//                printAgentDetails(agentTemp->agent);
//                printf("---------------------------\n");
//            }
//            agentTemp = agentTemp->next;
//        }
//        areaTemp = areaTemp->next;
//    }
//}
//
AgentNode* getAgentById(AgentNode* root, char agentId[]){
    if(!root) return NULL;

    if(strcmp(root->agent.id, agentId) == 0) return root;
    else if(strcmp(root->agent.id, agentId) < 0) return getAgentById(root->right, agentId);
    else if(strcmp(root->agent.id, agentId) > 0) return getAgentById(root->left, agentId);
}


#endif //HUNGYAPP_AGENTLL_H
