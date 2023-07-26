//
// Created by Om Dharme on 11/03/23.
//

#ifndef HUNGYAPP_ORDERLL_H
#define HUNGYAPP_ORDERLL_H

#include "./../Headers/Order.h"
#include "stdlib.h"
#include "string.h"
#include "utils.h"

typedef struct OrderNode{
    Order order;
    struct OrderNode *left;
    struct OrderNode *right;
    int height;
} OrderNode;

OrderNode* createOrderNode(Order order){
    OrderNode* newNode = (OrderNode*)malloc(sizeof(OrderNode));
    newNode->order = order;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;

    return newNode;
}

int getOrderHeight(OrderNode* orderNode){
    if(!orderNode) return 0;

    return orderNode->height;
}

OrderNode *rightRotateOrder(OrderNode *y) {
    OrderNode *x = y->left;
    OrderNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getOrderHeight(y->left), getOrderHeight(y->right)) + 1;
    x->height = max(getOrderHeight(x->left), getOrderHeight(x->right)) + 1;

    return x;
}

OrderNode *leftRotateOrder(OrderNode *x) {
    OrderNode *y = x->right;
    OrderNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getOrderHeight(x->left), getOrderHeight(x->right)) + 1;
    y->height = max(getOrderHeight(y->left), getOrderHeight(y->right)) + 1;

    return y;
}

int getBalanceOrder(OrderNode* orderNode) {
    if (orderNode == NULL)
        return 0;
    return getOrderHeight(orderNode->left) - getOrderHeight(orderNode->right);
}

OrderNode * insertOrderNode(OrderNode* root, Order order) {
    // Find the correct position to insertNode the node and insertNode it
    if (root == NULL)
        return createOrderNode(order);

    if (dateComp(order.dateOrdered,root->order.dateOrdered) < 0)
        root->left = insertOrderNode(root->left, order);
    else if (dateComp(order.dateOrdered,root->order.dateOrdered) >= 0)
        root->right = insertOrderNode(root->right, order);
    else
        return root;

    // Update the balance factor of each node and
    // Balance the tree
    root->height = 1 + max(getOrderHeight(root->left),
                           getOrderHeight(root->right));

    int balance = getBalanceOrder(root);
    if (balance > 1 && dateComp(order.dateOrdered,root->left->order.dateOrdered) < 0)
        return rightRotateOrder(root);

    if (balance < -1 && dateComp(order.dateOrdered,root->right->order.dateOrdered) > 0)
        return leftRotateOrder(root);

    if (balance > 1 && dateComp(order.dateOrdered,root->left->order.dateOrdered) > 0) {
        root->left = leftRotateOrder(root->left);
        return rightRotateOrder(root);
    }

    if (balance < -1 && dateComp(order.dateOrdered,root->right->order.dateOrdered) < 0) {
        root->right = rightRotateOrder(root->right);
        return leftRotateOrder(root);
    }

    return root;
}


void printOrdersData(OrderNode* root){
    if(!root) return;

    printOrdersData(root->left);
    printOrderDetails(root->order);
    printOrdersData(root->right);
}

OrderNode* minValueNode(OrderNode* node) {
    OrderNode* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

OrderNode* deleteOrderNode(OrderNode* root, Order order) {
    // Find the node and delete it
    if (root == NULL)
        return root;

    if(root->right == NULL){
        free(root);
        root = NULL;
    }else{
        root->right = deleteOrderNode(root->right, order);
    }

    if (root == NULL)
        return root;

    // Update the balance factor of each node and
    // balance the tree
    root->height = 1 + max(getOrderHeight(root->left),
                           getOrderHeight(root->right));

    int balance = getBalanceOrder(root);
    if (balance > 1 && getBalanceOrder(root->left) >= 0)
        return rightRotateOrder(root);

    if (balance > 1 && getBalanceOrder(root->left) < 0) {
        root->left = leftRotateOrder(root->left);
        return rightRotateOrder(root);
    }

    if (balance < -1 && getBalanceOrder(root->right) <= 0)
        return leftRotateOrder(root);

    if (balance < -1 && getBalanceOrder(root->right) > 0) {
        root->right = rightRotateOrder(root->right);
        return leftRotateOrder(root);
    }

    return root;
}

//OrderNode* removeDeliveredOrder(OrderNode* head){
//    OrderNode *temp = head, *prev = NULL;
//
//    if(temp->next == NULL){
//        free(temp);
//        return NULL;
//    }else{
//        while(temp->next != NULL){
//            prev = temp;
//            temp = temp->next;
//        }
//
//        prev->next = NULL;
//        free(temp);
//    }
//
//    return head;
//}

#endif //HUNGYAPP_ORDERLL_H
