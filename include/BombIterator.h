#ifndef SBOMBER_BOMBITERATOR_H
#define SBOMBER_BOMBITERATOR_H

#include <vector>

#include "Bomb.h"
#include "IIterator.h"

class BombIterator {
public:
    explicit BombIterator(std::vector<Bomb*>  vecBombs);
    void begin();
    Bomb* Next();
    Bomb* CurrentObj();
    [[nodiscard]]bool isDone() const;
private:
    std::vector<Bomb*> mVecBombs;
    size_t mCurIndex;
    Bomb* mPtr;
};



#endif //SBOMBER_BOMBITERATOR_H
