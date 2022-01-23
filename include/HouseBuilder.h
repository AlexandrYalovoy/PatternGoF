#pragma once

#include <memory>

#include "House.h"

class HouseBuilder {
public:
    virtual ~HouseBuilder() = default;
    HouseBuilder() = default;
    virtual void createHouse() {};
    virtual void createWall() {};
    virtual void createWindow() {};
    virtual void createPipe() {};
    virtual void createRoof() {};
    virtual House* getHouse() {return pHouse.get();}
    virtual void printHouse() {};
protected:
//    House* pHouse;
    std::unique_ptr<House> pHouse;
};