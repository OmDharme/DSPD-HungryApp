//
// Created by Om Dharme on 10/04/23.
//

#ifndef HUNGRYAPPV2_HUNGRYAPP_H
#define HUNGRYAPPV2_HUNGRYAPP_H

#include "Trees/AgentTree.h"
#include "Trees/AreaTree.h"
#include "Trees/UserTree.h"
#include "Trees/RestaurantTree.h"
#include "Trees/OrderTree.h"

typedef struct HungryApp{
    AreaNode* areaData;
    AgentNode* agentData;
    UserNode* userData;
    RestaurantNode* restaurantData;
    OrderNode* liveOrderData;

} HungryApp;

HungryApp* initialiseApp(){
    HungryApp* app = (HungryApp*)malloc(sizeof(HungryApp));

    app->areaData = initialiseAreaData();
    app->agentData = initialiseAgentData();
    app->userData = initialiseUserList();
    app->restaurantData = initialiseRestaurantData();
    app->liveOrderData = NULL;

    return app;
}

void assignAgentToOrder(AgentNode* root, Order* order, bool* done){
    if(!root || *done) return;

    if(root->agent.isFree){
        if(*done == false){
            root->agent.isFree = false;
            strcpy((*order).agentAssignedId,root->agent.id);
            *done = true;
            return;
        }
    }

    assignAgentToOrder(root->left, order, done);
    assignAgentToOrder(root->right, order, done);
}

Order placeOrder(HungryApp* app, Order order){
    bool done = false;
    assignAgentToOrder(app->agentData, &order, &done);
//    printAgentsData(app->agentData);
    app->liveOrderData = insertOrderNode(app->liveOrderData, order);
    return order;
}

void printOrderPlacedDetails(HungryApp* app, Order order){
    printf("\nOrder: %s - Rs %.2f\n", order.food.name, order.food.price);
    printf("Date ordered: ");
    printDate(order.dateOrdered);
    printf("\n");
    printAgentDetails(getAgentById(app->agentData, order.agentAssignedId)->agent);
}

void cancelOrder(HungryApp* app, Order order){
    getAgentById(app->agentData, order.agentAssignedId)->agent.isFree = true;

    app->liveOrderData = deleteOrderNode(app->liveOrderData, order);
}

bool orderPlacedInterface(HungryApp* app, char userId[], Order order){
    bool done = false;

    while(!done){
        system("clear");
        printf("0: Go To Home page\n");
        printf("1: Cancel Order?\n");

        printf("Order Placed!! \n\n");

        printf("Order Details:\n");
        printOrderPlacedDetails(app, order);

        int choice;
        scanf("%d", &choice);

        if(choice == 0){
            return true;
        }
        else if(choice == 1){
            cancelOrder(app, order);
            return true;
        }
    }
}

bool placeOrderInterface(HungryApp* app, char userId[], Food food){
    bool done = false;

    while(!done){
        system("clear");
        printf("0: Go Back\n");
        printf("1: Place Order\n");
        printf("\nWould you like to order: %s - Rs %.2f\n\n", food.name, food.price);

        int choice;
        scanf("%d", &choice);

        if(choice == 0) return false;
        else if(choice == 1){
            Order order;
            strcpy(order.userId ,userId);
            order.food = food;
            order.dateOrdered = getCurrentDate();
            order = placeOrder(app, order);
            if(orderPlacedInterface(app, userId, order)) return true;
        }
    }

}

bool menuInterface(HungryApp* app, char userId[], Food menu[], int size){
    bool done = false;

    while(!done){
        system("clear");
        printf("0: Go Back\n");
        for(int i=0; i<size && !done; i++){
            if(menu[i].price == 0.0) done = true;
            else printf("%d: %s - Rs %.2f\n", i+1, menu[i].name, menu[i].price);
        }

        int choice;
        scanf("%d", &choice);

        if(choice == 0) return false;
        else{
            if(placeOrderInterface(app, userId, menu[choice-1])) return true;
        }
    }
}

bool restaurantInterface(HungryApp* app, char userId[], Restaurant restaurant){
    bool done = false;

    while(!done){
        system("clear");
        printf("0: Go Back\n");
        printf("1: Check Menu\n");
        printRestaurantDescription(restaurant);

        int choice;
        scanf("%d", &choice);

        if(choice == 0) return false;
        else{
            if(menuInterface(app, userId, restaurant.menu, 30)) return true;
        }
    }
}

bool searchResultInterface(HungryApp* app, char userId[], RestaurantNode* searchResult){
    bool done = false;

    while(!done){
        system("clear");
        printf("0: Go Back\n");

        int i=1;
        printRestaurantListByIndex(searchResult, &i);

        int choice;
        scanf("%d", &choice);

        if(choice == 0) return false;
        else{
            Restaurant restaurant;
            getRestaurantByIndex(searchResult, &choice, &restaurant);
            if(restaurantInterface(app, userId, restaurant)) return true;
        }
    }
}

bool typeInterface(HungryApp* app, char userId[]){
    char types[3][20] = {"Restaurant", "Cafe", "Pub"};
    bool done = false;

    while(!done){
        system("clear");
        printf("0: Go Back\n");
        for(int i=1; i<=3; i++){
            printf("%d: %s\n", i, types[i-1]);
        }

        int choice;
        scanf("%d", &choice);

        if(choice == 0) return false;
        else{
            RestaurantNode* searchResult = NULL;
            searchByType(app->restaurantData, types[choice-1], &searchResult);
            if(searchResultInterface(app, userId, searchResult)) return true;
        }
    }
}

bool cuisineInterface(HungryApp* app, char userId[]){
    char cuisines[15][40] = {"Chaat", "Chinese", "South-Indian", "Thali", "Biryani", "Main-Course", "Desert", "Drinks", "Coffee", "Pizza", "Pasta", "Sandwich", "Shakes", "Pure-Veg", "Non-Veg"};
    bool done = false;

    while(!done){
        system("clear");
        printf("0: Go Back\n");
        for(int i=1; i<=15; i++){
            printf("%d: %s\n", i, cuisines[i-1]);
        }

        int choice;
        scanf("%d", &choice);

        if(choice == 0) return false;
        else{
            RestaurantNode* searchResult = NULL;
            searchByCuisine(app->restaurantData, cuisines[choice-1], &searchResult);
            if(searchResultInterface(app, userId, searchResult)) return true;
        }
    }
}

bool areaInterface(HungryApp* app, char userId[]){
    char areas[8][20] = {"Area1", "Area2", "Area3", "Area4", "Area5", "Area6", "Area7", "Area8"};
    bool done = false;

    while(!done){
        system("clear");
        printf("0: Go Back\n");
        for(int i=1; i<=8; i++){
            printf("%d: %s\n", i, areas[i-1]);
        }

        int choice;
        scanf("%d", &choice);

        if(choice == 0) return false;
        else{
            RestaurantNode* searchResult = NULL;
            searchByArea(app->restaurantData, areas[choice-1], &searchResult);
            if(searchResultInterface(app, userId, searchResult)) return true;
        }
    }
}

bool searchRestaurantInterface(HungryApp* app, char userId[]){
    bool done = false;

    while(!done){
        system("clear");
        printf("0: Go Back\n");
        printf("1: Search By Type\n");
        printf("2: Search By Cuisine\n");
        printf("3: Search By Area\n");

        int choice;
        scanf("%d", &choice);

        if(choice == 0){
            system("clear");
            return false;
        }else if(choice == 1){
            if(typeInterface(app, userId)) return true;
        }else if(choice == 2){
            if(cuisineInterface(app, userId)) return true;
        }else if(choice == 3){
            if(areaInterface(app, userId)) return true;
        }
    }
}

void printOrdersHelper(HungryApp* app, OrderNode* root){
    if(!root) return;

    printOrdersHelper(app, root->left);
    printOrderPlacedDetails(app, root->order);
    printOrdersHelper(app, root->right);
}

void currentOrdersInterface(HungryApp* app, char userId[]){
    bool done = false;

    while(!done){
        system("clear");
        printf("0: Go Back\n");
        if(app->liveOrderData == NULL){
            printf("No Current Orders\n");
        }else{
            printOrdersHelper(app, app->liveOrderData);
//            printOrdersData(app->liveOrderData);
        }

        int choice;
        scanf("%d", &choice);

        if(choice == 0) return;
    }
}

OrderNode* removeDeliveredOrder(OrderNode* root){
    // Find the node and delete it
    if (root == NULL)
        return root;

    if(root->left) removeDeliveredOrder(root->left);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            OrderNode *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        }
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

void deliverOrder(HungryApp* app){
    OrderNode *orderNode = app->liveOrderData, *parent = NULL;
    bool done = false;

    while(!done){
        if(orderNode->left){
            parent = orderNode;
            orderNode = orderNode->left;
        }else{
            done = true;
        }
    }

    AgentNode* agentNode = getAgentById(app->agentData, orderNode->order.agentAssignedId);
    agentNode->agent.isFree = true;
    agentNode->agent.commission = agentNode->agent.commission * 1.1;

    app->liveOrderData = removeDeliveredOrder(app->liveOrderData);
}

bool deliveryDoneInterface(){
    bool done = false;

    while(!done){
        system("clear");
        printf("0: Go Back\n\n");

        printf("Order Delivered!!!\n\n");

        int choice;
        scanf("%d", &choice);

        if(choice == 0) return false;
    }
}

bool previousOrderInterface(HungryApp* app, Order order){
    system("clear");
    bool done = false;

    while(!done){
        printf("0: Go Back\n");
        printf("1: Reorder?\n\n");
        printOrderDetails(order);

        int choice;
        scanf("%d", &choice);

        if(choice == 0) return false;
        else if(choice  == 1){
            if(placeOrderInterface(app, order.userId, order.food)) return true;
        }
    }

}

bool previousOrdersInterface(HungryApp* app, char userId[]){
    bool done = false;
    User user = getUserById(app->userData, userId)->user;

    while(!done){
        system("clear");
        printf("0: Go Back\n");
        printStackByIndex(&user.previousOrders);

        int choice;
        scanf("%d", &choice);

        if(choice == 0) return false;
        else{
            if(previousOrderInterface(app, user.previousOrders.orders[user.previousOrders.top + 1 -choice])) return true;
        }
    }
}

void allOrdersTraverse(UserNode* root, RestaurantSet* restaurantSet){
    if(!root) return;

    for(int i=0; i<= root->user.previousOrders.top; i++){
        insertInRestaurantSet(restaurantSet, root->user.previousOrders.orders[i].food.restaurantName);
    }

    allOrdersTraverse(root->left, restaurantSet);
    allOrdersTraverse(root->right, restaurantSet);
}

RestaurantNode* findTopRestaurants(HungryApp* app){
    RestaurantSet restaurantSet;
    initialiseRestaurantSet(&restaurantSet);

    allOrdersTraverse(app->userData, &restaurantSet);

    RestaurantNode* newRoot = createRestaurantNode(getRestaurantByName(app->restaurantData, restaurantSet.restaurants[1].restaurantName)->restaurant);
    newRoot->left = createRestaurantNode(getRestaurantByName(app->restaurantData, restaurantSet.restaurants[0].restaurantName)->restaurant);
    newRoot->right = createRestaurantNode(getRestaurantByName(app->restaurantData, restaurantSet.restaurants[2].restaurantName)->restaurant);

    return newRoot;
}

bool topRestaurantsInterface(HungryApp* app, char userId[]){
    RestaurantNode* searchResult = findTopRestaurants(app);
    if(searchResultInterface(app, userId, searchResult)) return true;
}

Food* findFavouriteFoodsOfUser(HungryApp* app, char userId[10], Food favFoods[3]){
    User user = getUserById(app->userData, userId)->user;

    FoodSet foodSet;
    initialiseFoodSet(&foodSet);

    int currMonth = getCurrentMonth();

    for(int i=0; i<=user.previousOrders.top; i++){
        int orderPlacedMonth = user.previousOrders.orders[i].dateOrdered.month;
        if(currMonth - orderPlacedMonth <= 2 && currMonth - orderPlacedMonth >= 0){
            insertInFoodSet(&foodSet, user.previousOrders.orders[i].food);
        }
    }

    for(int i=0; i<3; i++){
        favFoods[i] = foodSet.foods[i].food;
    }

    return favFoods;
}

bool favouriteOrdersUserInterface(HungryApp* app, char userId[]){
    Food favFoods[3];
    findFavouriteFoodsOfUser(app, userId, favFoods);
    if(menuInterface(app, userId, favFoods, 3)) return true;
}

void allOrdersTraverse2(UserNode* root, FoodSet* foodSet){
    if(!root) return;

    for(int i=0; i<= root->user.previousOrders.top; i++){
        insertInFoodSet(foodSet, root->user.previousOrders.orders[i].food);
    }

    allOrdersTraverse2(root->left, foodSet);
    allOrdersTraverse2(root->right, foodSet);
}

void findFavouriteFoodsAcrossRestaurants(HungryApp* app, Food favFoods[3]){
    UserNode* temp = app->userData;

    FoodSet foodSet;
    initialiseFoodSet(&foodSet);

    allOrdersTraverse2(app->userData, &foodSet);

    for(int i=0; i<3; i++){
        favFoods[i] = foodSet.foods[i].food;
    }
}

bool favouriteOrdersOverallInterface(HungryApp* app, char userId[]){
    Food favFoods[3];
    findFavouriteFoodsAcrossRestaurants(app, favFoods);
    if(menuInterface(app, userId, favFoods, 3)) return true;
}

void rangeSearch(OrderNode* root, char userId1[], char userId2[]){
    if(!root) return;

    rangeSearch(root->left, userId1, userId2);
    if(strcmp(root->order.userId, userId1) >= 0 && strcmp(root->order.userId, userId2) <= 0){
        printOrderDetails(root->order);
    }
    rangeSearch(root->right, userId1, userId2);
}

void appInterface(HungryApp* app, char userId[10]){
    bool done = false;

    while(!done){
        system("clear");
        printf("---------------- Hungry App ----------------\n\n");
        printf("0: Quit\n");
        printf("1: See Top 3 Restaurants\n");
        printf("2: Search Restaurants\n");
        printf("3: See Your Favourite Orders\n");
        printf("4: See Top 3 Most Ordered Dishes\n");
        printf("5: See Previous Orders\n");
        printf("6: See Current Order Details\n");
        printf("7: Get delivery\n");

        int choice;
        scanf("%d", &choice);

        if(choice == 0){
            system("clear");
            return;
        }else if(choice == 1){
            topRestaurantsInterface(app, userId);
        }else if(choice == 2){
            searchRestaurantInterface(app, userId);
        }else if(choice == 3){
            favouriteOrdersUserInterface(app, userId);
        }else if(choice == 4){
            favouriteOrdersOverallInterface(app, userId);
        }else if(choice == 5){
            previousOrdersInterface(app, userId);
        }else if(choice == 6){
            currentOrdersInterface(app, userId);
        }else if(choice == 7){
            deliverOrder(app);
            deliveryDoneInterface();
        }
    }

}

#endif //HUNGRYAPPV2_HUNGRYAPP_H
