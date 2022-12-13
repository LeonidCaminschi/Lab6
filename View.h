#pragma once

#include <iostream>

void View(char** field, int maxSize) {
    for (int i=0; i<maxSize-1; i++) {
        for (int j=0; j<maxSize-1; j++) {
            std::cout << field[i][j] << " ";
        }
        std::cout << std::endl;
    }
}