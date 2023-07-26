//
// Created by Om Dharme on 07/03/23.
//

#ifndef HUNGYAPP_USERLL_H
#define HUNGYAPP_USERLL_H

#include "../Headers/User.h"
#include "./../Headers/FoodSet.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct UserNode{
    User user;
    struct UserNode *left;
    struct UserNode *right;
    int height;
} UserNode;

UserNode* createUserNode(User user){
    UserNode* newNode = (UserNode*)malloc(sizeof(UserNode));

    newNode->user = user;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;

    return newNode;
}

int getUserHeight(UserNode* userNode){
    if(!userNode) return 0;

    return userNode->height;
}

UserNode *rightRotateUser(UserNode *y) {
    UserNode *x = y->left;
    UserNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getUserHeight(y->left), getUserHeight(y->right)) + 1;
    x->height = max(getUserHeight(x->left), getUserHeight(x->right)) + 1;

    return x;
}

UserNode *leftRotateUser(UserNode *x) {
    UserNode *y = x->right;
    UserNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getUserHeight(x->left), getUserHeight(x->right)) + 1;
    y->height = max(getUserHeight(y->left), getUserHeight(y->right)) + 1;

    return y;
}

int getBalanceUser(UserNode* userNode) {
    if (userNode == NULL)
        return 0;
    return getUserHeight(userNode->left) - getUserHeight(userNode->right);
}

UserNode* insertUserNode(UserNode* root, User user) {
    // Find the correct position to insertNode the node and insertNode it
    if (root == NULL)
        return createUserNode(user);

    if (strcmp(user.id,root->user.id) < 0)
        root->left = insertUserNode(root->left, user);
    else if (strcmp(user.id,root->user.id) > 0)
        root->right = insertUserNode(root->right, user);
    else
        return root;

    // Update the balance factor of each node and
    // Balance the tree
    root->height = 1 + max(getUserHeight(root->left),
                           getUserHeight(root->right));

    int balance = getBalanceUser(root);
    if (balance > 1 && strcmp(user.id,root->left->user.id) < 0)
        return rightRotateUser(root);

    if (balance < -1 && strcmp(user.id,root->right->user.id) > 0)
        return leftRotateUser(root);

    if (balance > 1 && strcmp(user.id,root->left->user.id) > 0) {
        root->left = leftRotateUser(root->left);
        return rightRotateUser(root);
    }

    if (balance < -1 && strcmp(user.id,root->right->user.id) < 0) {
        root->right = rightRotateUser(root->right);
        return leftRotateUser(root);
    }

    return root;
}

UserNode* initialiseUserList(){
    UserNode *root = NULL;

//    Reading all Area data from userList.txt, and storing in users array
    User users[3];
    FILE* userFile = fopen("./../Data/userList.txt", "r");
    fread(&users, sizeof(User), 3, userFile);
    fclose(userFile);

    for(int i=0; i<3; i++){
        root = insertUserNode(root, users[i]);
    }

    return root;
}

void printUsersData(UserNode* root){
    if(!root) return;

    printUserDetails(root->user);
    printf("\n---------------------\n");

    printUsersData(root->left);
    printUsersData(root->right);
}

UserNode* getUserById(UserNode* root, char userId[]){
    if(!root) return NULL;

    if(strcmp(root->user.id, userId) == 0) return root;
    else if(strcmp(root->user.id, userId) < 0) return getUserById(root->right, userId);
    else if(strcmp(root->user.id, userId) > 0) return getUserById(root->left, userId);
}


#endif //HUNGYAPP_USERLL_H
