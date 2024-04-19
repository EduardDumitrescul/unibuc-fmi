#include <iostream>
#include "Menu.h"

int main() {
    std::srand(time(nullptr));

    Menu* menu = Menu::getInstance();
    menu->run();


    return 0;
}
