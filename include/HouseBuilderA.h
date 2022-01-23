#pragma once

#include "HouseBuilder.h"

class HouseBuilderA : public HouseBuilder {
public:
    void createHouse() override;
    void createWall() override;
    void createWindow() override;
    void createPipe() override;
    void createRoof() override;
    void printHouse() override;
private:
};