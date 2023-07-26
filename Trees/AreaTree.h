//
// Created by Om Dharme on 05/03/23.
//

#ifndef HUNGYAPP_AREALL_H
#define HUNGYAPP_AREALL_H

#include "../Headers/Area.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AreaNode{
    Area area;
    struct AreaNode *left;
    struct AreaNode *right;
    int height;
} AreaNode;

AreaNode* createAreaNode(Area area){
    AreaNode* newNode = (AreaNode*)malloc(sizeof(AreaNode));

    newNode->area = area;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;

    return newNode;
}

int getAreaHeight(AreaNode* areaNode){
    if(!areaNode) return 0;

    return areaNode->height;
}

AreaNode *rightRotateArea(AreaNode *y) {
    AreaNode *x = y->left;
    AreaNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getAreaHeight(y->left), getAreaHeight(y->right)) + 1;
    x->height = max(getAreaHeight(x->left), getAreaHeight(x->right)) + 1;

    return x;
}

// Left rotate
AreaNode *leftRotateArea(AreaNode *x) {
    AreaNode *y = x->right;
    AreaNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getAreaHeight(x->left), getAreaHeight(x->right)) + 1;
    y->height = max(getAreaHeight(y->left), getAreaHeight(y->right)) + 1;

    return y;
}

int getBalanceArea(AreaNode* areaNode) {
    if (areaNode == NULL)
        return 0;
    return getAreaHeight(areaNode->left) - getAreaHeight(areaNode->right);
}

AreaNode* insertAreaNode(AreaNode* root, Area area) {
    // Find the correct position to insertNode the node and insertNode it
    if (root == NULL)
        return createAreaNode(area);

    if (strcmp(area.areaName,root->area.areaName) < 0)
        root->left = insertAreaNode(root->left, area);
    else if (strcmp(area.areaName,root->area.areaName) > 0)
        root->right = insertAreaNode(root->right, area);
    else
        return root;

    // Update the balance factor of each node and
    // Balance the tree
    root->height = 1 + max(getAreaHeight(root->left),
                           getAreaHeight(root->right));

    int balance = getBalanceArea(root);
    if (balance > 1 && strcmp(area.areaName,root->left->area.areaName) < 0)
        return rightRotateArea(root);

    if (balance < -1 && strcmp(area.areaName,root->right->area.areaName) > 0)
        return leftRotateArea(root);

    if (balance > 1 && strcmp(area.areaName,root->left->area.areaName) > 0) {
        root->left = leftRotateArea(root->left);
        return rightRotateArea(root);
    }

    if (balance < -1 && strcmp(area.areaName,root->right->area.areaName) < 0) {
        root->right = rightRotateArea(root->right);
        return leftRotateArea(root);
    }

    return root;
}

AreaNode* initialiseAreaData(){
    AreaNode *root = NULL;

//    Reading all Area data from areaList.txt, and storing in areas array
    Area areas[8];
    FILE* areaFile = fopen("./../Data/areaList.txt", "r");
    fread(&areas, sizeof(Area), 8, areaFile);

    for(int i=0; i<8; i++){
        root = insertAreaNode(root, areas[i]);
    }

    return root;
}

void printAreasData(AreaNode* root){
    if(!root) return;

    printAreaDetails(root->area);
    printf("\n");

    printAreasData(root->left);
    printAreasData(root->right);
}

#endif //HUNGYAPP_AREALL_H
