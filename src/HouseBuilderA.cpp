#include <iostream>

#include "HouseBuilderA.h"


void HouseBuilderA::createWall() {
    for (size_t i = 0; i < House::rows; ++i) {
        for (size_t j = 0; j < House::columns; ++j) {
            if ((i == 5 && j == 4) || (i == 6 && j == 4)) {
                pHouse->look[i][j] = '#';
            }
            else if ((i == 5 && j == 12) || (i == 6 && j == 12)) {
                pHouse->look[i][j] = '#';
            }
        }
    }

}

void HouseBuilderA::createWindow() {
    for (size_t i = 0; i < House::rows; ++i) {
        for (size_t j = 0; j < House::columns; ++j) {
            if (i == 5 && j == 7) {
                while (j <= 9) {
                    pHouse->look[i][j] = '#';
                    ++j;
                }
            }
            else if (i == 6 && j == 7) {
                while (j <= 9) {
                    pHouse->look[i][j] = '#';
                    ++j;
                }
            }
        }
    }
}

void HouseBuilderA::createPipe() {
    for (size_t i = 0; i < House::rows; ++i) {
        for (size_t j = 0; j < House::columns; ++j) {
            if (i == 0 && j == 10) {
                pHouse->look[i][j] = '#';
            }
            else if (i == 1 && j == 10) {
                pHouse->look[i][j] = '#';
            }
            else if (i == 2 && j == 10) {
                pHouse->look[i][j] = '#';
            }
        }
    }
}

void HouseBuilderA::createRoof() {
    for (size_t i = 0; i < House::rows; ++i) {
        for (size_t j = 0; j < House::columns; ++j) {
            if (i == 1 && j == 8) {
                pHouse->look[i][j] = '#';
            }
            else if ((i == 2 && j == 7) || (i == 2 && j == 9)) {
                pHouse->look[i][j] = '#';
            }
            else if ((i == 3 && j == 6) || (i == 3 && j == 10)) {
                pHouse->look[i][j] = '#';
            }
            else if (i == 4 && j == 4) {
                while (j <= 12) {
                    pHouse->look[i][j] = '#';
                    ++j;
                }
            }
        }
    }
}

void HouseBuilderA::printHouse() {
    for (size_t i = 0; i < House::rows; ++i) {
        for (size_t j = 0; j < House::columns; ++j) {
            std::cout << pHouse->look[i][j] << ' ';
        }
        std::cout << '\n';;
    }

}

void HouseBuilderA::createHouse() {
    pHouse = std::make_unique<House>();
    for (size_t i = 0; i < House::rows; ++i) {
        for (size_t j = 0; j < House::columns; ++j) {
            pHouse->look[i][j] = ' ';
        }
    }
}


