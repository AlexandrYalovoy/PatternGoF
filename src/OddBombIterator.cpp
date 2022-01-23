#include "OddBombIterator.h"

#include <utility>

OddBombIterator::OddBombIterator(std::vector<DynamicObject *> refArr) :
                                 mRefArr(std::move(refArr)), mCurIndex(0),
                                 mPtr(nullptr){
}

void OddBombIterator::First() {
    mCurIndex = 1;
    mPtr = dynamic_cast<Bomb*>(mRefArr[mCurIndex]);
}

bool OddBombIterator::isDone() const {
    return mCurIndex == mRefArr.size();
}

Bomb* OddBombIterator::Next() {
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

Bomb* OddBombIterator::CurrentObj() {
    return mPtr;
}
