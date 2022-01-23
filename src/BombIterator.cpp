#include "BombIterator.h"

#include <iostream>
#include <utility>

BombIterator::BombIterator(std::vector<Bomb*>  vecBombs) :
                 mVecBombs(std::move(vecBombs)), mCurIndex(0),
                 mPtr(nullptr) {
}

void BombIterator::begin() {
    mCurIndex = 0;
}

Bomb *BombIterator::CurrentObj() {
    return mVecBombs[mCurIndex];
}

bool BombIterator::isDone() const {
    return mCurIndex == mVecBombs.size();
}

Bomb* BombIterator::Next() {
    if (isDone()) {
        mCurIndex = 0;
        mPtr = nullptr;
    }
    ++mCurIndex;

    if (mCurIndex > mVecBombs.size()) {
        mCurIndex = mVecBombs.size();
    }
    if (!isDone()) {
        mPtr = mVecBombs[mCurIndex];
    }
    return mPtr;
}




