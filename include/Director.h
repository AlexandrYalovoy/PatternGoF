#ifndef SBOMBER_DIRECTOR_H
#define SBOMBER_DIRECTOR_H

#include "HouseBuilder.h"
#include "HouseBuilderA.h"
#include "House.h"

class Director {
public:
    House* createStandardHouse(HouseBuilder* pBuilder) {
        pBuilder->createHouse();
        pBuilder->createPipe();
        pBuilder->createRoof();
        pBuilder->createWall();
        pBuilder->createWindow();
        return (pBuilder->getHouse());
    }
    House* createMinimalHouse(HouseBuilder* pBuilder) {
        pBuilder->createHouse();
        pBuilder->createRoof();
        pBuilder->createWall();
        return (pBuilder->getHouse());

    }
private:
};


#endif //SBOMBER_DIRECTOR_H