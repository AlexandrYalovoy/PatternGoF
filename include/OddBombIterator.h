#ifndef SBOMBER_ODDBOMBITERATOR_H
#define SBOMBER_ODDBOMBITERATOR_H

#include "SBomber.h"
#include "EvenBombIterator.h"

class OddBombIterator : public IIterator {
public:
    explicit OddBombIterator(std::vector<DynamicObject*>  refArr);
    void First() override;
    [[nodiscard]] bool isDone() const override;
    Bomb* Next() override;
    Bomb* CurrentObj() override;
private:
    std::vector<DynamicObject*> mRefArr;
    size_t mCurIndex;
    Bomb *mPtr;
};


#endif //SBOMBER_ODDBOMBITERATOR_H
