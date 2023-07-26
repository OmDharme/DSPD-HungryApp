//
// Created by Om Dharme on 09/03/23.
//

#ifndef HUNGYAPP_RESTAURANTLL_H
#define HUNGYAPP_RESTAURANTLL_H

#include "./../Headers/Restaurant.h"
#include "./../Headers/RestaurantSet.h"
#include <stdio.h>
#include "utils.h"

typedef struct RestaurantNode{
    Restaurant restaurant;
    struct RestaurantNode *left;
    struct RestaurantNode *right;
    int height;
} RestaurantNode;

RestaurantNode* createRestaurantNode(Restaurant restaurant){
    RestaurantNode* newNode = (RestaurantNode*)malloc(sizeof(RestaurantNode));

    newNode->restaurant = restaurant;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;

    return newNode;
}

int getRestaurantHeight(RestaurantNode* restaurantNode){
    if(!restaurantNode) return 0;

    return restaurantNode->height;
}

RestaurantNode *rightRotateRestaurant(RestaurantNode *y) {
    RestaurantNode *x = y->left;
    RestaurantNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getRestaurantHeight(y->left), getRestaurantHeight(y->right)) + 1;
    x->height = max(getRestaurantHeight(x->left), getRestaurantHeight(x->right)) + 1;

    return x;
}

RestaurantNode *leftRotateRestaurant(RestaurantNode *x) {
    RestaurantNode *y = x->right;
    RestaurantNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getRestaurantHeight(x->left), getRestaurantHeight(x->right)) + 1;
    y->height = max(getRestaurantHeight(y->left), getRestaurantHeight(y->right)) + 1;

    return y;
}

int getBalanceRestaurant(RestaurantNode* restaurantNode) {
    if (restaurantNode == NULL)
        return 0;
    return getRestaurantHeight(restaurantNode->left) - getRestaurantHeight(restaurantNode->right);
}

RestaurantNode* insertRestaurantNode(RestaurantNode* root, Restaurant restaurant) {
    // Find the correct position to insertNode the node and insertNode it
    if (root == NULL)
        return createRestaurantNode(restaurant);

    if (strcmp(restaurant.restaurantName,root->restaurant.restaurantName) < 0)
        root->left = insertRestaurantNode(root->left, restaurant);
    else if (strcmp(restaurant.restaurantName,root->restaurant.restaurantName) > 0)
        root->right = insertRestaurantNode(root->right, restaurant);
    else
        return root;

    // Update the balance factor of each node and
    // Balance the tree
    root->height = 1 + max(getRestaurantHeight(root->left),
                           getRestaurantHeight(root->right));

    int balance = getBalanceRestaurant(root);
    if (balance > 1 && strcmp(restaurant.restaurantName,root->left->restaurant.restaurantName) < 0)
        return rightRotateRestaurant(root);

    if (balance < -1 && strcmp(restaurant.restaurantName,root->right->restaurant.restaurantName) > 0)
        return leftRotateRestaurant(root);

    if (balance > 1 && strcmp(restaurant.restaurantName,root->left->restaurant.restaurantName) > 0) {
        root->left = leftRotateRestaurant(root->left);
        return rightRotateRestaurant(root);
    }

    if (balance < -1 && strcmp(restaurant.restaurantName,root->right->restaurant.restaurantName) < 0) {
        root->right = rightRotateRestaurant(root->right);
        return leftRotateRestaurant(root);
    }

    return root;
}

RestaurantNode* initialiseRestaurantData(){
    RestaurantNode *root = NULL;

//    Reading all Area data from userList.txt, and storing in users array
    Restaurant restaurants[8];
    FILE* restaurantFile = fopen("./../Data/restaurantList.txt", "r");
    if(restaurantFile){
        fread(&restaurants, sizeof(Restaurant), 8, restaurantFile);
    }
    fclose(restaurantFile);

    for(int i=0; i<8; i++){
        root = insertRestaurantNode(root, restaurants[i]);
    }

    return root;
}

void printRestaurantsData(RestaurantNode* root){
    if(!root) return;

    printRestaurantDetails(root->restaurant);
    printf("\n-----------------\n");

    printRestaurantsData(root->left);
    printRestaurantsData(root->right);
}

void printRestaurantListByIndex(RestaurantNode* root, int* i){
    if(!root) return;

    printRestaurantListByIndex(root->left, i);
    printf("%d: %s\n", *i, root->restaurant.restaurantName, i);
    *i = *i + 1;
    printRestaurantListByIndex(root->right, i);

}


// Searching restaurant list by type, and returning a Tree of result
void searchByType(RestaurantNode* root, char type[], RestaurantNode** result){
    if(!root) return;

    if(strcmp(root->restaurant.type, type) == 0){
        *result = insertRestaurantNode(*result, root->restaurant);
    }

    searchByType(root->left, type, result);
    searchByType(root->right, type, result);
}

void searchByCuisine(RestaurantNode* root, char cuisine[], RestaurantNode** result){
    if(!root) return;

    for(int i=0; i<10; i++){
        if(strcmp(root->restaurant.cuisine[i], cuisine) == 0){
            *result = insertRestaurantNode(*result, root->restaurant);
        }
    }

    searchByCuisine(root->left, cuisine, result);
    searchByCuisine(root->right, cuisine, result);
}

void searchByArea(RestaurantNode* root, char areaName[], RestaurantNode** result){
    if(!root) return;

    if(strcmp(root->restaurant.areaName, areaName) == 0){
        *result = insertRestaurantNode(*result, root->restaurant);
    }

    searchByArea(root->left, areaName, result);
    searchByArea(root->right, areaName, result);
}
//
//void printRestaurantFromName(RestaurantNode* head, char restaurantName[20]){
//    RestaurantNode* temp = head;
//
//    while(temp != NULL){
//        if(strcmp(temp->restaurant.restaurantName, restaurantName) == 0) break;
//        temp = temp->next;
//    }
//
//    printRestaurantDetails(temp->restaurant);
//}
//
//

//For interface use
void getRestaurantByIndex(RestaurantNode* root, int* index, Restaurant* restaurant){
    if(!root) return;
    if(*index < 1) return;

    getRestaurantByIndex(root->left, index, restaurant);
    if(*index == 1){
        *restaurant = root->restaurant;
    }
    (*index)--;
    getRestaurantByIndex(root->right, index, restaurant);
}
//
RestaurantNode* getRestaurantByName(RestaurantNode* root, char restaurantName[]){
    if(!root) return NULL;

    if(strcmp(root->restaurant.restaurantName, restaurantName) > 0) return getRestaurantByName(root->left, restaurantName);
    else if(strcmp(root->restaurant.restaurantName, restaurantName) < 0) return getRestaurantByName(root->right, restaurantName);
    else return root;
}
//
//void deleteRestaurantList(RestaurantNode* head){
//    RestaurantNode* temp = head;
//
//    while(head != NULL){
//        head = head->next;
//        free(temp);
//        temp = head;
//    }
//}


#endif //HUNGYAPP_RESTAURANTLL_H
