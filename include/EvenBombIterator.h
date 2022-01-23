#ifndef SBOMBER_EVENBOMBITERATOR_H
#define SBOMBER_EVENBOMBITERATOR_H

#include "SBomber.h"
#include "IIterator.h"

class EvenBombIterator : public IIterator {
private:

public:
    explicit EvenBombIterator(std::vector<DynamicObject*>  refArr);
    void First() override;
    Bomb* Next() override;
    [[nodiscard]] bool isDone() const override;
    [[nodiscard]] Bomb* CurrentObj() override;

private:
    std::vector<DynamicObject*> mRefArr;
    size_t mCurIndex;
    Bomb* mPtr;
};


#endif //SBOMBER_EVENBOMBITERATOR_H
