#include "EvenBombIterator.h"

#include <utility>

EvenBombIterator::EvenBombIterator(std::vector<DynamicObject *> refArr) :
                               mRefArr(std::move(refArr)), mCurIndex(0), mPtr(nullptr){

}

void EvenBombIterator::First() {
    mCurIndex = 1;
    mPtr = dynamic_cast<Bomb*>(mRefArr[mCurIndex]);
}

Bomb *EvenBombIterator::Next() {
    if (isDone()) {
        mPtr = nullptr;
        mCurIndex = 0;
    }


    mCurIndex += 2;
    if (mCurIndex > mRefArr.size()) {
        mCurIndex = mRefArr.size();
    }
    if (!isDone()) {
        mPtr = dynamic_cast<Bomb*>(mRefArr[mCurIndex]);
    }

    return mPtr;
}

bool EvenBombIterator::isDone() const {
    return mCurIndex == mRefArr.size();
}

Bomb *EvenBombIterator::CurrentObj() {
    return mPtr;
}
