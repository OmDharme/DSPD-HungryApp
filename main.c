#include <stdio.h>

#include "HungryApp.h"

int main() {

    HungryApp* app = initialiseApp();

    appInterface(app, app->userData);

    return 0;
}
